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
	void HitEffect(float _deltaTime);

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;


	void ReduceHP(float _deltaTime);

	void GainExp(float _deltaTime);

private:
	//Player* player_;
	GameEngineTextureRenderer* playerHpMax_;
	GameEngineTextureRenderer* playerHpUi_;
	GameEngineTextureRenderer* playerHpRed_;
							 
	GameEngineTextureRenderer* playerExpMax_;
	GameEngineTextureRenderer* playerExpUi_;
	GameEngineTextureRenderer* playerExpBlue_;

	GameEngineFontRenderer* playerLevelUi_;

	float playerXindex_;
	float playerYindex_;
	
	float hpRedBar_;
	bool hpRedBarTregar_;

	float ExpBlueBar_;
	float ExpBlueBarTimer_;

	float HitDleta_;
};