#pragma once

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

	void SoulCoinRenderersOn();
protected:

private:
	GameEngineFontRenderer* stagefontrenderer_;
	GameEngineFontRenderer* spacefontrenderer_;
	GameEngineFontRenderer* coinfontrenderer_;
	GameEngineFontRenderer* soulfontrenderer_;

	GameEngineTextureRenderer* coinrenderer_;
	GameEngineTextureRenderer* soulrenderer_;

	GameEngineTextureRenderer* stageboxrenderer_;
	GameEngineTextureRenderer* spaceboxrenderer_;
	GameEngineTextureRenderer* coinboxrenderer_;
	GameEngineTextureRenderer* soulboxrenderer_;

	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;



};

