#include "PreCompile.h"
#include "GameEngineInstancingRenderer.h"
#include "GameEngineInputLayout.h"
#include "GameEngineDevice.h"
#include "GameEngineInstancingBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineVertexes.h"


GameEngineInstancingRenderer::InstancingUnit::InstancingUnit(
	const std::set<std::string>& _structuredBufferSetterNames,
	const std::string_view& _meshName,
	const std::string_view& _materialName
)
{
	for (const std::string& name : _structuredBufferSetterNames)
	{
		data_.insert(std::make_pair(name, nullptr));
	}

	this->renderUnit_ = std::make_shared<GameEngineRenderUnit>();
	this->renderUnit_->SetMesh(_meshName);
	this->renderUnit_->SetMaterial(_materialName);
	this->renderUnit_->Off();
	this->textureIndex_ = 0;
	//this->isRendering_ = true;
}

void GameEngineInstancingRenderer::InstancingUnit::Link(const std::string_view& _name, const void* _data)
{
	std::string uppercaseDataName = GameEngineString::ToUpperReturn(_name);

	if (data_.end() == data_.find(uppercaseDataName))
	{
		MsgBoxAssertString(std::string(_name) + ": �׷� �̸��� �ν��Ͻ� �����Ͱ� �������� �ʽ��ϴ�.");
		//Ʈ������������, ��Ʋ�󽺵����͸� ��ũ���ѵ� ����� �������� ����.
		return;
	}
	else
	{
		data_.find(uppercaseDataName)->second = _data;
	}
}

void GameEngineInstancingRenderer::InstancingUnit::SetWorldScale(const float4& _worldScaleVector)
{
	this->transformData_.worldScaleVector_ = _worldScaleVector;
	this->transformData_.localScaleMatrix_.Scale(_worldScaleVector);
	CalWorldWorldMatrix();
}

void GameEngineInstancingRenderer::InstancingUnit::SetWorldRotation(const float4& _worldRotationVector)
{
	this->transformData_.worldRotationVector_ = _worldRotationVector;
	this->transformData_.localRotationMatrix_.Rotate3AxisByDegree(_worldRotationVector);
	CalWorldWorldMatrix();
}

void GameEngineInstancingRenderer::InstancingUnit::SetWorldPosition(const float4& _worldPositionVector)
{
	this->transformData_.worldPositionVector_ = _worldPositionVector;
	this->transformData_.localPositionMatrix_.Position(_worldPositionVector);
	CalWorldWorldMatrix();
}

void GameEngineInstancingRenderer::InstancingUnit::SetTextureIndex(unsigned int _textureIndex)
{
	textureIndex_ = _textureIndex;
}

void GameEngineInstancingRenderer::InstancingUnit::CalWorldWorldMatrix()
{
	this->transformData_.worldWorldMatrix_
		= this->transformData_.localScaleMatrix_ 
		* this->transformData_.localRotationMatrix_ 
		* this->transformData_.localPositionMatrix_;
}

GameEngineInstancingRenderer::GameEngineInstancingRenderer()
	: instancingUnitCount_(0),
	topology_(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
}

GameEngineInstancingRenderer::~GameEngineInstancingRenderer()
{
}

