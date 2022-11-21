#pragma once

class GameEngineTextureRenderer;
class Texture2DShadowRenderer;
class MyTileMapRenderer;
class TileMapActor : public GameEngineActor
{

public:
	TileMapActor();
	~TileMapActor();

protected:
	TileMapActor(const TileMapActor& _other) = delete;
	TileMapActor(TileMapActor&& _other) noexcept = delete;

private:
	TileMapActor& operator=(const TileMapActor& _other) = delete;
	TileMapActor& operator=(const TileMapActor&& _other) = delete;


public:	
	std::shared_ptr<MyTileMapRenderer> tileRenderer_;
	std::shared_ptr<GameEngineCollision> col_;
	std::vector<std::shared_ptr<GameEngineTextureRenderer>> renderers_;
	std::vector<std::shared_ptr<Texture2DShadowRenderer>> shadowRenderers_;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

private:
	bool renderOn;
	void ResourceLoad();
	CollisionReturn CameraCheck(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
};

