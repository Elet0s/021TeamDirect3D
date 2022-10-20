#include "PreCompile.h"
#include "GameEngineTransformComponent.h"

GameEngineTransformComponent::GameEngineTransformComponent()
{
}

GameEngineTransformComponent::~GameEngineTransformComponent()
{
}

void GameEngineTransformComponent::SetParent(GameEngineUpdateObject* _newParent)
{
	GameEngineComponent::SetParent(_newParent);

	GameEngineTransformBase* transformParent = dynamic_cast<GameEngineTransformBase*>(_newParent);
	if (transformParent == nullptr)
	{
		MsgBoxAssert("트랜스폼이 있는 오브젝트만이 다른 트랜스폼오브젝트의 부모가 될 수 있습니다.");
		return;
	}
	else
	{
		this->GetTransform().SetParentTransform(transformParent->GetTransform());
	}
}

void GameEngineTransformComponent::DetachObject()
{
	GameEngineUpdateObject::DetachObject();	//부모 오브젝트에서 먼저 떼어낸다.
	this->GetTransform().DetachTransform();	//부모의 트랜스폼에서도 떼어낸다. 
}
