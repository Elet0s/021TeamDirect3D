#pragma once

class TileMapRenderer;
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
	TileMapRenderer* tileRenderer_;

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

private:

};

