#pragma once
#include "GlobalContentsValue.h"

class Mouse;
class FieldRenderingActor;
class TestLevel : public GameEngineLevel
{
public:
	TestLevel();
	~TestLevel();

	TestLevel(const TestLevel& _Other) = delete;
	TestLevel(TestLevel&& _Other) noexcept = delete;
	TestLevel& operator=(const TestLevel& _Other) = delete;
	TestLevel& operator=(TestLevel&& _Other) noexcept = delete;

	std::shared_ptr<Mouse> GetMousePointer()
	{
		return mousePointer_;
	}
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override {};
	void LevelStartEvent() override;
	void LevelEndEvent() override;


private:
	void MouseMoveCamera();
	void PlayerMoveCamera();

private:
	std::shared_ptr<FieldRenderingActor> fieldRenderingActor_;
	std::shared_ptr<GameEngineLighting> testLevelLighting_;
	std::shared_ptr<Mouse> mousePointer_;
	std::shared_ptr<class StageUI> stageUI_;



	StageType stageType_;
	CombatType combatType_;

	int killCount_;
	float time_;



};
