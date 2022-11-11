#pragma once

class GameEngineUpdateObject
	: public GameEngineDebugObject,
	public std::enable_shared_from_this<GameEngineUpdateObject>
{
	//이 프레임워크에 사용되는 모든 오브젝트들의 생성, 갱신, 삭제 구조를 만드는 클래스.

public:

	GameEngineUpdateObject();
	virtual ~GameEngineUpdateObject();

	GameEngineUpdateObject(const GameEngineUpdateObject& _other) = delete;
	GameEngineUpdateObject(GameEngineUpdateObject&& _other) noexcept = delete;
	GameEngineUpdateObject& operator=(const GameEngineUpdateObject& _other) = delete;
	GameEngineUpdateObject& operator=(GameEngineUpdateObject&& _other) = delete;


public:
	//이 오브젝트에게 부모를 달아주고, 부모 오브젝트의 children_ 리스트에 이 오브젝트를 등록하는 함수.
	virtual void SetParent(std::shared_ptr<GameEngineUpdateObject> _newParent);

	//이 오브젝트와 그 자식들을 최종 삭제하는 함수.
	virtual void ReleaseHierarchy();

	// 이 오브젝트가 프레임구조안에서 돌때 거치는 절차.
	virtual void Update(float _deltaTime) = 0;

	void AllUpdate(float _deltaTime);

	virtual void LevelStartEvent() {};
	virtual void LevelEndEvent() {};

public:
	inline void On()
	{
		isUpdate_ = true;
		AllOnEvent();
	}

	inline void Off()
	{
		isUpdate_ = false;
		AllOffEvent();
	}

	inline void OnOffSwitch()
	{
		isUpdate_ = !isUpdate_;
		isUpdate_ == true ? OnEvent() : OffEvent();
	}

	//특정 오브젝트가 업데이트중인지 아닌지 받아보는 함수.
	inline bool IsUpdate()
	{
		if (nullptr == parent_.lock())
		{
			return isUpdate_ && false == isDead_;
		}
		else
		{
			return isUpdate_ && false == isDead_ && true == parent_.lock()->IsUpdate();
			//자기 자신이 isUpdate_ == true여도 부모 오브젝트가 isUpdate_ == false면 업데이트에서 제외된다. 
		}
	}

	inline bool& IsUpdateRef()
	{
		return isUpdate_;
	}

	inline bool IsDead()
	{
		if (nullptr == parent_.lock())
		{
			return isDead_;
		}
		else
		{
			return isDead_ || true == parent_.lock()->IsDead();
			//자기 자신이 isDead_ == false여도 부모 오브젝트가 isUpdate_ == true면 사망 판정받고 삭제된다.
		}
	}

	//특정 오브젝트가 생성된 시점으로부터 얼마나 시간이 지났는지 측정하는 함수.
	void AddAccTime(float _deltaTime)
	{
		accTime_ += _deltaTime;
	}

	//생성된 시점으로부터 얼마만큼의 시간이 지났는지 받아보는 함수.
	float GetAccTime()
	{
		return accTime_;
	}

	//특정 오브젝트가 생성된 시간 초기화.
	void ResetAccTime()
	{
		accTime_ = 0.0f;
	}

	//특정 오브젝트를 즉시 사망판정 내리는 함수.
	inline void Death()
	{
		isDead_ = true;
	}

	//입력한 시간이 지난 후 특정 오브젝트를 사망 판정하는 함수.
	inline void Death(float _time)
	{
		isReleaseUpdate_ = true;
		deadTime_ = _time;
	}

	//특정 시간 후 사망 판정되는 오브젝트의 남은 시간이 얼마인지 갱신하는 함수.
	void ReleaseUpdate(float _deltaTime)
	{
		if (false == isReleaseUpdate_)
		{
			return;
		}

		deadTime_ -= _deltaTime;

		if (0.0f >= deadTime_)
		{
			isDead_ = true;
		}
	}

	inline int GetOrder()
	{
		return order_;
	}

	//업데이트 순서 설정.
	virtual inline void SetOrder(int _order)
	{
		order_ = _order;
	}

	//형변환 부모 받기.
	template<typename ParentType>
	std::shared_ptr<ParentType> GetParent()
	{
		return std::dynamic_pointer_cast<ParentType>(parent_.lock());
	}

	//GameEngineUpdateObject* 형태로 부모 받기.
	std::shared_ptr<GameEngineUpdateObject> GetParent()
	{
		return parent_.lock();
	}

	//레벨 바로 아래 등록된 오브젝트까지 거슬러 올라가, 그 오브젝트를 형변환해서 반환받는 함수.
	template<typename ParentType>
	std::shared_ptr<ParentType> GetRoot()
	{
		return std::dynamic_pointer_cast<ParentType>(GetRoot());
	}

	//레벨 바로 아래 등록된 오브젝트까지 거슬러 올라가, 그 오브젝트를 반환받는 함수.
	std::shared_ptr<GameEngineUpdateObject> GetRoot()
	{
		std::shared_ptr<GameEngineUpdateObject> currentObject = shared_from_this();

		while (nullptr != currentObject->GetParent())
		{
			currentObject = currentObject->GetParent();
		}
		return currentObject;
	}



protected:
	//이 오브젝트가 업데이트를 시작할때 호출하는 함수.
	virtual void OnEvent() {}

	//이 오브젝트가 업데이트를 정지할 때 호출하는 함수.
	virtual void OffEvent() {}

	//이 오브젝트가 생성될때 거치는 절차들을 실행하는 함수.
	virtual void Start() = 0;

	// 이 오브젝트가 메모리가 삭제될 때 거치는 절차들을 실행하는 함수. 현재 유저코어의 End()외엔 호출되지 않음.
	virtual void End() = 0;

	void AllLevelStartEvent();
	void AllLevelEndEvent();

	void AllOnEvent();		//
	void AllOffEvent();		//

	//사망판정받은 오브젝트와 그 자식들을 업데이트 루프에서 떼어내 삭제 대상 리스트에 등록하는 함수.
	//여기에 넣은 오브젝트들은 다음 루프에서 삭제된다. 바로 삭제되지 않는것에 주의할 것.
	void ReleaseObject(std::list<std::shared_ptr<GameEngineUpdateObject>>& _releaseList);

	//이 오브젝트를 부모 오브젝트의 children_리스트에서 제거하는 함수.
	virtual void DetachObject();

protected:
	//이 오브젝트의 자식들 중 특정 형태의 자식들만 받아보는 함수.
	template<typename ConvertType>
	std::list<ConvertType*> GetConvertedChildren()
	{
		std::list<ConvertType*> newList;

		for (GameEngineUpdateObject* child : children_)
		{
			ConvertType* convertedChild = dynamic_cast<ConvertType*>(child);
			if (nullptr != convertedChild)
			{
				newList.push_back(convertedChild);
			}
		}

		return newList;
	}

protected:
	std::list<std::shared_ptr<GameEngineUpdateObject>> children_;	//자식 오브젝트들.

private:



private:
	int order_;			//업데이트 순서.
	bool isReleaseUpdate_;	//true: 특정 오브젝트가 일정 시간후 사망.
	float deadTime_;	//지정 오브젝트의 사망 예정 시간. 이 시간이 0이나 음수가 되면 사망.
	float accTime_;		//오브젝트 생성 시점으로부터 지난 시간.

	bool isUpdate_;	//true: 업데이트 참여. false: 업데이트 제외.
	bool isDead_;	//true: 사망 판정 받음. false: 사망 판정 안 받음. 사망처리가 아닌 사망 판정임에 주의.

	std::weak_ptr<GameEngineUpdateObject> parent_;	//부모 오브젝트.


};

