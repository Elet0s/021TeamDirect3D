#include "PreCompile.h"
#include "GameEngineInstancing.h"
#include "GameEngineInstancingBuffer.h"
#include "GameEngineMaterial.h"
#include "GameEngineRenderer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineVertexes.h"

size_t GameEngineInstancing::maxInstancingCount_ = 100;

void GameEngineInstancing::InstancingData::Init(const std::set<std::string>& _shaderResourceHelperNames)
{
	for (const std::string& name : _shaderResourceHelperNames)
	{
		data_.insert(std::make_pair(name, nullptr));
	}
}

void GameEngineInstancing::InstancingData::Link(const std::string_view& _name, const void* _data)
{
	std::string uppercaseDataName = GameEngineString::ToUpperReturn(_name);

	if (data_.end() == data_.find(uppercaseDataName))
	{
		MsgBoxAssertString(std::string(_name) + ": 그런 이름의 인스턴싱 데이터가 존재하지 않습니다.");
		return;
	}

	for (std::multimap<std::string, const void*>::iterator iter = data_.lower_bound(uppercaseDataName);
		iter != data_.upper_bound(uppercaseDataName); ++iter)
	{
		iter->second = _data;
	}
}

GameEngineInstancing::GameEngineInstancing() : initRenderUnit_(nullptr)
{
}

GameEngineInstancing::~GameEngineInstancing()
{
}

void GameEngineInstancing::PushUnit(std::shared_ptr<GameEngineRenderUnit> _renderUnit, std::function<void(InstancingData&)> _function)
{
	if (nullptr == _renderUnit)
	{
		MsgBoxAssert("렌더유닛이 없습니다.");
		return;
	}

	if (false == _renderUnit->GetMaterial()->GetVertexShader()->IsInstancing())
	{
		MsgBoxAssert("인스턴싱용 버텍스 셰이더를 가지지 않은 렌더유닛입니다.");
		return;
	}

	if (nullptr == initRenderUnit_)
	{
		initRenderUnit_ = _renderUnit;
		CreateInstancingDataList();
	}

	_renderUnit->Off();
	//인스턴싱에 등록되면 일반 렌더링 대상에서 제외한다.

	bool isInserted = false;	//새 렌더유닛이 제대로 삽입되었는가 여부.
	//true: 제대로 삽입되었다.
	//false: renderUnits_[i]가 100개 제한을 넘긴 상태에서 또 들어와서 제대로 삽입되지 않았다. 따로 처리를 해줄 필요가 있다.

	for (size_t i = 0; i < instancingDatas_.size(); ++i)
	{
		if (instancingDatas_[i].size() >= maxInstancingCount_)
		{
			continue;
			//renderUnits_의 i번 리스트 크기가 100을 넘어가면 여기서 등록하지 않고 아래로 넘어간다.
		}

		isInserted = true;

		InstancingData newData = _renderUnit;
		newData.Init(structuredBufferSetterNames_);

		_function(newData);

		instancingDatas_[i].push_back(newData);
	}

	//renderUnits_의 한개 리스트가 100개 제한을 넘기면 여기로 넘어와서 새 리스트를 생성한다.
	if (false == isInserted)
	{
		std::list<InstancingData>& newInstancingDataList = CreateInstancingDataList();

		InstancingData newData = _renderUnit;

		newData.Init(structuredBufferSetterNames_);

		_function(newData);

		newInstancingDataList.push_back(newData);
	}
}

