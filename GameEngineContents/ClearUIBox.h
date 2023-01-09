#pragma once

// Ό³Έν :
class ClearUIBox : public GameEngineActor
{
public:
	// constrcuter destructer
	ClearUIBox();
	~ClearUIBox();

	// delete Function
	ClearUIBox(const ClearUIBox& _Other) = delete;
	ClearUIBox(ClearUIBox&& _Other) noexcept = delete;
	ClearUIBox& operator=(const ClearUIBox& _Other) = delete;
	ClearUIBox& operator=(ClearUIBox&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<class SoulCardSelectBox> soulCardSelectBox_;

	std::shared_ptr<GameEngineTextureRenderer> mainrenderer_;
	std::shared_ptr<GameEngineTextureRenderer> button1renderer_;
	std::shared_ptr<GameEngineTextureRenderer> button2renderer_;
	std::shared_ptr<GameEngineTextureRenderer> button3renderer_;

	std::shared_ptr<GameEngineFontRenderer> button1FontRenderer_;
	std::shared_ptr<GameEngineFontRenderer> button2FontRenderer_;
	std::shared_ptr<GameEngineFontRenderer> button3FontRenderer_;

	std::shared_ptr<class Mouse> mousePointer_;

	bool button1On_;
	bool button2On_;

	void RendererOn();
	void RendererOff();
	void Start()override;
	void Update(float _deltaTime) override;
	void End()  override {};
	
};

