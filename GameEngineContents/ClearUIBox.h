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
	std::shared_ptr<GameEngineTextureRenderer> mainrenderer_;
	std::shared_ptr<GameEngineTextureRenderer> button1renderer_;
	std::shared_ptr<GameEngineTextureRenderer> button2renderer_;

	std::shared_ptr<GameEngineCollision> button1Col_;
	std::shared_ptr<GameEngineCollision> button2Col_;

	void Start()override;
	void Update(float _deltaTime) override;
	void End()  override {};
};

