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
		MsgBoxAssertString(std::string(_structuredBufferName) + ": 그런 이름의 구조화 버퍼를 사용하지 않습니다.");
		//트랜스폼데이터, 아틀라스데이터를 링크시켜도 여기로 들어오는점 주의.
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
	//인스턴싱유닛이 가진 월드행렬에 카메라의 뷰행렬을 받아서 적용.

	this->transformData_.worldViewProjectionMatrix_ = this->transformData_.worldViewMatrix_ * _projectionMatrix;
	//투영행렬도 받아서 적용.

	size_t transformDataSize = sizeof(TransformData);	//한개 트랜스폼데이터 크기.

	int copyResult = memcpy_s(
		_transformDataPtr,
		transformDataSize,
		&this->transformData_,
		transformDataSize
	);
	//각각의 인스턴싱유닛들이 가진 트랜스폼데이터를 Inst_TransformData구조화버퍼 세터가 가진 오리지날데이터로 복사한다.
}

void GameEngineInstancingRenderer::InstancingUnit::UpdateAtlasData(char* _atlasDataPtr)
{
	const size_t atlasDataSize = sizeof(AtlasData);	//한개 아틀라스데이터 크기.

	int copyResult = memcpy_s(
		_atlasDataPtr,
		atlasDataSize,
		&this->atlasData_,
		atlasDataSize
	);
	//각각의 인스턴싱유닛들이 가진 아틀라스데이터를 Inst_AtlasData구조화버퍼 세터가 가진 오리지날데이터로 복사한다.
}

