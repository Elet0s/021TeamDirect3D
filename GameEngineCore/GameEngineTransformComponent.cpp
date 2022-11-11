#include "PreCompile.h"
#include "GameEngineTransformComponent.h"

GameEngineTransformComponent::GameEngineTransformComponent()
{
}

GameEngineTransformComponent::~GameEngineTransformComponent()
{
}

void GameEngineTransformComponent::SetParent(std::shared_ptr<GameEngineUpdateObject> _newParent)
{
	GameEngineUpdateObject::SetParent(_newParent);

	std::shared_ptr<GameEngineTransformBase> transformParent
		= std::dynamic_pointer_cast<GameEngineTransformBase>(_newParent);
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
