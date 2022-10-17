#include "PreCompile.h"
#include "GameEngineInstancing.h"

// �ּ� 2���̻��� �𿩾� �ν��Ͻ��� �����ϰڴ�.
unsigned int GameEngineInstancing::MinInstancingCount = 1;

// �ϴ� �����ߴٸ� 100���� �Ҽ� �ִٴ� �����Ͽ� �̰� �ϰڴ�.
unsigned int GameEngineInstancing::StartInstancingCount = 100;

GameEngineInstancing::GameEngineInstancing() 
	: Buffer(nullptr)
	, Count(0)
	, DataInsert(0)

{
}

GameEngineInstancing::~GameEngineInstancing() 
{
}



void GameEngineInstancing::InstancingBufferChangeData()
{
	if (nullptr == Buffer)
	{
		MsgBoxAssert("�ν��Ͻ̿� ���۸� ������ �ʾҽ��ϴ�. �ʾҽ��ϴ�.")
	}

	Buffer->ChangeData(&DataBuffer[0], DataBuffer.size());
}