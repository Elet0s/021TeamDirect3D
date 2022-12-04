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
}

void GameEngineInstancingRenderer::InstancingUnit::Link(const std::string_view& _name, const void* _data)
{
	std::string uppercaseDataName = GameEngineString::ToUpperReturn(_name);

	if (data_.end() == data_.find(uppercaseDataName))
	{
		MsgBoxAssertString(std::string(_name) + ": �׷� �̸��� �ν��Ͻ� �����Ͱ� �������� �ʽ��ϴ�.");
		return;
	}
	else
	{
		data_.find(uppercaseDataName)->second = _data;
	}
}

void GameEngineInstancingRenderer::InstancingUnit::SetTransformData(const TransformData& _transformData)
{
	this->transformData_ = _transformData;
}

GameEngineInstancingRenderer::GameEngineInstancingRenderer(): instancingUnitCount_(0)
{
}

GameEngineInstancingRenderer::~GameEngineInstancingRenderer()
{
}

void GameEngineInstancingRenderer::Initialize(
	size_t _instancingUnitCount,
	const std::string_view& _meshName /*= "Rect"*/,
	const std::string_view& _materialName /*= "Test"*/
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


	//�ν��Ͻ� ���� ũ��.
	UINT instancingSize = GameEngineMesh::Find(_meshName)->GetInputLayoutDesc().instancingSize_;

	this->instancingBuffer_ = GameEngineInstancingBuffer::Create(instancingUnitCount_, instancingSize);
	//instancingUnitCount_ * instancingSizeũ���� �ν��Ͻ̹��� ����.

	rowIndexBuffer_.resize(static_cast<size_t>(instancingSize) * instancingUnitCount_);
	//instancingUnitCount_ * instancingSizeũ��� �ο��ε��� ���� ũ�� ����.



	this->shaderResourceHelper_ = GameEngineShaderResourceHelper();
	this->shaderResourceHelper_.ShaderCheck(
		GameEngineMaterial::Find(_materialName)->GetVertexShader()->GetInst_VertexShader());
	//this->shaderResourceHelper_.ShaderCheck(
	//	GameEngineMaterial::Find(_materialName)->GetPixelShader());
	this->shaderResourceHelper_.ShaderCheck(
		GameEngineMaterial::Find(_materialName)->GetPixelShader()->GetInst_PixelShader());
	//_materialName�� �̸��� ���� ���׸����� ��� ������ �����͸� �´� ���̴��� �����Ų��.


	
	std::multimap<std::string, GameEngineStructuredBufferSetter>& structuredBufferSetters
		= shaderResourceHelper_.GetStructuredBufferSetterMap();
	//���̴����ҽ����ۿ� ��ϵ� ����ȭ���� ���͸� ���� �����´�.



	for (std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator iter = structuredBufferSetters.begin();
		iter != structuredBufferSetters.end(); ++iter)
	{
		//Ʈ�����������ʹ� ���� ó���ؾ��ϹǷ� ũ�� ������ �ϰ� structuredBufferSetterNames_�� ������� �ʴ´�.
		if (std::string::npos != iter->first.find("INST_TRANSFORMDATA"))
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

	this->instancingUnits_.reserve(instancingUnitCount_);
	for (size_t i = 0; i < instancingUnitCount_; ++i)
	{
		instancingUnits_.push_back(
			GameEngineInstancingRenderer::InstancingUnit::InstancingUnit(
				this->structuredBufferSetterNames_,
				_meshName,
				_materialName
			)
		);
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

	int* rowIndexBufferIndex = reinterpret_cast<int*>(&rowIndexBuffer_[0]);
	int rowIndex = 0;

	//for (InstancingUnit& instancingUnit : instancingUnits_)
	for (size_t index = 0; index < instancingUnitCount_; ++index)
	{
		{
			//Ʈ�����������ʹ� �����, ��������� �����ؾ� �ϹǷ� ���� ó��.
			instancingUnits_[index].transformData_.worldViewProjectionMatrix_
				= instancingUnits_[index].transformData_.worldWorldMatrix_ * _viewMatrix * _projectionMatrix;


			//���������� �ø� �ִ´ٸ� ���⿡.


			size_t transformDataSize = shaderResourceHelper_.GetStructuredBufferSetter("Inst_TransformData")->size_;
			char* transformDataPtr = &shaderResourceHelper_.GetStructuredBufferSetter("Inst_TransformData")->originalData_[index * transformDataSize];
		
			int copyResult = memcpy_s(	//
				transformDataPtr,		//
				transformDataSize,		//
				&instancingUnits_[index].transformData_,	//
				transformDataSize		//
			);

			if (0 != copyResult)
			{
				MsgBoxAssert("Ʈ������������ ���� ����!");
				return;
			}
		}

		for (std::map<std::string, const void*>::iterator unitDataIter = instancingUnits_[index].data_.begin();
			unitDataIter != instancingUnits_[index].data_.end(); ++unitDataIter)
		{
			//����ȭ���ۼ��ͷ� �� ���ֺ� ������ ����.
			for (std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator sBufferSetterIter = structuredBufferSetters.lower_bound(unitDataIter->first);
				sBufferSetterIter != structuredBufferSetters.upper_bound(unitDataIter->first); ++sBufferSetterIter) {
				{
					size_t originalDataSize = sBufferSetterIter->second.size_;
					//����ȭ���� ���Ͱ� ��� �ִ� originalData_�� ���� ũ��.

					char* originalDataPtr = &sBufferSetterIter->second.originalData_[rowIndex * originalDataSize];
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
		}

		*rowIndexBufferIndex = rowIndex;
		++rowIndex;
		rowIndexBufferIndex += 1;
		//�ο��ε������ۿ� �ε����� ����ϰ� �ڷ� �Ѿ��.
	}

	instancingBuffer_->ChangeData(&rowIndexBuffer_[0], rowIndexBuffer_.size());
	shaderResourceHelper_.AllResourcesSetting();

	instancingUnits_[0].renderUnit_->RenderInstancing2(_deltaTime, instancingUnitCount_, instancingBuffer_);


}