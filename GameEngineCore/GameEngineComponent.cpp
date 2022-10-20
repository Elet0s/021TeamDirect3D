#include "PreCompile.h"
#include "GameEngineComponent.h"

GameEngineComponent::GameEngineComponent()
{
}

GameEngineComponent::~GameEngineComponent()
{
}

void GameEngineComponent::SetParent(GameEngineUpdateObject* _newParent)
{
	GameEngineUpdateObject::SetParent(_newParent);
}

void GameEngineComponent::Start()
{
}

void GameEngineComponent::Update(float _deltaTime)
{
}

void GameEngineComponent::End()
{
}
