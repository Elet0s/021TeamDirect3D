#include "PreCompile.h"
#include "GameEngineActor.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineLevel.h"

GameEngineActor::GameEngineActor() : parentLevel_(), isLevelOver_(false)
{
}

GameEngineActor::~GameEngineActor()
{
}

void GameEngineActor::DetachObject()
{
	GameEngineUpdateObject::DetachObject();

	this->GetTransform().DetachTransform();
	//더 이상 액터 부모로 레벨만 온다는 보장이 없다.

	if (false == this->IsDead())
	{
		GetLevel()->PushActor(std::dynamic_pointer_cast<GameEngineActor>(shared_from_this()), this->GetOrder());
	}
}

void GameEngineActor::SetParent(std::shared_ptr<GameEngineUpdateObject> _newParent)
{
	if (nullptr == this->GetParent())	//액터의 부모가 없다 == 레벨이 액터의 부모다.	
	{
		this->GetLevel()->RemoveActor(std::dynamic_pointer_cast<GameEngineActor>(shared_from_this()));
		//레벨의 allActors_에 등록된 액터를 제거한다.
	}

	this->GameEngineUpdateObject::SetParent(_newParent);	//액터에게 새로운 부모를 세팅해준다.

	std::shared_ptr<GameEngineTransformBase> newParent = std::dynamic_pointer_cast<GameEngineTransformBase>(_newParent);
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