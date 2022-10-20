#pragma once
#include "GameEngineComponent.h"
#include "GameEngineActor.h"
#include "GameEngineTransformBase.h"


class GameEngineTransformComponent : public GameEngineComponent, public GameEngineTransformBase
{
	//GameEngineTransform transform_;
	//�� �̻� ��ü������ Ʈ�������� ������ �ʰ�, 
	// ���� ������ �ʿ��ϸ� Ʈ���������̽� Ŭ������ ��ӹ޾Ƽ� �װ� ����Ѵ�.


public:

	GameEngineTransformComponent();
	~GameEngineTransformComponent();

	GameEngineTransformComponent(const GameEngineTransformComponent& _other) = delete;
	GameEngineTransformComponent(GameEngineTransformComponent&& _other) noexcept = delete;
	GameEngineTransformComponent& operator=(const GameEngineTransformComponent& _other) = delete;
	GameEngineTransformComponent& operator=(GameEngineTransformComponent&& _other) = delete;

public:
	void SetParent(GameEngineUpdateObject* _newParent) override;
	void DetachObject() override;


public:

	GameEngineActor* GetActor()
	{
		return this->GetRoot<GameEngineActor>();
	}

	template<typename ParentType>
	ParentType* GetActor()
	{
		return this->GetParent<ParentType>();
	}

};

