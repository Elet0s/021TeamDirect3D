#pragma once

// 설명 :
class DashUI : public GameEngineActor
{
public:
	// constrcuter destructer
	DashUI();
	~DashUI();

	// delete Function
	DashUI(const DashUI& _Other) = delete;
	DashUI(DashUI&& _Other) noexcept = delete;
	DashUI& operator=(const DashUI& _Other) = delete;
	DashUI& operator=(DashUI&& _Other) noexcept = delete;

protected:

private:
	GameEngineTextureRenderer* templaterenderer_;
	std::vector <GameEngineTextureRenderer*> dashrenderers_;

	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void TemplateSetting();
	void DashRenderersSetting();
	void DashRendererChange();

	int dashMaxCount_; // 대쉬 최대 충전 개수
	int currentDashCount_; // 현재까지 충전된 대쉬의 수
};

