#pragma once
class MagicCircle :public GameEngineActor
{
public:
	MagicCircle();
	~MagicCircle();

	MagicCircle(const MagicCircle& _Other) = delete;
	MagicCircle(MagicCircle&& _Other) noexcept = delete;
	MagicCircle& operator=(const MagicCircle& _Other) = delete;
	MagicCircle& operator=(MagicCircle&& _Other) noexcept = delete;
public:
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	void RotateRenderer(float _deltaTime);
	void TimeOff(float _deltaTime);
	void LevelEndEvent() override;

private:
	float timer_;
	float addRadian_;

	std::shared_ptr<GameEngineTextureRenderer> magicCircle01_;
	std::shared_ptr<GameEngineTextureRenderer> magicCircle02_;
	std::shared_ptr<GameEngineTextureRenderer> magicCircle03_;
};