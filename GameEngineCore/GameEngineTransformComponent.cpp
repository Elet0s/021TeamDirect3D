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
		MsgBoxAssert("Ʈ�������� �ִ� ������Ʈ���� �ٸ� Ʈ������������Ʈ�� �θ� �� �� �ֽ��ϴ�.");
		return;
	}
	else
	{
		this->GetTransform().SetParentTransform(transformParent->GetTransform());
	}
}

void GameEngineTransformComponent::DetachObject()
{
	GameEngineUpdateObject::DetachObject();	//�θ� ������Ʈ���� ���� �����.
	this->GetTransform().DetachTransform();	//�θ��� Ʈ������������ �����. 
}
