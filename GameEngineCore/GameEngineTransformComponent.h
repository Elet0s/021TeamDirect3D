#pragma once
#include "GameEngineComponent.h"
#include "GameEngineActor.h"
#include "GameEngineTransformBase.h"


class GameEngineTransformComponent : public GameEngineComponent, public GameEngineTransformBase
{
	//GameEngineTransform transform_;
	//더 이상 자체적으로 트랜스폼을 가지지 않고, 
	// 기하 정보가 필요하면 트랜스폼베이스 클래스를 상속받아서 그걸 사용한다.


public:

	GameEngineTransformComponent();
	~GameEngineTransformComponent();

	GameEngineTransformComponent(const GameEngineTransformComponent& _other) = delete;
	GameEngineTransformComponent(GameEngineTransformComponent&& _other) noexcept = delete;
	GameEngineTransformComponent& operator=(const GameEngineTransformComponent& _other) = delete;
	GameEngineTransformComponent& operator=(GameEngineTransformComponent&& _other) = delete;

public:
	void SetParent(std::shared_ptr<GameEngineUpdateObject> _newParent) override;
	void DetachObject() override;


public:

	std::shared_ptr<GameEngineActor> GetActor()
	{
		return this->GetRoot<GameEngineActor>();
	}

	template<typename ParentType>
	std::shared_ptr<ParentType> GetActor()
	{
		return this->GetParent<ParentType>();
	}

};

