#include "PreCompile.h"
#include "GameEngineInstancingRenderer.h"
#include "GameEngineInputLayout.h"
#include "GameEngineDevice.h"
#include "GameEngineInstancingBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineVertexes.h"


GameEngineInstancingRenderer::InstancingUnit::InstancingUnit(
	const std::multiset<std::string>& _structuredBufferSetterNames,
	size_t _unitIndex
): unitIndex_(_unitIndex),
colorTextureIndex_(0),
normalMapTextureIndex_(-1)
{
	for (const std::string& name : _structuredBufferSetterNames)
	{
		data_.insert(std::make_pair(name, nullptr));
	}
}

void GameEngineInstancingRenderer::InstancingUnit::Link(
	const std::string_view& _structuredBufferName,
	const void* _data
)
{
	std::string uppercaseDataName = GameEngineString::ToUpperReturn(_structuredBufferName);

	if (data_.end() == data_.find(uppercaseDataName))
	{
		MsgBoxAssertString(std::string(_structuredBufferName) + ": �׷� �̸��� ����ȭ ���۸� ������� �ʽ��ϴ�.");
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

void GameEngineInstancingRenderer::InstancingUnit::SetColorTextureIndex(unsigned int _colorTextureIndex)
{
	colorTextureIndex_ = _colorTextureIndex;
}

void GameEngineInstancingRenderer::InstancingUnit::SetNormalMapTextureIndex(unsigned int _normalMapTextureIndex)
{
	normalMapTextureIndex_ = _normalMapTextureIndex;
}

void GameEngineInstancingRenderer::InstancingUnit::SwitchLeftToRight()
{
	this->transformData_.worldScaleVector_.x = -this->transformData_.worldScaleVector_.x;
	this->transformData_.localScaleMatrix_.Scale(this->transformData_.worldScaleVector_);
	CalWorldWorldMatrix();
}

void GameEngineInstancingRenderer::InstancingUnit::CalWorldWorldMatrix()
{
	this->transformData_.worldWorldMatrix_
		= this->transformData_.localScaleMatrix_ 
		* this->transformData_.localRotationMatrix_ 
		* this->transformData_.localPositionMatrix_;
}

void GameEngineInstancingRenderer::InstancingUnit::UpdateTransformData(
	const float4x4& _viewMatrix,
	const float4x4& _projectionMatrix,
	char* _transformDataPtr
)
{
	this->transformData_.worldViewMatrix_ = this->transformData_.worldWorldMatrix_ * _viewMatrix;
	//�ν��Ͻ������� ���� ������Ŀ� ī�޶��� ������� �޾Ƽ� ����.

	this->transformData_.worldViewProjectionMatrix_ = this->transformData_.worldViewMatrix_ * _projectionMatrix;
	//������ĵ� �޾Ƽ� ����.

	size_t transformDataSize = sizeof(TransformData);	//�Ѱ� Ʈ������������ ũ��.

	int copyResult = memcpy_s(
		_transformDataPtr,
		transformDataSize,
		&this->transformData_,
		transformDataSize
	);
	//������ �ν��Ͻ����ֵ��� ���� Ʈ�����������͸� Inst_TransformData����ȭ���� ���Ͱ� ���� �������������ͷ� �����Ѵ�.
}

void GameEngineInstancingRenderer::InstancingUnit::UpdateAtlasData(char* _atlasDataPtr)
{
	const size_t atlasDataSize = sizeof(AtlasData);	//�Ѱ� ��Ʋ�󽺵����� ũ��.

	int copyResult = memcpy_s(
		_atlasDataPtr,
		atlasDataSize,
		&this->atlasData_,
		atlasDataSize
	);
	//������ �ν��Ͻ����ֵ��� ���� ��Ʋ�󽺵����͸� Inst_AtlasData����ȭ���� ���Ͱ� ���� �������������ͷ� �����Ѵ�.
}

void GameEngineInstancingRenderer::InstancingUnit::UpdateLinkedData(std::multimap<std::string, GameEngineStructuredBufferSetter>& _structuredBufferSetters)
{
	for (std::map<std::string, const void*>::iterator unitDataIter = this->data_.begin();
		unitDataIter != this->data_.end(); ++unitDataIter)
	{
		//if (nullptr == unitDataIter->second)
		//{
		//	MsgBoxAssertString(unitDataIter->first + ": ���̴��� ������� �� �����Ͱ� �ν��Ͻ� ���ֿ� �����ϴ�.");
		//	return;
		//}

		if (nullptr == unitDataIter->second)
		{
			continue;
		}

		//�̸��� �´� ����ȭ���ۼ��ͷ� �� �ν��Ͻ����ֵ��� ���� ������ ������ ����.
		for (std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator sBufferSetterIter = _structuredBufferSetters.lower_bound(unitDataIter->first);
			sBufferSetterIter != _structuredBufferSetters.upper_bound(unitDataIter->first); ++sBufferSetterIter)
		{
			const size_t originalDataSize = sBufferSetterIter->second.size_;
			//����ȭ���� ���Ͱ� ��� �ִ� originalData_�� ���� ũ��.

			char* originalDataPtr = &sBufferSetterIter->second.originalData_[this->unitIndex_ * originalDataSize];
			//����ȭ���� ���Ͱ� ��� �ִ� originalData_�� ������.

			int copyResult = memcpy_s(
				originalDataPtr,
				originalDataSize,
				unitDataIter->second,
				originalDataSize
			);
			//������ �ν��Ͻ����ֵ��� ���� ������ �����͸� ����ȭ���� ���Ͱ� ���� �������������ͷ� ���� �����Ѵ�.
		}
	}
}

void GameEngineInstancingRenderer::InstancingUnit::UpdateTextureIndex(char* _instanceDataBufferPtr1, char* _instanceDataBufferPtr2)
{
	//char* instanceDataBufferPtr1 = &instanceDataBuffer_[index * instanceDataSize_];

	int copyResult1 = memcpy_s(
		_instanceDataBufferPtr1,
		sizeof(this->colorTextureIndex_),
		&this->colorTextureIndex_,
		sizeof(this->colorTextureIndex_)
	);
	//�ν��Ͻ������͹��ۿ� �ؽ�ó�迭�� �÷��ؽ�ó �ε����� ����Ѵ�.

	//char* instanceDataBufferPtr2 = &instanceDataBuffer_[index * instanceDataSize_ + colorTextureIndexSize];

	int copyResult2 = memcpy_s(
		_instanceDataBufferPtr2,
		sizeof(this->normalMapTextureIndex_),
		&this->normalMapTextureIndex_,
		sizeof(this->normalMapTextureIndex_)
	);
	//�ν��Ͻ������͹��ۿ� �ؽ�ó�迭�� �븻���ؽ�ó �ε����� ����Ѵ�.
}

GameEngineInstancingRenderer::GameEngineInstancingRenderer()
	: isShadowRendering_(false),
	instancingUnitCount_(0),
	mesh_(nullptr),
	inputLayout_(nullptr),
	material_(nullptr),
	topology_(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST),
	instancingBuffer_(nullptr),
	instanceDataSize_(0)
{
}

GameEngineInstancingRenderer::~GameEngineInstancingRenderer()
{
}

void GameEngineInstancingRenderer::Initialize(
	size_t _instancingUnitCount,
	const std::string_view& _meshName,
	const std::string_view& _materialName,
	bool _isShadowRendering /*= false*/
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
	//�ν��Ͻ��� ������ ������ ������ �ν��Ͻ������� ���� ����.

	this->isShadowRendering_ = _isShadowRendering;
	//�׸��� ������ ���� ����.


	this->mesh_ = GameEngineMesh::Find(_meshName);
	this->material_ = GameEngineMaterial::Find(_materialName);
	this->inputLayout_ = GameEngineInputLayout::Create(
		this->mesh_->GetInputLayoutDesc(),
		this->material_->GetVertexShader()
	);
	//�޽�, ���׸���, ��ǲ ���̾ƿ� ����.

	
	instanceDataSize_ = static_cast<size_t>(this->mesh_->GetInputLayoutDesc().instanceDataSize_);
	//�ν��Ͻ��� ��ǲ���̾ƿ� ũ�⸦ �����´�. 
	
	this->instancingBuffer_ = GameEngineInstancingBuffer::Create(instancingUnitCount_, instanceDataSize_);
	//instancingUnitCount_ * instanceDataSizeũ���� �ν��Ͻ̹��� ����.

	instanceDataBuffer_.resize(instanceDataSize_ * instancingUnitCount_);
	//instancingUnitCount_ * instanceDataSizeũ��� �ν��Ͻ������� ���� ũ�� ����.

	this->shaderResourceHelper_ = GameEngineShaderResourceHelper();
	this->shaderResourceHelper_.ShaderCheck(
		this->material_->GetVertexShader()->GetInst_VertexShader());
	this->shaderResourceHelper_.ShaderCheck(
		this->material_->GetPixelShader()->GetInst_PixelShader());
	//�ν��Ͻ̷������� �� ���̴����ҽ����۸� �����ϰ� 
	// ������ ������ ���׸����� ���� �ν��Ͻ̿� �������̴��� �ȼ����̴��� �ʿ�� �ϴ� ���̴����ҽ��� 
	// ����̽� ���ؽ�Ʈ�� �����Ѵ�.
	
	std::multimap<std::string, GameEngineStructuredBufferSetter>& structuredBufferSetters
		= shaderResourceHelper_.GetStructuredBufferSetterMap();
	//���̴����ҽ����ۿ� ��ϵ� ����ȭ���� ���͸� ���� �����´�.

	for (std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator iter = structuredBufferSetters.begin();
		iter != structuredBufferSetters.end(); ++iter)
	{
		if (0 == iter->first.compare("INST_TRANSFORMDATA")
			|| 0 == iter->first.compare("INST_ATLASDATA"))
		{
			iter->second.Resize(instancingUnitCount_);
			continue;
		}
		//Ʈ������������, ��Ʋ�󽺵����ʹ� ���� ó���ϰ� �����Ƿ� ũ�� ������ �ϰ� structuredBufferSetterNames_���� ������� �ʴ´�.

		if (std::string::npos != iter->first.find("INST_"))
		{
			structuredBufferSetterNames_.insert(iter->first);
			//structuredBufferSetters�� ��� ����ȭ���� ���͵� �� �̸��� "INST_" ��� ���ڿ��� ���Ե� �͵鸸 ��� 
			// structuredBufferSetterNames_�� �̸��� ����Ѵ�.

			iter->second.Resize(instancingUnitCount_);
			//�� ���Ϳ� ����� ����ȭ���۸� �����ϰų� ũ�⸦ �����Ѵ�.
		}
	}

	this->allInstancingUnits_.reserve(instancingUnitCount_);
	for (size_t i = 0; i < instancingUnitCount_; ++i)
	{
		allInstancingUnits_.push_back(
			GameEngineInstancingRenderer::InstancingUnit::InstancingUnit(
				this->structuredBufferSetterNames_,
				i
			)
		);
	}
	//instancingUnitCount_��ŭ�� �ν��Ͻ������� ����, �����Ѵ�.
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
	if (true == isShadowRendering_)
	{
		return;
		//�׸��� �������� ���⼭ ���� �ʴ´�.
	}

	if (true == this->material_->GetPixelShader()->GetInst_PixelShader()->IsDeferredRendering())
	{
		return;
		//���۵� �������� ���⼭ ���� �ʴ´�.
	}

	if (nullptr == this->mesh_)
	{
		MsgBoxAssert("�޽��� �����ϴ�. �������� �� �� �����ϴ�.");
		return;
	}

	if (nullptr == this->inputLayout_)
	{
		MsgBoxAssert("��ǲ ���̾ƿ��� �����ϴ�. �������� �� �� �����ϴ�.");
		return;
	}

	if (nullptr == this->material_)
	{
		MsgBoxAssert("���׸����� �����ϴ�. �������� �� �� �����ϴ�.");
		return;
	}

	std::multimap<std::string, GameEngineStructuredBufferSetter>& structuredBufferSetters
		= shaderResourceHelper_.GetStructuredBufferSetterMap();
	//ShaderCheck()�Լ��� ���� �̸� �غ��ߴ� ����ȭ���۵��� ���� �����´�.

	//int* instanceDataBufferPtr = reinterpret_cast<int*>(&instanceDataBuffer_[0]);
	//�ν��Ͻ������͹��� �޸��� ���� �ּҰ��� �޾ƿ´�.


	const static size_t transformDataSize = sizeof(TransformData);	//�Ѱ� Ʈ������������ ũ��.
	const static size_t atlasDataSize = sizeof(AtlasData);	//�Ѱ� ��Ʋ�󽺵����� ũ��.

	for (size_t index = 0; index < instancingUnitCount_; ++index)
	{
		this->allInstancingUnits_[index].UpdateTransformData(
			_viewMatrix,
			_projectionMatrix,
			&this->shaderResourceHelper_.GetStructuredBufferSetter(
				"Inst_TransformData")->originalData_[index * transformDataSize]
		);
		//Ʈ�����������ʹ� �����, ��������� �����ؾ� �ϹǷ� ���� ó��.

		this->allInstancingUnits_[index].UpdateAtlasData(
			&this->shaderResourceHelper_.GetStructuredBufferSetter(
				"Inst_AtlasData")->originalData_[index * atlasDataSize]
		);
		//��Ʋ�󽺵����͵� ���� ó��.

		this->allInstancingUnits_[index].UpdateLinkedData(structuredBufferSetters);

		const static size_t colorTextureIndexSize = sizeof(allInstancingUnits_[index].colorTextureIndex_);
		//const static size_t normalMapTextureIndexSize = sizeof(allInstancingUnits_[index].normalMapTextureIndex_);

		this->allInstancingUnits_[index].UpdateTextureIndex(
			&instanceDataBuffer_[index * instanceDataSize_],
			&instanceDataBuffer_[index * instanceDataSize_ + colorTextureIndexSize]
		);
	}

	instancingBuffer_->ChangeData(&instanceDataBuffer_[0], instanceDataBuffer_.size());
	//�ν��Ͻ������͹��ۿ� ����� �÷��ؽ�ó �ε����� �븻���ؽ�ó �ε����� �ν��Ͻ̹��۷� �����Ѵ�.

	shaderResourceHelper_.AllResourcesSetting();
	//���̴����ҽ����۰� ���� ��� ���ҽ����� ����̽� ���ؽ�Ʈ�� �����Ѵ�.

	this->mesh_->SettingInstancing(this->instancingBuffer_);
	//�޽��� ���� �⺻ ���������� �Բ� �ν��Ͻ̹����� �����鵵 ����̽� ���ؽ�Ʈ�� �����Ѵ�.

	this->inputLayout_->Set();
	GameEngineDevice::GetDC()->IASetPrimitiveTopology(topology_);
	this->material_->SettingInstancing2();

	this->mesh_->RenderInstancing(this->instancingUnitCount_);
	//�־��� �ν��Ͻ� ������ŭ �⺻ ������ �׸���.

	shaderResourceHelper_.AllResourcesReset();
}

void GameEngineInstancingRenderer::DeferredRender(float _deltaTime, const float4x4& _viewMatrix, const float4x4& _projectionMatrix)
{
	if (true == this->isShadowRendering_)
	{
		return;
		//�׸��� �������� ���⼭ ���� �ʴ´�.
	}

	if (false == this->material_->GetPixelShader()->GetInst_PixelShader()->IsDeferredRendering())
	{
		return;
		//������ �������� ���⼭ ���� �ʴ´�.
	}

	if (nullptr == this->mesh_)
	{
		MsgBoxAssert("�޽��� �����ϴ�. �������� �� �� �����ϴ�.");
		return;
	}

	if (nullptr == this->inputLayout_)
	{
		MsgBoxAssert("��ǲ ���̾ƿ��� �����ϴ�. �������� �� �� �����ϴ�.");
		return;
	}

	if (nullptr == this->material_)
	{
		MsgBoxAssert("���׸����� �����ϴ�. �������� �� �� �����ϴ�.");
		return;
	}

	std::multimap<std::string, GameEngineStructuredBufferSetter>& structuredBufferSetters
		= shaderResourceHelper_.GetStructuredBufferSetterMap();

	const static size_t transformDataSize = sizeof(TransformData);	//�Ѱ� Ʈ������������ ũ��.
	const static size_t atlasDataSize = sizeof(AtlasData);	//�Ѱ� ��Ʋ�󽺵����� ũ��.

	for (size_t index = 0; index < instancingUnitCount_; ++index)
	{
		this->allInstancingUnits_[index].UpdateTransformData(
			_viewMatrix,
			_projectionMatrix,
			&this->shaderResourceHelper_.GetStructuredBufferSetter(
				"Inst_TransformData")->originalData_[index * transformDataSize]
		);
		//Ʈ�����������ʹ� �����, ��������� �����ؾ� �ϹǷ� ���� ó��.

		this->allInstancingUnits_[index].UpdateAtlasData(
			&this->shaderResourceHelper_.GetStructuredBufferSetter(
				"Inst_AtlasData")->originalData_[index * atlasDataSize]
		);
		//��Ʋ�󽺵����͵� ���� ó��.

		this->allInstancingUnits_[index].UpdateLinkedData(structuredBufferSetters);

		const static size_t colorTextureIndexSize = sizeof(allInstancingUnits_[index].colorTextureIndex_);
		//const static size_t normalMapTextureIndexSize = sizeof(allInstancingUnits_[index].normalMapTextureIndex_);

		this->allInstancingUnits_[index].UpdateTextureIndex(
			&instanceDataBuffer_[index * instanceDataSize_],
			&instanceDataBuffer_[index * instanceDataSize_ + colorTextureIndexSize]
		);
	}

	instancingBuffer_->ChangeData(&instanceDataBuffer_[0], instanceDataBuffer_.size());
	shaderResourceHelper_.AllResourcesSetting();

	this->mesh_->SettingInstancing(this->instancingBuffer_);
	this->inputLayout_->Set();
	GameEngineDevice::GetDC()->IASetPrimitiveTopology(topology_);
	this->material_->SettingInstancing2();

	this->mesh_->RenderInstancing(this->instancingUnitCount_);
	shaderResourceHelper_.AllResourcesReset();
}

void GameEngineInstancingRenderer::RenderShadow(float _deltaTime, const float4x4& _viewMatrix, const float4x4& _projectionMatrix)
{
	if (false == isShadowRendering_)
	{
		return;
		//�Ϲ� �������� ���⼭ ���� �ʴ´�.
	}

	if (true == this->material_->GetPixelShader()->GetInst_PixelShader()->IsDeferredRendering())
	{
		MsgBoxAssert("�׸��� �������� ���۵� ���̴��� �ʿ� �����ϴ�.");
		return;
		//���۵� �������� ���⼭ ���� �ʴ´�.
	}

	if (nullptr == this->mesh_)
	{
		MsgBoxAssert("�޽��� �����ϴ�. �������� �� �� �����ϴ�.");
		return;
	}

	if (nullptr == this->inputLayout_)
	{
		MsgBoxAssert("��ǲ ���̾ƿ��� �����ϴ�. �������� �� �� �����ϴ�.");
		return;
	}

	if (nullptr == this->material_)
	{
		MsgBoxAssert("���׸����� �����ϴ�. �������� �� �� �����ϴ�.");
		return;
	}

	std::multimap<std::string, GameEngineStructuredBufferSetter>& structuredBufferSetters
		= shaderResourceHelper_.GetStructuredBufferSetterMap();

	const static size_t transformDataSize = sizeof(TransformData);	//�Ѱ� Ʈ������������ ũ��.
	const static size_t atlasDataSize = sizeof(AtlasData);	//�Ѱ� ��Ʋ�󽺵����� ũ��.

	for (size_t index = 0; index < instancingUnitCount_; ++index)
	{
		this->allInstancingUnits_[index].UpdateTransformData(
			_viewMatrix,
			_projectionMatrix,
			&shaderResourceHelper_.GetStructuredBufferSetter(
				"Inst_TransformData")->originalData_[index * transformDataSize]
		);
		//Ʈ�����������ʹ� �����, ��������� �����ؾ� �ϹǷ� ���� ó��.

		this->allInstancingUnits_[index].UpdateAtlasData(
			&shaderResourceHelper_.GetStructuredBufferSetter(
				"Inst_AtlasData")->originalData_[index * atlasDataSize]
		);
		//��Ʋ�󽺵����͵� ���� ó��.

		this->allInstancingUnits_[index].UpdateLinkedData(structuredBufferSetters);

		const static size_t colorTextureIndexSize = sizeof(allInstancingUnits_[index].colorTextureIndex_);
		//const static size_t normalMapTextureIndexSize = sizeof(allInstancingUnits_[index].normalMapTextureIndex_);

		this->allInstancingUnits_[index].UpdateTextureIndex(
			&instanceDataBuffer_[index * instanceDataSize_],
			&instanceDataBuffer_[index * instanceDataSize_ + colorTextureIndexSize]
		);
	}

	instancingBuffer_->ChangeData(&instanceDataBuffer_[0], instanceDataBuffer_.size());
	shaderResourceHelper_.AllResourcesSetting();

	this->mesh_->SettingInstancing(this->instancingBuffer_);
	this->inputLayout_->Set();
	GameEngineDevice::GetDC()->IASetPrimitiveTopology(topology_);
	this->material_->SettingInstancing2();

	this->mesh_->RenderInstancing(this->instancingUnitCount_);
	shaderResourceHelper_.AllResourcesReset();
}
