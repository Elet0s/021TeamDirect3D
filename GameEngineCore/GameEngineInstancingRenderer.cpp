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
		MsgBoxAssertString(std::string(_name) + ": 그런 이름의 인스턴싱 데이터가 존재하지 않습니다.");
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


	//인스턴싱 단위 크기.
	UINT instancingSize = GameEngineMesh::Find(_meshName)->GetInputLayoutDesc().instancingSize_;

	this->instancingBuffer_ = GameEngineInstancingBuffer::Create(instancingUnitCount_, instancingSize);
	//instancingUnitCount_ * instancingSize크기의 인스턴싱버퍼 생성.

	rowIndexBuffer_.resize(static_cast<size_t>(instancingSize) * instancingUnitCount_);
	//instancingUnitCount_ * instancingSize크기로 로우인덱스 버퍼 크기 조정.



	this->shaderResourceHelper_ = GameEngineShaderResourceHelper();
	this->shaderResourceHelper_.ShaderCheck(
		GameEngineMaterial::Find(_materialName)->GetVertexShader()->GetInst_VertexShader());
	//this->shaderResourceHelper_.ShaderCheck(
	//	GameEngineMaterial::Find(_materialName)->GetPixelShader());
	this->shaderResourceHelper_.ShaderCheck(
		GameEngineMaterial::Find(_materialName)->GetPixelShader()->GetInst_PixelShader());
	//_materialName의 이름을 가진 마테리얼의 모든 렌더링 데이터를 맞는 셰이더에 연결시킨다.


	
	std::multimap<std::string, GameEngineStructuredBufferSetter>& structuredBufferSetters
		= shaderResourceHelper_.GetStructuredBufferSetterMap();
	//셰이더리소스헬퍼에 등록된 구조화버퍼 세터를 전부 가져온다.



	for (std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator iter = structuredBufferSetters.begin();
		iter != structuredBufferSetters.end(); ++iter)
	{
		//트랜스폼데이터는 따로 처리해야하므로 크기 조정만 하고 structuredBufferSetterNames_에 등록하지 않는다.
		if (std::string::npos != iter->first.find("INST_TRANSFORMDATA"))
		{
			iter->second.Resize(instancingUnitCount_);
			continue;
		}

		if (std::string::npos != iter->first.find("INST_"))
		{
			//structuredBufferSetters의 모든 구조화버퍼 세터들 중 이름에 "INST_" 라는 문자열이 포함된 것들만 골라서 
			// structuredBufferSetterNames_에 이름을 등록한다.
			structuredBufferSetterNames_.insert(iter->first);

			//그 세터와 연결된 구조화버퍼를 생성하거나 크기를 조정한다.
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
			//트랜스폼데이터는 뷰행렬, 투영행렬을 적용해야 하므로 따로 처리.
			instancingUnits_[index].transformData_.worldViewProjectionMatrix_
				= instancingUnits_[index].transformData_.worldWorldMatrix_ * _viewMatrix * _projectionMatrix;


			//뷰프러스텀 컬링 넣는다면 여기에.


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
				MsgBoxAssert("트랜스폼데이터 복사 실패!");
				return;
			}
		}

		for (std::map<std::string, const void*>::iterator unitDataIter = instancingUnits_[index].data_.begin();
			unitDataIter != instancingUnits_[index].data_.end(); ++unitDataIter)
		{
			//구조화버퍼세터로 각 유닛별 데이터 전달.
			for (std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator sBufferSetterIter = structuredBufferSetters.lower_bound(unitDataIter->first);
				sBufferSetterIter != structuredBufferSetters.upper_bound(unitDataIter->first); ++sBufferSetterIter) {
				{
					size_t originalDataSize = sBufferSetterIter->second.size_;
					//구조화버퍼 세터가 들고 있는 originalData_의 단위 크기.

					char* originalDataPtr = &sBufferSetterIter->second.originalData_[rowIndex * originalDataSize];
					//구조화버퍼 세터가 들고 있는 originalData_의 포인터.

					int copyResult = memcpy_s(	//
						originalDataPtr,		//구조화버퍼 세터의 originalData_로 
						originalDataSize,		//originalData_의 단위 크기만큼 == 인스턴싱유닛이 들고있는 데이터 크기만큼
						unitDataIter->second,	//인스턴싱유닛이 들고있는 데이터를 복사한다.
						originalDataSize		//originalData_의 단위 크기만큼 == 인스턴싱유닛이 들고있는 데이터 크기만큼.
					);

					if (0 != copyResult)
					{
						MsgBoxAssert("메모리 복사 실패!");
						return;
					}
				}
			}
		}

		*rowIndexBufferIndex = rowIndex;
		++rowIndex;
		rowIndexBufferIndex += 1;
		//로우인덱스버퍼에 인덱스를 기록하고 뒤로 넘어간다.
	}

	instancingBuffer_->ChangeData(&rowIndexBuffer_[0], rowIndexBuffer_.size());
	shaderResourceHelper_.AllResourcesSetting();

	instancingUnits_[0].renderUnit_->RenderInstancing2(_deltaTime, instancingUnitCount_, instancingBuffer_);


}