void GameEngineInstancing::RenderInstancing(float _deltaTime)
{
	//데이터 수집 완료.
	//보내기만 하면 된다.

	//size_t instancingCount = 0;

	for (size_t instancingDataGroupIndex = 0; instancingDataGroupIndex < instancingDatas_.size();
		++instancingDataGroupIndex)
	{
		std::list<InstancingData>& instancingDataList = instancingDatas_[instancingDataGroupIndex];
		//instancingDatas_의 instancingDataGroupIndex번째 리스트를 받아놓는다.

		GameEngineShaderResourceHelper& instancingShaderResourceHelper = shaderResourceHelpers_[instancingDataGroupIndex];
		//instancingDataGroupIndex번째 셰이더리소스헬퍼도 받아 놓는다.

		std::multimap<std::string, GameEngineStructuredBufferSetter>& sBufferSetters
			= instancingShaderResourceHelper.GetStructuredBufferSetterMap();
		//위 셰이더리소스헬퍼의 구조화버퍼 세터를 전부 가져온다.

		std::shared_ptr<GameEngineInstancingBuffer> instancingBuffer
			= instancingBuffers_[instancingDataGroupIndex];
		//instancingBuffers_의 instancingDataGroupIndex번째 인스턴싱버퍼도 받아 놓는다??

		std::vector<char>& instancingBufferData = instancingBufferDatas_[instancingDataGroupIndex];
		//??


		int instancingRowIndex = 0;	//셰이더의 ROWINDEX 시맨틱으로 전달되는 값.
		int* instancingBufferDataStartPtr = reinterpret_cast<int*>(&instancingBufferData[0]);
		//??


		for (InstancingData& instancingData : instancingDataList)
		{
			for (std::map<std::string, const void*>::iterator dataIter = instancingData.data_.begin();
				dataIter != instancingData.data_.end(); ++dataIter)
			{
				for (std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator sBufferSetterIter = sBufferSetters.lower_bound(dataIter->first);
					sBufferSetterIter != sBufferSetters.upper_bound(dataIter->first); ++sBufferSetterIter)
				{
					size_t originalDataSize = sBufferSetterIter->second.size_;
					//

					char* originalDataPtr = &sBufferSetterIter->second.originalData_[instancingRowIndex * originalDataSize];
					//

					int copyResult = memcpy_s(
						originalDataPtr,	//
						originalDataSize,	//
						dataIter->second,	//
						originalDataSize	//
					);

					if (0 != copyResult)
					{
						MsgBoxAssert("메모리 복사 실패!");
						return;
					}
				}
			}

			*instancingBufferDataStartPtr = instancingRowIndex;
			++instancingRowIndex;
			instancingBufferDataStartPtr += 1;

		}

		instancingBuffer->ChangeData(&instancingBufferData[0], instancingBufferData.size());
		instancingShaderResourceHelper.AllResourcesSetting();
		initRenderUnit_->RenderInstancing(_deltaTime, instancingDataList.size(), instancingBuffer);
		//instancingCount += instancingDataList.size();
	}

	//shaderResourceHelpers_[0].AllResourcesSetting();
	//initRenderUnit_->RenderInstancing2(_deltaTime, instancingCount, instancingBuffers_);

	//렌더링이 끝나면 제거작업도 여기서 한다.
	for (size_t instancingDataGroupIndex = 0; instancingDataGroupIndex < instancingDatas_.size();
		++instancingDataGroupIndex)
	{

	}
}

std::list<GameEngineInstancing::InstancingData>& GameEngineInstancing::CreateInstancingDataList()
{
	std::list<InstancingData>& newInstancingDataList = instancingDatas_.emplace_back();
	//renderUnits_에 크기 100짜리 새 리스트를 생성한다.

	std::vector<char>& newInstancingBufferData = instancingBufferDatas_.emplace_back();
	//??

	GameEngineShaderResourceHelper& newHelper = shaderResourceHelpers_.emplace_back();
	//새 셰이더리소스헬퍼 생성, 삽입.

	newHelper.ShaderCheck(initRenderUnit_->GetMaterial()->GetVertexShader()->GetInst_VertexShader());
	//initRenderUnit_의 인스턴싱버텍스셰이더가 가진 모든 구조화 버퍼들을 찾아 연결한다.

	//std::shared_ptr<GameEngineInstancingBuffer> newInstancingBufferPtr = instancingBuffers_.emplace_back();
	//밖으로 복사되지 않음.

	std::shared_ptr<GameEngineInstancingBuffer>& newInstancingBufferPtr = instancingBuffers_.emplace_back();
	//새 인스턴싱버퍼 생성, 삽입.

	size_t instancingSize = static_cast<size_t>(initRenderUnit_->GetMesh()->GetInputLayoutDesc().instancingSize_);
	//인스턴싱 단위 크기 == UINT 4byte.

	newInstancingBufferPtr = GameEngineInstancingBuffer::Create(maxInstancingCount_, instancingSize);
	//인스턴싱버퍼 생성.

	newInstancingBufferData.resize(maxInstancingCount_ * newInstancingBufferPtr->GetDataSize());
	//????

	std::multimap<std::string, GameEngineStructuredBufferSetter>& structuredBufferSetterMap
		= newHelper.GetStructuredBufferSetterMap();
	//newHelper가 가진 구조화버퍼 세터를 전부 가져온다.


	for (std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator iter = structuredBufferSetterMap.begin();
		iter != structuredBufferSetterMap.end(); ++iter)
	{
		//newHelper의 모든 구조화버퍼 세터들 중 이름에 "INST_" 라는 문자열이 포함된 것들만 골라서 
		// 그 세터와 연결된 구조화버퍼를 생성하거나 크기를 조정한다.
		if (std::string::npos != iter->first.find("INST_"))
		{
			iter->second.Resize(maxInstancingCount_);

			//Start->second.Res = GameEngineStructuredBuffer::Create(Start->second.Res->GetShaderDesc(), MaxInstancingCount);
			//Start->second.Resize(MaxInstancingCount);
			//Start->second.Bind();
		}
	}

	if (true == structuredBufferSetterNames_.empty())
	{
		for (std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator iter = structuredBufferSetterMap.begin();
			iter != structuredBufferSetterMap.end(); ++iter)
		{
			//structuredBufferSetterNames_가 비어있다면 
			// newHelper의 모든 구조화버퍼 세터들 중 이름에 "INST_" 라는 문자열이 포함된 것들만 골라서 
			// structuredBufferSetterNames_에 이름을 등록한다.
			if (std::string::npos != iter->first.find("INST_"))
			{
				structuredBufferSetterNames_.insert(iter->first);
			}
		}
	}

	return newInstancingDataList;
}