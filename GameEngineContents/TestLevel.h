#pragma once

class FieldRenderingActor;
class Monster;
class TestLevel : public GameEngineLevel
{
public:
	TestLevel();
	~TestLevel();

	TestLevel(const TestLevel& _Other) = delete;
	TestLevel(TestLevel&& _Other) noexcept = delete;
	TestLevel& operator=(const TestLevel& _Other) = delete;
	TestLevel& operator=(TestLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override {};
	void LevelStartEvent() override;
	void LevelEndEvent() override;

	void LevelManager();


private:
	void MouseMoveCamera();
	void PlayerMoveCamera();

private:
	std::shared_ptr<FieldRenderingActor> fieldRenderingActor_;
	std::shared_ptr<GameEngineLighting> testLevelLighting_;
};
