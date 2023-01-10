#pragma once

enum class UIType
{
	World,
	Stage,
	Claer
};
// 설명 :
class StageUI : public GameEngineActor
{
public:
	// constrcuter destructer
	StageUI();
	~StageUI();

	// delete Function
	StageUI(const StageUI& _Other) = delete;
	StageUI(StageUI&& _Other) noexcept = delete;
	StageUI& operator=(const StageUI& _Other) = delete;
	StageUI& operator=(StageUI&& _Other) noexcept = delete;

	void SetStageText(const std::string& _Text)
	{
		stagefontrenderer_->SetText("스테이지 : " + _Text, "Free Pixel");
	}

	void SetCoinText(const std::string& _Text)
	{
		coinfontrenderer_->SetText(_Text, "Free Pixel");
	}

	void SetSoulCoinText(const std::string& _Text)
	{
		soulfontrenderer_->SetText(_Text, "Free Pixel");
	}

	void SoulCoinRenderersOff();
	
	void SetUI(UIType _type);

	void SoulCoinRenderersOn();
protected:

private:
	std::shared_ptr<GameEngineFontRenderer> stagefontrenderer_;
	std::shared_ptr<GameEngineFontRenderer> spacefontrenderer_;
	std::shared_ptr<GameEngineFontRenderer> coinfontrenderer_;
	std::shared_ptr<GameEngineFontRenderer> soulfontrenderer_;

	std::shared_ptr<GameEngineFontRenderer> killcountfontrenderer_;


	std::shared_ptr<GameEngineTextureRenderer> coinrenderer_;
	std::shared_ptr<GameEngineTextureRenderer> soulrenderer_;


	std::shared_ptr<GameEngineTextureRenderer> stageboxrenderer_;
	std::shared_ptr<GameEngineTextureRenderer> spaceboxrenderer_;
	std::shared_ptr<GameEngineTextureRenderer> coinboxrenderer_;
	std::shared_ptr<GameEngineTextureRenderer> soulboxrenderer_;

	std::shared_ptr<GameEngineTextureRenderer> killcountboxrenderer_;

	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	
	void StageSetting();
	void WorldSetting();
	void ClearSetting();
	void AllOff();
	void UIUpdate();

	UIType mytype_;
	int goalCount_;
};

