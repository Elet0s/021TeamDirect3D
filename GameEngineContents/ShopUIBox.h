#pragma once

// Ό³Έν :
class ShopUIBox : public GameEngineActor
{
public:
	// constrcuter destructer
	ShopUIBox();
	~ShopUIBox();

	// delete Function
	ShopUIBox(const ShopUIBox& _Other) = delete;
	ShopUIBox(ShopUIBox&& _Other) noexcept = delete;
	ShopUIBox& operator=(const ShopUIBox& _Other) = delete;
	ShopUIBox& operator=(ShopUIBox&& _Other) noexcept = delete;

protected:

private:
	void RenderOn();
	void RenderOff();
	void ShopReset();

	std::shared_ptr<class SoulCardSelectBox> soulCardSelectBox_;

	std::shared_ptr<GameEngineTextureRenderer> mainrenderer_;
	std::vector<std::shared_ptr<class ShopButton>> buttons_;

	std::shared_ptr<GameEngineTextureRenderer> buttonrenderer_;
	std::shared_ptr<GameEngineFontRenderer> buttonFontRenderer_;


	bool soundCheck_;

	void Start()override;
	void Update(float _deltaTime) override;
	void End()  override {};

	void LevelStartEvent() override;
};

