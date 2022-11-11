#pragma once

class GameEngineUpdateObject
	: public GameEngineDebugObject,
	public std::enable_shared_from_this<GameEngineUpdateObject>
{
	//�� �����ӿ�ũ�� ���Ǵ� ��� ������Ʈ���� ����, ����, ���� ������ ����� Ŭ����.

public:

	GameEngineUpdateObject();
	virtual ~GameEngineUpdateObject();

	GameEngineUpdateObject(const GameEngineUpdateObject& _other) = delete;
	GameEngineUpdateObject(GameEngineUpdateObject&& _other) noexcept = delete;
	GameEngineUpdateObject& operator=(const GameEngineUpdateObject& _other) = delete;
	GameEngineUpdateObject& operator=(GameEngineUpdateObject&& _other) = delete;


public:
	//�� ������Ʈ���� �θ� �޾��ְ�, �θ� ������Ʈ�� children_ ����Ʈ�� �� ������Ʈ�� ����ϴ� �Լ�.
	virtual void SetParent(std::shared_ptr<GameEngineUpdateObject> _newParent);

	//�� ������Ʈ�� �� �ڽĵ��� ���� �����ϴ� �Լ�.
	virtual void ReleaseHierarchy();

	// �� ������Ʈ�� �����ӱ����ȿ��� ���� ��ġ�� ����.
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

	//Ư�� ������Ʈ�� ������Ʈ������ �ƴ��� �޾ƺ��� �Լ�.
	inline bool IsUpdate()
	{
		if (nullptr == parent_.lock())
		{
			return isUpdate_ && false == isDead_;
		}
		else
		{
			return isUpdate_ && false == isDead_ && true == parent_.lock()->IsUpdate();
			//�ڱ� �ڽ��� isUpdate_ == true���� �θ� ������Ʈ�� isUpdate_ == false�� ������Ʈ���� ���ܵȴ�. 
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
			//�ڱ� �ڽ��� isDead_ == false���� �θ� ������Ʈ�� isUpdate_ == true�� ��� �����ް� �����ȴ�.
		}
	}

	//Ư�� ������Ʈ�� ������ �������κ��� �󸶳� �ð��� �������� �����ϴ� �Լ�.
	void AddAccTime(float _deltaTime)
	{
		accTime_ += _deltaTime;
	}

	//������ �������κ��� �󸶸�ŭ�� �ð��� �������� �޾ƺ��� �Լ�.
	float GetAccTime()
	{
		return accTime_;
	}

	//Ư�� ������Ʈ�� ������ �ð� �ʱ�ȭ.
	void ResetAccTime()
	{
		accTime_ = 0.0f;
	}

	//Ư�� ������Ʈ�� ��� ������� ������ �Լ�.
	inline void Death()
	{
		isDead_ = true;
	}

	//�Է��� �ð��� ���� �� Ư�� ������Ʈ�� ��� �����ϴ� �Լ�.
	inline void Death(float _time)
	{
		isReleaseUpdate_ = true;
		deadTime_ = _time;
	}

	//Ư�� �ð� �� ��� �����Ǵ� ������Ʈ�� ���� �ð��� ������ �����ϴ� �Լ�.
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

	//������Ʈ ���� ����.
	virtual inline void SetOrder(int _order)
	{
		order_ = _order;
	}

	//����ȯ �θ� �ޱ�.
	template<typename ParentType>
	std::shared_ptr<ParentType> GetParent()
	{
		return std::dynamic_pointer_cast<ParentType>(parent_.lock());
	}

	//GameEngineUpdateObject* ���·� �θ� �ޱ�.
	std::shared_ptr<GameEngineUpdateObject> GetParent()
	{
		return parent_.lock();
	}

	//���� �ٷ� �Ʒ� ��ϵ� ������Ʈ���� �Ž��� �ö�, �� ������Ʈ�� ����ȯ�ؼ� ��ȯ�޴� �Լ�.
	template<typename ParentType>
	std::shared_ptr<ParentType> GetRoot()
	{
		return std::dynamic_pointer_cast<ParentType>(GetRoot());
	}

	//���� �ٷ� �Ʒ� ��ϵ� ������Ʈ���� �Ž��� �ö�, �� ������Ʈ�� ��ȯ�޴� �Լ�.
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
	//�� ������Ʈ�� ������Ʈ�� �����Ҷ� ȣ���ϴ� �Լ�.
	virtual void OnEvent() {}

	//�� ������Ʈ�� ������Ʈ�� ������ �� ȣ���ϴ� �Լ�.
	virtual void OffEvent() {}

	//�� ������Ʈ�� �����ɶ� ��ġ�� �������� �����ϴ� �Լ�.
	virtual void Start() = 0;

	// �� ������Ʈ�� �޸𸮰� ������ �� ��ġ�� �������� �����ϴ� �Լ�. ���� �����ھ��� End()�ܿ� ȣ����� ����.
	virtual void End() = 0;

	void AllLevelStartEvent();
	void AllLevelEndEvent();

	void AllOnEvent();		//
	void AllOffEvent();		//

	//����������� ������Ʈ�� �� �ڽĵ��� ������Ʈ �������� ��� ���� ��� ����Ʈ�� ����ϴ� �Լ�.
	//���⿡ ���� ������Ʈ���� ���� �������� �����ȴ�. �ٷ� �������� �ʴ°Ϳ� ������ ��.
	void ReleaseObject(std::list<std::shared_ptr<GameEngineUpdateObject>>& _releaseList);

	//�� ������Ʈ�� �θ� ������Ʈ�� children_����Ʈ���� �����ϴ� �Լ�.
	virtual void DetachObject();

protected:
	//�� ������Ʈ�� �ڽĵ� �� Ư�� ������ �ڽĵ鸸 �޾ƺ��� �Լ�.
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
	std::list<std::shared_ptr<GameEngineUpdateObject>> children_;	//�ڽ� ������Ʈ��.

private:



private:
	int order_;			//������Ʈ ����.
	bool isReleaseUpdate_;	//true: Ư�� ������Ʈ�� ���� �ð��� ���.
	float deadTime_;	//���� ������Ʈ�� ��� ���� �ð�. �� �ð��� 0�̳� ������ �Ǹ� ���.
	float accTime_;		//������Ʈ ���� �������κ��� ���� �ð�.

	bool isUpdate_;	//true: ������Ʈ ����. false: ������Ʈ ����.
	bool isDead_;	//true: ��� ���� ����. false: ��� ���� �� ����. ���ó���� �ƴ� ��� �����ӿ� ����.

	std::weak_ptr<GameEngineUpdateObject> parent_;	//�θ� ������Ʈ.


};

