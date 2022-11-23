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

	void GainExp(float _deltaTime);
private:
	std::weak_ptr<Player> player_;
	std::shared_ptr<GameEngineTextureRenderer> playerHpMax_;
	std::shared_ptr<GameEngineTextureRenderer> playerHpUi_;
	std::shared_ptr<GameEngineTextureRenderer> playerHpRed_;

	std::shared_ptr<GameEngineTextureRenderer> playerExpMax_;
	std::shared_ptr<GameEngineTextureRenderer> playerExpUi_;
	std::shared_ptr<GameEngineTextureRenderer> playerExpBlue_;

	std::shared_ptr<GameEngineFontRenderer>playerLevelUi_;

	float playerXindex_;
	float playerYindex_;
	
	float hpRedBar_;
	bool hpRedBarTregar_;

	float ExpBlueBar_;
	float ExpBlueBarTimer_;
};