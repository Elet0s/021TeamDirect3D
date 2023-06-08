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
	//왜 더이상 소멸자에서 삭제하지 않지??
	//->액터가 컴포넌트들을 더이상 직접 가지지 않고 GameEngineUpdateObject클래스의 children_을 통해 간접적으로 가지기 
	// 때문에 컴포넌트 삭제도 직접 삭제할 수 없고, 삭제 대상인 컴포넌트가 직접 Death()함수를 호출해야 여러 절차를 거쳐 
	// 제대로 삭제할 수 있다.
}

void GameEngineActor::DetachObject()
{
	GameEngineUpdateObject::DetachObject();

	this->GetTransform().DetachTransform();
	//더 이상 액터 부모로 레벨만 온다는 보장이 없다.

	if (false == this->IsDead())
	{
		GetLevel()->PushActor(this, this->GetOrder());
	}
}

void GameEngineActor::SetParent(GameEngineUpdateObject* _newParent)
{
	if (nullptr == this->GetParent())	//액터의 부모가 없다 == 레벨이 액터의 부모다.	
	{
		this->GetLevel()->RemoveActor(this);
		//레벨의 allActors_에 등록된 액터를 제거한다.
	}

	this->GameEngineUpdateObject::SetParent(_newParent);	//액터에게 새로운 부모를 세팅해준다.

	GameEngineTransformBase* newParent = dynamic_cast<GameEngineTransformBase*>(_newParent);
	if (nullptr == newParent)
	{
		MsgBoxAssert("트랜스폼이 있는 오브젝트만이 액터의 부모가 될 수 있습니다.");
	}
	else
	{
		this->GetTransform().SetParentTransform(newParent->GetTransform());	//트랜스폼도 부모자식 관계를 맺는다.
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