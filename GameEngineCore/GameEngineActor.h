#pragma once
#include "GameEngineTransformBase.h"
#include "GameEngineUpdateObject.h"
#include "GameEngineComponent.h"

class GameEngineTransformComponent;
class GameEngineLevel;
class GameEngineActor :
	public GameEngineNameObject,
	public GameEngineUpdateObject,
	public GameEngineTransformBase
{
	//
	//����:

	//���߻�� ����: ��ӹ��� �θ� Ŭ�������� ����� ������ �ϴµ�, �� ����� ���� Ŭ�������� ������ ����°� ���������̾.


	friend GameEngineLevel;
	friend class GameEngineCamera;


public:
	GameEngineActor();
	virtual ~GameEngineActor() /*= 0*/;

private:
	GameEngineActor(const GameEngineActor& _other) = delete;
	GameEngineActor(GameEngineActor&& _other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _other) = delete;


public:
	void DetachObject() override;
	void SetParent(std::shared_ptr<GameEngineUpdateObject> _newParent) override;	//���Ϳ� ������ �ƴ� �� �θ� ���̴� �Լ�.

public:

	template<typename ComponentType>
	std::shared_ptr<ComponentType> CreateComponent(const std::string_view& _componentName = "")
	{
		std::shared_ptr<GameEngineComponent> newComponent = std::make_shared<ComponentType>();

		newComponent->SetParent(shared_from_this());
		newComponent->SetName(_componentName);
		newComponent->Start();

		return std::dynamic_pointer_cast<ComponentType>(newComponent);
	}

	inline GameEngineLevel* GetLevel()
	{
		return parentLevel_;
	}

	template<typename LevelType>
	inline LevelType* GetLevel()
	{
		return dynamic_cast<LevelType*>(parentLevel_);
	}

	void SetLevelOverOn()	//������ �ű� ���͵��� ǥ���ϴ� �Լ�.
	{
		isLevelOver_ = true;
		//�� �Լ��� ȣ���� ������Ʈ�� �ߺ����� ����!
	}


protected:
	virtual void Start() override;
	virtual void Update(float _deltaTime) override;
	virtual void End() override;

private:
	void SetLevel(GameEngineLevel* _level)
	{
		parentLevel_ = _level;
	}


private:

	GameEngineLevel* parentLevel_;	//�� ���͸� ���� ����.

	bool isLevelOver_;	//true: �� �������� �ٸ� ������ �ű� ������ ������Ʈ.
};

