#pragma once
class Player;
class PlayerUI : public GameEngineActor
{
public:
	PlayerUI();
	~PlayerUI();


	PlayerUI(const PlayerUI& _Other) = delete;
	PlayerUI(PlayerUI&& _Other) noexcept = delete;
	PlayerUI& operator=(const PlayerUI& _Other) = delete;
	PlayerUI& operator=(PlayerUI&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	void HitEffect();
	void ReduceHP(float _deltaTime);
private:
	std::weak_ptr<Player> player_;
	std::shared_ptr<GameEngineTextureRenderer> playerHpMax_;
	std::shared_ptr<GameEngineTextureRenderer> playerHpUi_;
	std::shared_ptr<GameEngineTextureRenderer> playerHpRed_;
	float hpRedBar_;
	bool hpRedBarTregar_;
};