#pragma once

class StageObject;
class PlayerObject;
class StageCreater : public GameEngineActor
{
	friend class WorldMapLevel;

public:
	// constrcuter destructer
	StageCreater();
	~StageCreater();

	// delete Function
	StageCreater(const StageCreater& _Other) = delete;
	StageCreater(StageCreater&& _Other) noexcept = delete;
	StageCreater& operator=(const StageCreater& _Other) = delete;
	StageCreater& operator=(StageCreater&& _Other) noexcept = delete;



public:
	std::shared_ptr<StageObject>& GetCurLevel()
	{
		return curlevel_;
	}

private:
	void LevelStartEvent() override;
	void Start() override;
	void Update(float _deltaTime) override;
	void SendPlayerToNextStage(std::weak_ptr<StageObject> _nextStageObject);

private:
	std::shared_ptr<StageObject> curlevel_;
	std::shared_ptr<PlayerObject> playerObject_;
	std::map<int, std::list<std::shared_ptr<StageObject>>> stageObjects_;
};

