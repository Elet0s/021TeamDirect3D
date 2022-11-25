#pragma once

// ���� :
class SoulCardUI : public GameEngineActor
{
public:
	// constrcuter destructer
	SoulCardUI();
	~SoulCardUI();

	// delete Function
	SoulCardUI(const SoulCardUI& _Other) = delete;
	SoulCardUI(SoulCardUI&& _Other) noexcept = delete;
	SoulCardUI& operator=(const SoulCardUI& _Other) = delete;
	SoulCardUI& operator=(SoulCardUI&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineTextureRenderer> template_;
	std::shared_ptr<GameEngineTextureRenderer> icon_;

	void Start() override;
	void Update(float _deltaTime);
	void End() override {};
};

