#pragma once

class GameEngineImageShotWindow : public GameEngineGUIWindow
{

public:
	GameEngineImageShotWindow() : renderTexture_(nullptr)
	{
	}

public:
	void RenderTextureSetting(ImTextureID _renderTexture, ImVec2 _size);

	void Initialize(GameEngineLevel* _level);
	void OnGUI(GameEngineLevel* _level, float _deltaTime) override;

private:
	ImTextureID renderTexture_;
	ImVec2 size_;
};


class GameEngineStatusWindow : public GameEngineGUIWindow
{

public:
	GameEngineStatusWindow();
	~GameEngineStatusWindow();

protected:
	GameEngineStatusWindow(const GameEngineStatusWindow& _other) = delete;
	GameEngineStatusWindow(GameEngineStatusWindow&& _other) noexcept = delete;

private:
	GameEngineStatusWindow& operator=(const GameEngineStatusWindow& _other) = delete;
	GameEngineStatusWindow& operator=(const GameEngineStatusWindow&& _other) = delete;


public:
	static void AddDebugRenderTarget(
		const std::string& _renderTargetName,
		class GameEngineRenderTarget* _renderTarget);

private:
	void Initialize(GameEngineLevel* _level) override;
	void OnGUI(GameEngineLevel* _level, float _deltaTime) override;

private:
	std::list<GameEngineImageShotWindow*> imageshotWindows_;
	static std::map<std::string, GameEngineRenderTarget*> debugRenderTargets_;

};