void GameEngineInstancingRenderer::Initialize(
	size_t _instancingUnitCount,
	const std::string_view& _meshName,
	const std::string_view& _materialName
)
{
	if (0 == _instancingUnitCount)
	{
		MsgBoxAssert("�ν��Ͻ� ������ 0�� �� �� �����ϴ�.");
		return;
	}

	if (false == GameEngineMaterial::Find(_materialName)->GetVertexShader()->IsInstancing())
	{
		MsgBoxAssertString(std::string(_materialName) + ": �� ���׸����� ���ؽ����̴��� �ν��Ͻ� �غ� �Ǿ����� �ʽ��ϴ�.");
		return;
	}

	if (false == GameEngineMaterial::Find(_materialName)->GetPixelShader()->IsInstancing())
	{
		MsgBoxAssertString(std::string(_materialName) + ": �� ���׸����� �ȼ����̴��� �ν��Ͻ� �غ� �Ǿ����� �ʽ��ϴ�.");
		return;
	}

	this->instancingUnitCount_ = _instancingUnitCount;


	this->mesh_ = GameEngineMesh::Find(_meshName);

	//�ν��Ͻ� ���� ũ��.
	UINT instancingSize = this->mesh_->GetInputLayoutDesc().instanceSize_;
	
	this->instancingBuffer_ = GameEngineInstancingBuffer::Create(instancingUnitCount_, instancingSize);
	//instancingUnitCount_ * instancingSizeũ���� �ν��Ͻ̹��� ����.

	instanceIndexBuffer_.resize(static_cast<size_t>(instancingSize) * instancingUnitCount_);
	//instancingUnitCount_ * instancingSizeũ��� �ο��ε��� ���� ũ�� ����.


	this->material_ = GameEngineMaterial::Create();
	this->material_->Copy(GameEngineMaterial::Find(_materialName));

	this->shaderResourceHelper_ = GameEngineShaderResourceHelper();
	this->shaderResourceHelper_.ShaderCheck(
		this->material_->GetVertexShader()->GetInst_VertexShader());
	//this->shaderResourceHelper_.ShaderCheck(
	//	GameEngineMaterial::Find(_materialName)->GetPixelShader());
	this->shaderResourceHelper_.ShaderCheck(
		this->material_->GetPixelShader()->GetInst_PixelShader());


	
	std::multimap<std::string, GameEngineStructuredBufferSetter>& structuredBufferSetters
		= shaderResourceHelper_.GetStructuredBufferSetterMap();
	//���̴����ҽ����ۿ� ��ϵ� ����ȭ���� ���͸� ���� �����´�.



	for (std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator iter = structuredBufferSetters.begin();
		iter != structuredBufferSetters.end(); ++iter)
	{
		//Ʈ������������, ��Ʋ�󽺵����ʹ� ���� ó���ؾ��ϹǷ� ũ�� ������ �ϰ� structuredBufferSetterNames_���� ������� �ʴ´�.
		if (0 == iter->first.compare("INST_TRANSFORMDATA")
			|| 0 == iter->first.compare("INST_ATLASDATA"))
		{
			iter->second.Resize(instancingUnitCount_);
			continue;
		}

		if (std::string::npos != iter->first.find("INST_"))
		{
			//structuredBufferSetters�� ��� ����ȭ���� ���͵� �� �̸��� "INST_" ��� ���ڿ��� ���Ե� �͵鸸 ��� 
			// structuredBufferSetterNames_�� �̸��� ����Ѵ�.
			structuredBufferSetterNames_.insert(iter->first);

			//�� ���Ϳ� ����� ����ȭ���۸� �����ϰų� ũ�⸦ �����Ѵ�.
			iter->second.Resize(instancingUnitCount_);
		}
	}

	this->allInstancingUnits_.reserve(instancingUnitCount_);
	for (size_t i = 0; i < instancingUnitCount_; ++i)
	{
		allInstancingUnits_.push_back(
			GameEngineInstancingRenderer::InstancingUnit::InstancingUnit(
				this->structuredBufferSetterNames_,
				_meshName,
				_materialName
			)
		);
	}
}

void GameEngineInstancingRenderer::SetAllUnitsWorldScale(const float4& _worldScaleVector)
{
	for (InstancingUnit& singleInstancingUnit : allInstancingUnits_)
	{
		singleInstancingUnit.transformData_.localScaleMatrix_.Scale(_worldScaleVector);
		singleInstancingUnit.CalWorldWorldMatrix();
	}
}

