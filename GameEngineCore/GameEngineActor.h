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
	//액터:

	//다중상속 이유: 상속받은 부모 클래스들의 기능은 가져야 하는데, 그 기능을 가진 클래스들을 일일히 만드는건 비현실적이어서.


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
	void SetParent(std::shared_ptr<GameEngineUpdateObject> _newParent) override;	//액터에 레벨이 아닌 새 부모를 붙이는 함수.

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

	void SetLevelOverOn()	//레벨을 옮길 액터들을 표시하는 함수.
	{
		isLevelOver_ = true;
		//이 함수를 호출한 오브젝트는 중복생성 금지!
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

	GameEngineLevel* parentLevel_;	//이 액터를 가진 레벨.

	bool isLevelOver_;	//true: 이 레벨에서 다른 레벨로 옮길 예정인 오브젝트.
};

