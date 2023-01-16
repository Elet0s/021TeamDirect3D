#pragma once

// ���� :
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

	int dashMaxCount_; // �뽬 �ִ� ���� ����
	int currentDashCount_; // ������� ������ �뽬�� ��
};

