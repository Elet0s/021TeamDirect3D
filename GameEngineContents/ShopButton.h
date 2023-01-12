#pragma once

// 설명 :
class ShopButton : public GameEngineActor
{
public:
	// constrcuter destructer
	ShopButton();
	~ShopButton();

	// delete Function
	ShopButton(const ShopButton& _Other) = delete;
	ShopButton(ShopButton&& _Other) noexcept = delete;
	ShopButton& operator=(const ShopButton& _Other) = delete;
	ShopButton& operator=(ShopButton&& _Other) noexcept = delete;

	void SetText(const std::string& _str);

	void CreateClickEvent(std::function<void()> _click)
	{
		click_ = _click;
	};

	float4x4 GetRendererMatrix()
	{
		return renderer_->GetTransformData().worldWorldMatrix_;
	}

	void SetPrice(size_t _price);

	void SetIsApper(bool _val)
	{
		IsApper = _val;
	}

	bool GetIsApper()
	{
		return IsApper;
	}
protected:

private:
	std::shared_ptr<GameEngineTextureRenderer> renderer_;
	std::shared_ptr<GameEngineFontRenderer> fontRenderer_;
	std::shared_ptr<GameEngineFontRenderer> PricefontRenderer_;
	std::function<void()> click_;

	size_t price_;
	bool IsApper;   // 다른 UI를 띄우기 위해 잠시 렌더더를 끄고 킬 때 계속꺼놓을지 킬지를 알기위한 변수


	void Start();
	void Update(float _deltaTime)override;
	void End() override;
};

