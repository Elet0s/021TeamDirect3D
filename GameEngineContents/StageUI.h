#pragma once

enum class UIType
{
	World,
	Stage,
	Claer,
	Shop,
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

	void SetUI(UIType _type);

protected:

private:
	GameEngineFontRenderer* stagefontrenderer_;
	GameEngineFontRenderer* spacefontrenderer_;
	GameEngineFontRenderer* coinfontrenderer_;

	GameEngineFontRenderer* killcountfontrenderer_;
	GameEngineFontRenderer* elitekillFontrenderer_;

	GameEngineFontRenderer* timerfontRenderer_;
	GameEngineTextureRenderer* timerboxrenderer_;

	GameEngineTextureRenderer* coinrenderer_;


	GameEngineTextureRenderer* stageboxrenderer_;
	GameEngineTextureRenderer* spaceboxrenderer_;
	GameEngineTextureRenderer* coinboxrenderer_;

	GameEngineTextureRenderer* killcountboxrenderer_;

	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void StageSetting();
	void WorldSetting();
	void ClearSetting();
	void AllOff();
	void UIUpdate();
	void TimeSet();
	void TimeCounter();

	bool IsClear_;
	float time_;
	UIType mytype_;
	int goalCount_;
};

