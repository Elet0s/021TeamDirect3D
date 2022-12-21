#pragma once

class StageLevel : public GameEngineLevel
{
public:
	StageLevel();
	~StageLevel();


	StageLevel(const StageLevel& _Other) = delete;
	StageLevel(StageLevel&& _Other) noexcept = delete;
	StageLevel& operator=(const StageLevel& _Other) = delete;
	StageLevel& operator=(StageLevel&& _Other) noexcept = delete;

	GameEngineTextureRenderer* PlayerRenderer;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
private:
	void LevelStartEvent() override;
};