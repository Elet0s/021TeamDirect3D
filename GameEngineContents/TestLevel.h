#pragma once

class TileMapActor;
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


	void CreateMapAndCamraMove();

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override {};
	void LevelStartEvent()override;
	void LevelEndEvent()override;
private:

	void UpdateWorld();
	void MoveWorld(int _Dir);
	void MouseMoveCamera();
	void PlayerMoveCamera();
	std::vector<std::vector<std::shared_ptr<TileMapActor>>> tilemaps_;


	//GameEngineCameraActor* tileCameraActor_;
};
