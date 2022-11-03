#pragma once

// Ό³Έν :
class TileMapActor;
class Monster;
class TestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TestLevel();
	~TestLevel();

	// delete Function
	TestLevel(const TestLevel& _Other) = delete;
	TestLevel(TestLevel&& _Other) noexcept = delete;
	TestLevel& operator=(const TestLevel& _Other) = delete;
	TestLevel& operator=(TestLevel&& _Other) noexcept = delete;


	void CreateMapAndCamraMove();
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override {};
private:
	
	void UpdateWorld();
	void MoveWorld(int _Dir);

	std::vector<std::vector<TileMapActor*>> tilemaps_;
	
	std::vector<Monster*> Monster_;
	TileMapActor* tilemap;

	GameEngineCameraActor* tileCameraActor_;
};

