#pragma once

class GameEngineTextureRenderer;
class MetaSpriteWindow: public GameEngineGUIWindow
{
	friend class MetaLevel;
public:
	MetaSpriteWindow();
	~MetaSpriteWindow();

protected:
	MetaSpriteWindow(const MetaSpriteWindow& _other) = delete;
	MetaSpriteWindow(MetaSpriteWindow&& _other) noexcept = delete;

private:
	MetaSpriteWindow& operator=(const MetaSpriteWindow& _other) = delete;
	MetaSpriteWindow& operator=(const MetaSpriteWindow&& _other) = delete;


public:	

protected:
	void Initialize(GameEngineLevel* _level) override;
	void OnGUI(GameEngineLevel* _level, float _deltaTime) override;

private:
	void MetaFileButton(GameEngineLevel* _level);
	void AtlasFileButton(GameEngineLevel* _level);

private:
	int curFrame_;
	GameEngineTextureRenderer* renderer_;

	GameEngineDirectory metaDir_;
	GameEngineTexture* targetTexture_;

	std::string curMetaFolder_;
	std::string curAtlasFolder_;

	std::string curMetaFile_;
	std::string curAtlasFile_;


};

