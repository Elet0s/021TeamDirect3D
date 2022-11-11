#pragma once
#include "GameEngineGUI.h"

class GameEngineImageShotWindow : public GameEngineGUIWindow
{

public:
	GameEngineImageShotWindow() : renderTexture_(nullptr)
	{
	}

public:
	void RenderTextureSetting(ImTextureID _renderTexture, ImVec2 _size);

	void Initialize(class GameEngineLevel* _level);
	void OnGUI(class GameEngineLevel* _level, float _deltaTime) override;

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
		std::shared_ptr<class GameEngineRenderTarget> _renderTarget);

private:
	void Initialize(class GameEngineLevel* _level) override;
	void OnGUI(class GameEngineLevel* _level, float _deltaTime) override;

private:
	std::list<std::shared_ptr<GameEngineImageShotWindow>> imageshotWindows_;
	static std::map<std::string, std::shared_ptr<class GameEngineRenderTarget>> debugRenderTargets_;

};

