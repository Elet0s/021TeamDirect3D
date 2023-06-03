#pragma once

// 설명 :
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

	class SoulCardSelectBox* soulCardSelectBox_;

	GameEngineTextureRenderer* mainrenderer_;
	std::vector<class ShopButton*> buttons_;

	GameEngineTextureRenderer* buttonrenderer_;
	GameEngineFontRenderer* buttonFontRenderer_;


	bool soundCheck_;

	void Start()override;
	void Update(float _deltaTime) override;
	void End()  override {};

	void LevelStartEvent() override;
};

