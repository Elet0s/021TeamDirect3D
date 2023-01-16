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
	StageObject* GetCurLevel()
	{
		return curlevel_;
	}

private:
	void LevelStartEvent() override;
	void Start() override;
	void Update(float _deltaTime) override;
	void SendPlayerToNextStage(StageObject* _nextStageObject);

private:
	StageObject* curlevel_;
	PlayerObject* playerObject_;
	std::map<int, std::list<StageObject*>> stageObjects_;
};

