#include "PreCompile.h"
#include "GameEngineInstancing.h"
#include "GameEngineInstancingBuffer.h"
#include "GameEngineMaterial.h"

// �ּ� 2���̻��� �𿩾� �ν��Ͻ��� �����ϰڴ�.
unsigned int GameEngineInstancing::minInstancingCount_ = 2;

// �ϴ� �����ߴٸ� 100���� �Ҽ� �ִٴ� �����Ͽ� �̰� �ϰڴ�.
unsigned int GameEngineInstancing::startInstancingCount_ = 100;

GameEngineInstancing::GameEngineInstancing()
	: instancingPipeLine_(nullptr),
	instancingBuffer_(nullptr),
	dataInsert_(0),
	size_(0),
	count_(0),
	maxDataCount_(0)
{
}

GameEngineInstancing::~GameEngineInstancing()
{
}

void GameEngineInstancing::InstancingBufferChangeData()
{
	if (nullptr == instancingBuffer_)
	{
		MsgBoxAssert("�ν��Ͻ̿� ���۰� �����ϴ�.");
		return;
	}	

	instancingBuffer_->ChangeData(&dataBuffer_[0], dataBuffer_.size());
}
