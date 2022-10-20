#pragma once

class TileMapActor;
class MapEditorLevel: public GameEngineLevel
{

public:
	MapEditorLevel();
	~MapEditorLevel();

protected:
	MapEditorLevel(const MapEditorLevel& _other) = delete;
	MapEditorLevel(MapEditorLevel&& _other) noexcept = delete;

private:
	MapEditorLevel& operator=(const MapEditorLevel& _other) = delete;
	MapEditorLevel& operator=(const MapEditorLevel&& _other) = delete;

public:	


protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;


private:
	void LevelStartEvent() override;

private:
	TileMapActor* tileMap_;

};

