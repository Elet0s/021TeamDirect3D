#pragma once

class StateInfo
{
public:
	float stateTime_;	//�� ������Ʈ�� ���ݱ��� �󸶳� ���� ���ӵǾ���.
	std::string prevState_;	//���� ������Ʈ�� ������.

	StateInfo() : stateTime_(0.f), prevState_("")
	{
	}
};

class GameEngineStateManager;
class GameEngineState : public GameEngineNameObject
{
	friend GameEngineStateManager;

public:
	GameEngineState() : start_(nullptr), update_(nullptr), end_(nullptr)
	{
	}

public:
	void StateUpdate(float _deltaTime)
	{
		if (nullptr == update_)
		{
			return;
		}
		this->info_.stateTime_ += _deltaTime;
		update_(_deltaTime, info_);
	}

private:
	StateInfo info_;
	std::function<void(const StateInfo&)> start_;
	std::function<void(float, const StateInfo&)> update_;
	std::function<void(const StateInfo&)> end_;
};

class GameEngineStateManager final	//final: <-�� ������ �߰� ��� �Ұ�.
{
	//
public:
	GameEngineStateManager();
	~GameEngineStateManager();

	GameEngineStateManager(const GameEngineStateManager& _other) = delete;
	GameEngineStateManager(GameEngineStateManager&& _other) noexcept = delete;
	GameEngineStateManager& operator=(const GameEngineStateManager& _other) = delete;
	GameEngineStateManager& operator=(GameEngineStateManager&& _other) = delete;

public:
	void Update(float _deltaTime);

public:

	void CreateState(
		const std::string& _stateName,
		std::function<void(float, const StateInfo&)> _update,
		std::function<void(const StateInfo&)> _start = nullptr,
		std::function<void(const StateInfo&)> _end = nullptr
	)
	{
		if (allStates_.end() != allStates_.find(_stateName))
		{
			MsgBoxAssertString(_stateName + ": �̹� ���� �̸��� ������Ʈ�� �����մϴ�.");
			return;
		}

		GameEngineState& newState = allStates_[_stateName];
		newState.SetName(_stateName);

		if (nullptr != _update)
		{
			newState.update_ = _update;
		}	
		
		if (nullptr != _start)
		{
			newState.start_ = _start;
		}	
		
		if (nullptr != _end)
		{
			newState.end_ = _end;
		}
	}


	void ChangeState(const std::string& _stateName)
	{
		if (allStates_.end() == allStates_.find(_stateName))
		{
			MsgBoxAssertString(_stateName + ": �׷� �̸��� ������Ʈ�� �����ϴ�.");
			return;
		}

		std::string prevState = "";

		if (nullptr != currentState_)
		{
			prevState = currentState_->GetNameCopy();

			if (nullptr != currentState_->end_)
			{
				currentState_->end_(currentState_->info_);
			}
		}

		currentState_ = &allStates_[_stateName];
		currentState_->info_.stateTime_ = 0.f;
		currentState_->info_.prevState_ = prevState;

		if (nullptr != currentState_->start_)
		{
			currentState_->start_(currentState_->info_);
		}
	}

	const std::string& GetCurrentStateName()
	{
		if (nullptr == currentState_)
		{
			return "";
		}

		return currentState_->GetNameCopy();
	}

	float GetCurrentStateTime()
	{
		if (nullptr == currentState_)
		{
			return 0.f;
		}

		return currentState_->info_.stateTime_;
	}
private:
	//
	std::map<std::string, GameEngineState> allStates_;
	GameEngineState* currentState_;

};

