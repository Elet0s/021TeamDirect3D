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
		MsgBoxAssertString(std::string(_name) + ": �׷� �̸��� �ν��Ͻ� �����Ͱ� �������� �ʽ��ϴ�.");
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
		MsgBoxAssert("���������� �����ϴ�.");
		return;
	}

	if (false == _renderUnit->GetMaterial()->GetVertexShader()->IsInstancing())
	{
		MsgBoxAssert("�ν��Ͻ̿� ���ؽ� ���̴��� ������ ���� ���������Դϴ�.");
		return;
	}

	if (nullptr == initRenderUnit_)
	{
		initRenderUnit_ = _renderUnit;
		CreateInstancingDataList();
	}

	_renderUnit->Off();
	//�ν��Ͻ̿� ��ϵǸ� �Ϲ� ������ ��󿡼� �����Ѵ�.

	bool isInserted = false;	//�� ���������� ����� ���ԵǾ��°� ����.
	//true: ����� ���ԵǾ���.
	//false: renderUnits_[i]�� 100�� ������ �ѱ� ���¿��� �� ���ͼ� ����� ���Ե��� �ʾҴ�. ���� ó���� ���� �ʿ䰡 �ִ�.

	for (size_t i = 0; i < instancingDatas_.size(); ++i)
	{
		if (instancingDatas_[i].size() >= maxInstancingCount_)
		{
			continue;
			//renderUnits_�� i�� ����Ʈ ũ�Ⱑ 100�� �Ѿ�� ���⼭ ������� �ʰ� �Ʒ��� �Ѿ��.
		}

		isInserted = true;

		InstancingData newData = _renderUnit;
		newData.Init(structuredBufferSetterNames_);

		_function(newData);

		instancingDatas_[i].push_back(newData);
	}

	//renderUnits_�� �Ѱ� ����Ʈ�� 100�� ������ �ѱ�� ����� �Ѿ�ͼ� �� ����Ʈ�� �����Ѵ�.
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
	//������ ���� �Ϸ�.
	//�����⸸ �ϸ� �ȴ�.

	//size_t instancingCount = 0;

	for (size_t instancingDataGroupIndex = 0; instancingDataGroupIndex < instancingDatas_.size();
		++instancingDataGroupIndex)
	{
		std::list<InstancingData>& instancingDataList = instancingDatas_[instancingDataGroupIndex];
		//instancingDatas_�� instancingDataGroupIndex��° ����Ʈ�� �޾Ƴ��´�.

		GameEngineShaderResourceHelper& instancingShaderResourceHelper = shaderResourceHelpers_[instancingDataGroupIndex];
		//instancingDataGroupIndex��° ���̴����ҽ����۵� �޾� ���´�.

		std::multimap<std::string, GameEngineStructuredBufferSetter>& sBufferSetters
			= instancingShaderResourceHelper.GetStructuredBufferSetterMap();
		//�� ���̴����ҽ������� ����ȭ���� ���͸� ���� �����´�.

		std::shared_ptr<GameEngineInstancingBuffer> instancingBuffer
			= instancingBuffers_[instancingDataGroupIndex];
		//instancingBuffers_�� instancingDataGroupIndex��° �ν��Ͻ̹��۵� �޾� ���´�??

		std::vector<char>& instancingBufferData = instancingBufferDatas_[instancingDataGroupIndex];
		//??


		int instancingRowIndex = 0;	//���̴��� ROWINDEX �ø�ƽ���� ���޵Ǵ� ��.
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
						MsgBoxAssert("�޸� ���� ����!");
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

	//�������� ������ �����۾��� ���⼭ �Ѵ�.
	for (size_t instancingDataGroupIndex = 0; instancingDataGroupIndex < instancingDatas_.size();
		++instancingDataGroupIndex)
	{

	}
}

std::list<GameEngineInstancing::InstancingData>& GameEngineInstancing::CreateInstancingDataList()
{
	std::list<InstancingData>& newInstancingDataList = instancingDatas_.emplace_back();
	//renderUnits_�� ũ�� 100¥�� �� ����Ʈ�� �����Ѵ�.

	std::vector<char>& newInstancingBufferData = instancingBufferDatas_.emplace_back();
	//??

	GameEngineShaderResourceHelper& newHelper = shaderResourceHelpers_.emplace_back();
	//�� ���̴����ҽ����� ����, ����.

	newHelper.ShaderCheck(initRenderUnit_->GetMaterial()->GetVertexShader()->GetInst_VertexShader());
	//initRenderUnit_�� �ν��Ͻ̹��ؽ����̴��� ���� ��� ����ȭ ���۵��� ã�� �����Ѵ�.

	//std::shared_ptr<GameEngineInstancingBuffer> newInstancingBufferPtr = instancingBuffers_.emplace_back();
	//������ ������� ����.

	std::shared_ptr<GameEngineInstancingBuffer>& newInstancingBufferPtr = instancingBuffers_.emplace_back();
	//�� �ν��Ͻ̹��� ����, ����.

	size_t instancingSize = static_cast<size_t>(initRenderUnit_->GetMesh()->GetInputLayoutDesc().instancingSize_);
	//�ν��Ͻ� ���� ũ�� == UINT 4byte.

	newInstancingBufferPtr = GameEngineInstancingBuffer::Create(maxInstancingCount_, instancingSize);
	//�ν��Ͻ̹��� ����.

	newInstancingBufferData.resize(maxInstancingCount_ * newInstancingBufferPtr->GetDataSize());
	//????

	std::multimap<std::string, GameEngineStructuredBufferSetter>& structuredBufferSetterMap
		= newHelper.GetStructuredBufferSetterMap();
	//newHelper�� ���� ����ȭ���� ���͸� ���� �����´�.


	for (std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator iter = structuredBufferSetterMap.begin();
		iter != structuredBufferSetterMap.end(); ++iter)
	{
		//newHelper�� ��� ����ȭ���� ���͵� �� �̸��� "INST_" ��� ���ڿ��� ���Ե� �͵鸸 ��� 
		// �� ���Ϳ� ����� ����ȭ���۸� �����ϰų� ũ�⸦ �����Ѵ�.
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
			//structuredBufferSetterNames_�� ����ִٸ� 
			// newHelper�� ��� ����ȭ���� ���͵� �� �̸��� "INST_" ��� ���ڿ��� ���Ե� �͵鸸 ��� 
			// structuredBufferSetterNames_�� �̸��� ����Ѵ�.
			if (std::string::npos != iter->first.find("INST_"))
			{
				structuredBufferSetterNames_.insert(iter->first);
			}
		}
	}

	return newInstancingDataList;
}