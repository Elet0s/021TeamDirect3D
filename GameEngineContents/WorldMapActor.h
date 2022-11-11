#pragma once

// Ό³Έν :
class MyWorldMapRenderer;
class WorldMapActor : public GameEngineActor
{
public:
	// constrcuter destructer
	WorldMapActor();
	~WorldMapActor();

	// delete Function
	WorldMapActor(const WorldMapActor& _Other) = delete;
	WorldMapActor(WorldMapActor&& _Other) noexcept = delete;
	WorldMapActor& operator=(const WorldMapActor& _Other) = delete;
	WorldMapActor& operator=(WorldMapActor&& _Other) noexcept = delete;

public:
	std::shared_ptr<MyWorldMapRenderer> worldmaprenderer_;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

};

