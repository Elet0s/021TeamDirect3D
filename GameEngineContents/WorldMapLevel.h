#pragma once

//class TestActor;
class WorldMapLevel : public GameEngineLevel
{
public:
	WorldMapLevel();
	~WorldMapLevel();

	WorldMapLevel(const WorldMapLevel& _Other) = delete;
	WorldMapLevel(WorldMapLevel&& _Other) noexcept = delete;
	WorldMapLevel& operator=(const WorldMapLevel& _Other) = delete;
	WorldMapLevel& operator=(WorldMapLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

private:
	void LevelStartEvent() override;
	void UpdateCameraMovement(float _deltaTime);
	void CheckNextStageSelection();


private:

	std::shared_ptr<class WorldMapRenderingActor> WorldMapRenderingActor_;
	std::shared_ptr<GameEngineLighting> WorldLevelLighting_;
	//std::shared_ptr<TestActor> TestActor_;
	std::shared_ptr<class StageCreater> stageCreater_;
	std::shared_ptr<class Mouse> mousePointer_;
};