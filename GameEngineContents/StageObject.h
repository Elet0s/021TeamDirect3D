#pragma once
enum class StageType
{
	ComBat,
	Elite,
	Chest,
	Event,
	Boss,
	Empty,
	Max
};

enum class ComBatType
{
	TimeAttack,
	Kill,
	EilteKill,
	BossKill,
	Max
};
// Ό³Έν :
class StageObject : public GameEngineActor
{
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
	void SetComBatType(int _num);
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
	ComBatType comBatType_;

	std::shared_ptr<GameEngineCollision> col_;
	std::shared_ptr<GameEngineTextureRenderer> renderer_;
	std::list<std::shared_ptr<StageObject>> nextLevels_;
};

