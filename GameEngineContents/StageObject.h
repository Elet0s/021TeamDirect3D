#pragma once
#include "GlobalContentsValue.h"

struct StageInfo
{
	StageType stageType_ = StageType::Max;
	CombatType combatType_ = CombatType::Max;

	int killCount_ = 0;
	float timeLimit_ = 0.f;

	std::map<MonsterType, size_t> summoningMonsterCountMap_;
	size_t totalMonsterCount_ = 0;


	void SetStageInfo(const StageInfo& _stageInfo)
	{
		this->stageType_ = _stageInfo.stageType_;
		this->combatType_ = _stageInfo.combatType_;

		this->killCount_ = _stageInfo.killCount_;
		this->timeLimit_ = _stageInfo.timeLimit_;

		this->summoningMonsterCountMap_ = _stageInfo.summoningMonsterCountMap_;
		this->totalMonsterCount_ = _stageInfo.totalMonsterCount_;
	}

	void SetStageInfo(
		const StageType& _stageType,
		const CombatType& _combatType,
		int _killCount,
		float _time,
		const std::map<MonsterType, size_t>& _summoningMonsterCountMap,
		size_t _totalMonsterCount
	)
	{
		this->stageType_ = _stageType;
		this->combatType_ = _combatType;

		this->killCount_ = _killCount;
		this->timeLimit_ = _time;
		this->summoningMonsterCountMap_ = _summoningMonsterCountMap;
		this->totalMonsterCount_ = _totalMonsterCount;
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
		killCount_ = _level * 100;
	}
	
	std::list<StageObject*>& GetNextLevelList()
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

	CombatType GetCombatType()
	{
		return combatType_;
	}

	bool CheckNextLevel(StageObject* _nextlevel);
	void SetStageType(int _num);
	//void SetStageType(StageType _stageType);
	void SetMonsterCount(MonsterType _monsterType, size_t _monstercount);
	void PushNextlevel(StageObject* _nextlevel);
	
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

	GameEngineTextureRenderer* renderer_;
	std::list<StageObject*> nextLevels_;

	std::map<MonsterType, size_t> summoningMonsterCountMap_;
	size_t totalMonsterCount_;
};

