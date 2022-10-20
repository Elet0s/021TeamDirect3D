#pragma once

class TileMapActor;
class MapEditorWindow: public GameEngineGUIWindow
{
	friend class MapEditorLevel;

public:
	MapEditorWindow();
	~MapEditorWindow();

protected:
	MapEditorWindow(const MapEditorWindow& _other) = delete;
	MapEditorWindow(MapEditorWindow&& _other) noexcept = delete;

private:
	MapEditorWindow& operator=(const MapEditorWindow& _other) = delete;
	MapEditorWindow& operator=(const MapEditorWindow&& _other) = delete;


public:	


protected:
	void Initialize(GameEngineLevel* _level) override;
	void OnGUI(GameEngineLevel* _level, float _deltaTime) override;

private:
	TileMapActor* tileMap_;
	std::string selectFolderTexture_;
	int scale_[2];
	size_t selectTile_;



};

