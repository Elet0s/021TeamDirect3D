#pragma once
#include "GlobalContentsValue.h"

struct StageInfo
{
	StageType stageType_ = StageType::Max;
	CombatType combatType_ = CombatType::Max;

	int killCount_ = 0;
	float time_ = 0.f;


	void SetStageInfo(const StageInfo& _stageInfo)
	{
		this->stageType_ = _stageInfo.stageType_;
		this->combatType_ = _stageInfo.combatType_;

		this->killCount_ = _stageInfo.killCount_;
		this->time_ = _stageInfo.time_;
	}

	void SetStageInfo(const StageType& _stageType, const CombatType& _combatType, int _killCount, float _time)
	{
		this->stageType_ = _stageType;
		this->combatType_ = _combatType;

		this->killCount_ = _killCount;
		this->time_ = _time;
	}
};

class StageObject : public GameEngineActor
{
	friend class StageCreater;

	static StageInfo nextStageInfo_;

public:
	// constrcuter destructer
	StageObject();
	~StageObject();

	// delete Function
	StageObject(const StageObject& _Other) = delete;
	StageObject(StageObject&& _Other) noexcept = delete;
	StageObject& operator=(const StageObject& _Other) = delete;
	StageObject& operator=(StageObject&& _Other) noexcept = delete;

public:
	static const StageInfo& GetNextStageInfo()
	{
		return nextStageInfo_;
	}

	void SetMyLevel(int _level)
	{
		myLevel_ = _level;
	}
	
	std::list<std::shared_ptr<StageObject>>& GetNextLevelList()
	{
		return nextLevels_;
	}

	bool IsNextLevelEmpty()
	{
		if (nextLevels_.size() == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	const float4x4& GetWorldWorldMatrix() const
	{
		return renderer_->GetTransformData().worldWorldMatrix_;
	}

	bool CheckNextLevel(std::shared_ptr<StageObject> _nextlevel);
	void SetStageType(int _num);
	void SetCombatType(int _num);
	void PushNextlevel(std::shared_ptr<StageObject> _nextlevel);
	
	float posY_;


private:
	void Start() override;
	void Update(float _deltaTime) override;

private:
	int myLevel_;
	int killCount_;
	float time_;
	StageType stageType_;
	CombatType combatType_;

	//std::shared_ptr<GameEngineCollision> col_;
	std::shared_ptr<GameEngineTextureRenderer> renderer_;
	std::list<std::shared_ptr<StageObject>> nextLevels_;
};

