#include "PreCompile.h"
#include "GameEngineActor.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineLevel.h"

GameEngineActor::GameEngineActor() : parentLevel_(), isLevelOver_(false)
{
}

GameEngineActor::~GameEngineActor()
{
	//for (GameEngineComponent* component : allComponents_)
	//{
	//	if (nullptr != component)
	//	{
	//		delete component;
	//		component = nullptr;
	//	}
	//}
	
	//for (GameEngineTransformComponent* transformComponent : allTransformComponents_)
	//{
	//	if (nullptr != transformComponent)
	//	{
	//		delete transformComponent;
	//		transformComponent = nullptr;
	//	}
	//}
	//�� ���̻� �Ҹ��ڿ��� �������� ����??
	//->���Ͱ� ������Ʈ���� ���̻� ���� ������ �ʰ� GameEngineUpdateObjectŬ������ children_�� ���� ���������� ������ 
	// ������ ������Ʈ ������ ���� ������ �� ����, ���� ����� ������Ʈ�� ���� Death()�Լ��� ȣ���ؾ� ���� ������ ���� 
	// ����� ������ �� �ִ�.
}

void GameEngineActor::DetachObject()
{
	GameEngineUpdateObject::DetachObject();

	this->GetTransform().DetachTransform();
	//�� �̻� ���� �θ�� ������ �´ٴ� ������ ����.

	if (false == this->IsDead())
	{
		GetLevel()->PushActor(this, this->GetOrder());
	}
}

void GameEngineActor::SetParent(GameEngineUpdateObject* _newParent)
{
	if (nullptr == this->GetParent())	//������ �θ� ���� == ������ ������ �θ��.	
	{
		this->GetLevel()->RemoveActor(this);
		//������ allActors_�� ��ϵ� ���͸� �����Ѵ�.
	}

	this->GameEngineUpdateObject::SetParent(_newParent);	//���Ϳ��� ���ο� �θ� �������ش�.

	GameEngineTransformBase* newParent = dynamic_cast<GameEngineTransformBase*>(_newParent);
	if (nullptr == newParent)
	{
		MsgBoxAssert("Ʈ�������� �ִ� ������Ʈ���� ������ �θ� �� �� �ֽ��ϴ�.");
	}
	else
	{
		this->GetTransform().SetParentTransform(newParent->GetTransform());	//Ʈ�������� �θ��ڽ� ���踦 �δ´�.
	}
}

void GameEngineActor::Start()
{
}

void GameEngineActor::Update(float _deltaTime)
{
}

void GameEngineActor::End()
{
}