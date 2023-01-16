#pragma once

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
	void SoundCheck();


private:
	bool soundCheck_;
	class WorldMapRenderingActor* WorldMapRenderingActor_;
	GameEngineLighting* WorldLevelLighting_;
	class StageCreater* stageCreater_;
	class Mouse* mousePointer_;
	class StageUI* stageUI_;
};