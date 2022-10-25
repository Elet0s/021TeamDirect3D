#include "PreCompile.h"
#include "GameEngineInstancing.h"
#include "GameEngineInstancingBuffer.h"
#include "GameEngineMaterial.h"

// 최소 2개이상이 모여야 인스턴싱을 시작하겠다.
unsigned int GameEngineInstancing::minInstancingCount_ = 2;

// 일단 시작했다면 100개는 할수 있다는 가정하에 이걸 하겠다.
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
		MsgBoxAssert("인스턴싱에 버퍼가 없습니다.");
		return;
	}	

	instancingBuffer_->ChangeData(&dataBuffer_[0], dataBuffer_.size());
}