void GameEngineInstancingRenderer::Render(
	float _deltaTime,
	const float4x4& _viewMatrix,
	const float4x4& _projectionMatrix
)
{
	std::multimap<std::string, GameEngineStructuredBufferSetter>& structuredBufferSetters
		= shaderResourceHelper_.GetStructuredBufferSetterMap();

	int* instanceIndexBufferPtr = reinterpret_cast<int*>(&instanceIndexBuffer_[0]);

	for (size_t index = 0; index < instancingUnitCount_; ++index)
	{
		//if (false == allInstancingUnits_[index].isRendering_)
		//{
		//	continue;
		//}

		{
			//Ʈ�����������ʹ� �����, ��������� �����ؾ� �ϹǷ� ���� ó��.
			allInstancingUnits_[index].transformData_.worldViewMatrix_
				= allInstancingUnits_[index].transformData_.worldWorldMatrix_ * _viewMatrix;

			allInstancingUnits_[index].transformData_.worldViewProjectionMatrix_
				= allInstancingUnits_[index].transformData_.worldViewMatrix_ * _projectionMatrix;

			//if (false == float4x4::IsInViewFrustum(
			//	allInstancingUnits_[index].transformData_.worldViewProjectionMatrix_,
			//	float4::Zero))
			//{
			//	//�̰� �ǹ̰� �ֳ�?
			//	continue;
			//}

			size_t transforDataSize = sizeof(TransformData);
			char* transformDataPtr
				= &shaderResourceHelper_.GetStructuredBufferSetter("Inst_TransformData")->originalData_[index * transforDataSize];

			int copyResult = memcpy_s(	//
				transformDataPtr,		//
				transforDataSize,		//
				&allInstancingUnits_[index].transformData_,	//
				transforDataSize		//
			);

			if (0 != copyResult)
			{
				MsgBoxAssert("Ʈ������������ ���� ����!");
				return;
			}
		}

		{
			//��Ʋ�󽺵����͵� ���� ó��.
			size_t atlasDataSize = sizeof(AtlasData);
			char* atlasDataPtr
				= &shaderResourceHelper_.GetStructuredBufferSetter("Inst_AtlasData")->originalData_[index * atlasDataSize];

			int copyResult = memcpy_s(	//
				atlasDataPtr,		//
				atlasDataSize,		//
				&allInstancingUnits_[index].atlasData_,	//
				atlasDataSize		//
			);

			if (0 != copyResult)
			{
				MsgBoxAssert("��Ʋ�󽺵����� ���� ����!");
				return;
			}
		}

		for (std::map<std::string, const void*>::iterator unitDataIter = allInstancingUnits_[index].data_.begin();
			unitDataIter != allInstancingUnits_[index].data_.end(); ++unitDataIter)
		{
			if (nullptr == unitDataIter->second)
			{
				MsgBoxAssertString(unitDataIter->first + ": ���̴��� ������� �� �����Ͱ� �ν��Ͻ� ���ֿ� �����ϴ�.");
				return;
			}

			//����ȭ���ۼ��ͷ� �� ���ֺ� ������ ����.
			for (std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator sBufferSetterIter = structuredBufferSetters.lower_bound(unitDataIter->first);
				sBufferSetterIter != structuredBufferSetters.upper_bound(unitDataIter->first); ++sBufferSetterIter) 
			{
			
				size_t originalDataSize = sBufferSetterIter->second.size_;
				//����ȭ���� ���Ͱ� ��� �ִ� originalData_�� ���� ũ��.

				char* originalDataPtr = &sBufferSetterIter->second.originalData_[index * originalDataSize];
				//����ȭ���� ���Ͱ� ��� �ִ� originalData_�� ������.

				int copyResult = memcpy_s(	//
					originalDataPtr,		//����ȭ���� ������ originalData_�� 
					originalDataSize,		//originalData_�� ���� ũ�⸸ŭ == �ν��Ͻ������� ����ִ� ������ ũ�⸸ŭ
					unitDataIter->second,	//�ν��Ͻ������� ����ִ� �����͸� �����Ѵ�.
					originalDataSize		//originalData_�� ���� ũ�⸸ŭ == �ν��Ͻ������� ����ִ� ������ ũ�⸸ŭ.
				);

				if (0 != copyResult)
				{
					MsgBoxAssert("�޸� ���� ����!");
					return;
				}
			}
		}

		*instanceIndexBufferPtr = static_cast<int>(index);
		instanceIndexBufferPtr += 1;
		//�ν��Ͻ��ε������ۿ� �ν��Ͻ� �ε����� ����ϰ� �ڷ� �Ѿ��.

		*instanceIndexBufferPtr = allInstancingUnits_[index].textureIndex_;
		instanceIndexBufferPtr += 1;
		//�ν��Ͻ��ε������ۿ� �ؽ�ó�迭 �ε����� ����ϰ� �ڷ� �Ѿ��.
	}



	instancingBuffer_->ChangeData(&instanceIndexBuffer_[0], instanceIndexBuffer_.size());
	shaderResourceHelper_.AllResourcesSetting();

	
	
	
	allInstancingUnits_[0].renderUnit_->RenderInstancing2(_deltaTime, instancingUnitCount_, instancingBuffer_);


}

