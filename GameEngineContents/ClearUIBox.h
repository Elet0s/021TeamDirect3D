#pragma once

// 설명 :
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
	class SoulCardSelectBox* soulCardSelectBox_;

	GameEngineTextureRenderer* mainrenderer_;
	GameEngineTextureRenderer* button1renderer_;
	GameEngineTextureRenderer* button2renderer_;
	GameEngineTextureRenderer* button3renderer_;

	GameEngineFontRenderer* button1FontRenderer_;
	GameEngineFontRenderer* button2FontRenderer_;
	GameEngineFontRenderer* button3FontRenderer_;

	class Mouse* mousePointer_;

	bool button1On_;
	bool button2On_;

	int gold_;

	void RendererOn();
	void RendererOff();
	void Start()override;
	void Update(float _deltaTime) override;
	void End()  override {};

};