void GameEngineInstancingRenderer::InstancingUnit::UpdateLinkedData(std::multimap<std::string, GameEngineStructuredBufferSetter>& _structuredBufferSetters)
{
	for (std::map<std::string, const void*>::iterator unitDataIter = this->data_.begin();
		unitDataIter != this->data_.end(); ++unitDataIter)
	{
		//if (nullptr == unitDataIter->second)
		//{
		//	MsgBoxAssertString(unitDataIter->first + ": 셰이더로 보내기로 한 데이터가 인스턴싱 유닛에 없습니다.");
		//	return;
		//}

		if (nullptr == unitDataIter->second)
		{
			continue;
		}

		//이름이 맞는 구조화버퍼세터로 각 인스턴싱유닛들이 가진 나머지 데이터 전달.
		for (std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator sBufferSetterIter = _structuredBufferSetters.lower_bound(unitDataIter->first);
			sBufferSetterIter != _structuredBufferSetters.upper_bound(unitDataIter->first); ++sBufferSetterIter)
		{
			const size_t originalDataSize = sBufferSetterIter->second.size_;
			//구조화버퍼 세터가 들고 있는 originalData_의 단위 크기.

			char* originalDataPtr = &sBufferSetterIter->second.originalData_[this->unitIndex_ * originalDataSize];
			//구조화버퍼 세터가 들고 있는 originalData_의 포인터.

			int copyResult = memcpy_s(
				originalDataPtr,
				originalDataSize,
				unitDataIter->second,
				originalDataSize
			);
			//각각의 인스턴싱유닛들이 가진 나머지 데이터를 구조화버퍼 세터가 가진 오리지날데이터로 전부 복사한다.
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
	//인스턴스데이터버퍼에 텍스처배열의 컬러텍스처 인덱스를 기록한다.

	//char* instanceDataBufferPtr2 = &instanceDataBuffer_[index * instanceDataSize_ + colorTextureIndexSize];

	int copyResult2 = memcpy_s(
		_instanceDataBufferPtr2,
		sizeof(this->normalMapTextureIndex_),
		&this->normalMapTextureIndex_,
		sizeof(this->normalMapTextureIndex_)
	);
	//인스턴스데이터버퍼에 텍스처배열의 노말맵텍스처 인덱스를 기록한다.
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
		MsgBoxAssert("인스턴스 개수는 0이 될 수 없습니다.");
		return;
	}

	if (false == GameEngineMaterial::Find(_materialName)->GetVertexShader()->IsInstancing())
	{
		MsgBoxAssertString(std::string(_materialName) + ": 이 마테리얼의 버텍스셰이더는 인스턴싱 준비가 되어있지 않습니다.");
		return;
	}

	if (false == GameEngineMaterial::Find(_materialName)->GetPixelShader()->IsInstancing())
	{
		MsgBoxAssertString(std::string(_materialName) + ": 이 마테리얼의 픽셀셰이더는 인스턴싱 준비가 되어있지 않습니다.");
		return;
	}

	this->instancingUnitCount_ = _instancingUnitCount;
	//인스턴스별 렌더링 정보를 저장할 인스턴싱유닛의 개수 지정.

	this->isShadowRendering_ = _isShadowRendering;
	//그림자 렌더링 여부 저장.


	this->mesh_ = GameEngineMesh::Find(_meshName);
	this->material_ = GameEngineMaterial::Find(_materialName);
	this->inputLayout_ = GameEngineInputLayout::Create(
		this->mesh_->GetInputLayoutDesc(),
		this->material_->GetVertexShader()
	);
	//메쉬, 마테리얼, 인풋 레이아웃 세팅.

	
	instanceDataSize_ = static_cast<size_t>(this->mesh_->GetInputLayoutDesc().instanceDataSize_);
	//인스턴스별 인풋레이아웃 크기를 가져온다. 
	
	this->instancingBuffer_ = GameEngineInstancingBuffer::Create(instancingUnitCount_, instanceDataSize_);
	//instancingUnitCount_ * instanceDataSize크기의 인스턴싱버퍼 생성.

	instanceDataBuffer_.resize(instanceDataSize_ * instancingUnitCount_);
	//instancingUnitCount_ * instanceDataSize크기로 인스턴스데이터 버퍼 크기 조정.

	this->shaderResourceHelper_ = GameEngineShaderResourceHelper();
	this->shaderResourceHelper_.ShaderCheck(
		this->material_->GetVertexShader()->GetInst_VertexShader());
	this->shaderResourceHelper_.ShaderCheck(
		this->material_->GetPixelShader()->GetInst_PixelShader());
	//인스턴싱렌더러가 쓸 셰이더리소스헬퍼를 생성하고 
	// 위에서 지정한 마테리얼이 가진 인스턴싱용 정점셰이더와 픽셀셰이더가 필요로 하는 셰이더리소스를 
	// 디바이스 컨텍스트에 연결한다.
	
	std::multimap<std::string, GameEngineStructuredBufferSetter>& structuredBufferSetters
		= shaderResourceHelper_.GetStructuredBufferSetterMap();
	//셰이더리소스헬퍼에 등록된 구조화버퍼 세터를 전부 가져온다.

	for (std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator iter = structuredBufferSetters.begin();
		iter != structuredBufferSetters.end(); ++iter)
	{
		if (0 == iter->first.compare("INST_TRANSFORMDATA")
			|| 0 == iter->first.compare("INST_ATLASDATA"))
		{
			iter->second.Resize(instancingUnitCount_);
			continue;
		}
		//트랜스폼데이터, 아틀라스데이터는 따로 처리하게 했으므로 크기 조정만 하고 structuredBufferSetterNames_에는 등록하지 않는다.

		if (std::string::npos != iter->first.find("INST_"))
		{
			structuredBufferSetterNames_.insert(iter->first);
			//structuredBufferSetters의 모든 구조화버퍼 세터들 중 이름에 "INST_" 라는 문자열이 포함된 것들만 골라서 
			// structuredBufferSetterNames_에 이름을 등록한다.

			iter->second.Resize(instancingUnitCount_);
			//그 세터와 연결된 구조화버퍼를 생성하거나 크기를 조정한다.
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
	//instancingUnitCount_만큼의 인스턴싱유닛을 생성, 저장한다.
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
		//그림자 렌더링은 여기서 하지 않는다.
	}

	if (true == this->material_->GetPixelShader()->GetInst_PixelShader()->IsDeferredRendering())
	{
		return;
		//디퍼드 렌더링은 여기서 하지 않는다.
	}

	if (nullptr == this->mesh_)
	{
		MsgBoxAssert("메쉬가 없습니다. 렌더링을 할 수 없습니다.");
		return;
	}

	if (nullptr == this->inputLayout_)
	{
		MsgBoxAssert("인풋 레이아웃이 없습니다. 렌더링을 할 수 없습니다.");
		return;
	}

	if (nullptr == this->material_)
	{
		MsgBoxAssert("마테리얼이 없습니다. 렌더링을 할 수 없습니다.");
		return;
	}

	std::multimap<std::string, GameEngineStructuredBufferSetter>& structuredBufferSetters
		= shaderResourceHelper_.GetStructuredBufferSetterMap();
	//ShaderCheck()함수를 통해 미리 준비했던 구조화버퍼들을 전부 가져온다.

	//int* instanceDataBufferPtr = reinterpret_cast<int*>(&instanceDataBuffer_[0]);
	//인스턴스데이터버퍼 메모리의 시작 주소값을 받아온다.


	const static size_t transformDataSize = sizeof(TransformData);	//한개 트랜스폼데이터 크기.
	const static size_t atlasDataSize = sizeof(AtlasData);	//한개 아틀라스데이터 크기.

	for (size_t index = 0; index < instancingUnitCount_; ++index)
	{
		this->allInstancingUnits_[index].UpdateTransformData(
			_viewMatrix,
			_projectionMatrix,
			&this->shaderResourceHelper_.GetStructuredBufferSetter(
				"Inst_TransformData")->originalData_[index * transformDataSize]
		);
		//트랜스폼데이터는 뷰행렬, 투영행렬을 적용해야 하므로 따로 처리.

		this->allInstancingUnits_[index].UpdateAtlasData(
			&this->shaderResourceHelper_.GetStructuredBufferSetter(
				"Inst_AtlasData")->originalData_[index * atlasDataSize]
		);
		//아틀라스데이터도 따로 처리.

		this->allInstancingUnits_[index].UpdateLinkedData(structuredBufferSetters);

		const static size_t colorTextureIndexSize = sizeof(allInstancingUnits_[index].colorTextureIndex_);
		//const static size_t normalMapTextureIndexSize = sizeof(allInstancingUnits_[index].normalMapTextureIndex_);

		this->allInstancingUnits_[index].UpdateTextureIndex(
			&instanceDataBuffer_[index * instanceDataSize_],
			&instanceDataBuffer_[index * instanceDataSize_ + colorTextureIndexSize]
		);
	}

	instancingBuffer_->ChangeData(&instanceDataBuffer_[0], instanceDataBuffer_.size());
	//인스턴스데이터버퍼에 저장된 컬러텍스처 인덱스와 노말맵텍스처 인덱스를 인스턴싱버퍼로 복사한다.

	shaderResourceHelper_.AllResourcesSetting();
	//셰이더리소스헬퍼가 가진 모든 리소스들을 디바이스 컨텍스트에 연결한다.

	this->mesh_->SettingInstancing(this->instancingBuffer_);
	//메쉬가 가진 기본 정점정보와 함께 인스턴싱버퍼의 정보들도 디바이스 컨텍스트에 연결한다.

	this->inputLayout_->Set();
	GameEngineDevice::GetDC()->IASetPrimitiveTopology(topology_);
	this->material_->SettingInstancing2();

	this->mesh_->RenderInstancing(this->instancingUnitCount_);
	//넣어준 인스턴스 개수만큼 기본 도형을 그린다.

	shaderResourceHelper_.AllResourcesReset();
}

void GameEngineInstancingRenderer::DeferredRender(float _deltaTime, const float4x4& _viewMatrix, const float4x4& _projectionMatrix)
{
	if (true == this->isShadowRendering_)
	{
		return;
		//그림자 렌더링은 여기서 하지 않는다.
	}

	if (false == this->material_->GetPixelShader()->GetInst_PixelShader()->IsDeferredRendering())
	{
		return;
		//포워드 렌더링은 여기서 하지 않는다.
	}

	if (nullptr == this->mesh_)
	{
		MsgBoxAssert("메쉬가 없습니다. 렌더링을 할 수 없습니다.");
		return;
	}

	if (nullptr == this->inputLayout_)
	{
		MsgBoxAssert("인풋 레이아웃이 없습니다. 렌더링을 할 수 없습니다.");
		return;
	}

	if (nullptr == this->material_)
	{
		MsgBoxAssert("마테리얼이 없습니다. 렌더링을 할 수 없습니다.");
		return;
	}

	std::multimap<std::string, GameEngineStructuredBufferSetter>& structuredBufferSetters
		= shaderResourceHelper_.GetStructuredBufferSetterMap();

	const static size_t transformDataSize = sizeof(TransformData);	//한개 트랜스폼데이터 크기.
	const static size_t atlasDataSize = sizeof(AtlasData);	//한개 아틀라스데이터 크기.

	for (size_t index = 0; index < instancingUnitCount_; ++index)
	{
		this->allInstancingUnits_[index].UpdateTransformData(
			_viewMatrix,
			_projectionMatrix,
			&this->shaderResourceHelper_.GetStructuredBufferSetter(
				"Inst_TransformData")->originalData_[index * transformDataSize]
		);
		//트랜스폼데이터는 뷰행렬, 투영행렬을 적용해야 하므로 따로 처리.

		this->allInstancingUnits_[index].UpdateAtlasData(
			&this->shaderResourceHelper_.GetStructuredBufferSetter(
				"Inst_AtlasData")->originalData_[index * atlasDataSize]
		);
		//아틀라스데이터도 따로 처리.

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
		//일반 렌더링은 여기서 하지 않는다.
	}

	if (true == this->material_->GetPixelShader()->GetInst_PixelShader()->IsDeferredRendering())
	{
		MsgBoxAssert("그림자 렌더링에 디퍼드 셰이더는 필요 없습니다.");
		return;
		//디퍼드 렌더링은 여기서 하지 않는다.
	}

	if (nullptr == this->mesh_)
	{
		MsgBoxAssert("메쉬가 없습니다. 렌더링을 할 수 없습니다.");
		return;
	}

	if (nullptr == this->inputLayout_)
	{
		MsgBoxAssert("인풋 레이아웃이 없습니다. 렌더링을 할 수 없습니다.");
		return;
	}

	if (nullptr == this->material_)
	{
		MsgBoxAssert("마테리얼이 없습니다. 렌더링을 할 수 없습니다.");
		return;
	}

	std::multimap<std::string, GameEngineStructuredBufferSetter>& structuredBufferSetters
		= shaderResourceHelper_.GetStructuredBufferSetterMap();

	const static size_t transformDataSize = sizeof(TransformData);	//한개 트랜스폼데이터 크기.
	const static size_t atlasDataSize = sizeof(AtlasData);	//한개 아틀라스데이터 크기.

	for (size_t index = 0; index < instancingUnitCount_; ++index)
	{
		this->allInstancingUnits_[index].UpdateTransformData(
			_viewMatrix,
			_projectionMatrix,
			&shaderResourceHelper_.GetStructuredBufferSetter(
				"Inst_TransformData")->originalData_[index * transformDataSize]
		);
		//트랜스폼데이터는 뷰행렬, 투영행렬을 적용해야 하므로 따로 처리.

		this->allInstancingUnits_[index].UpdateAtlasData(
			&shaderResourceHelper_.GetStructuredBufferSetter(
				"Inst_AtlasData")->originalData_[index * atlasDataSize]
		);
		//아틀라스데이터도 따로 처리.

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
