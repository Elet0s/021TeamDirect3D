#pragma once

enum class Appear
{
	True,
	False,
};

// Ό³Έν :
class Skill;
class SoulCardUI : public GameEngineActor
{
public:
	// constrcuter destructer
	SoulCardUI();
	~SoulCardUI();

	// delete Function
	SoulCardUI(const SoulCardUI& _Other) = delete;
	SoulCardUI(SoulCardUI&& _Other) noexcept = delete;
	SoulCardUI& operator=(const SoulCardUI& _Other) = delete;
	SoulCardUI& operator=(SoulCardUI&& _Other) noexcept = delete;

	void Setting();
protected:

private:
	std::shared_ptr<GameEngineTextureRenderer> linerenderer_;
	std::shared_ptr<GameEngineTextureRenderer> template_;
	std::shared_ptr<GameEngineTextureRenderer> icon_;
	std::vector<std::shared_ptr<GameEngineFontRenderer>> etc_;
	std::shared_ptr<GameEngineFontRenderer> skillName_;
	std::shared_ptr<GameEngineFontRenderer> Level_;
	std::shared_ptr<GameEngineFontRenderer> Rank_;
	std::shared_ptr<GameEngineCollision> cardColision_;
	
	std::shared_ptr<Skill> mySkill_;

	float alphaTexture_;
	float4 TextColor_;
	float4 RankColor_;
	Appear ColorCheck_;


	void Start() override;
	void Update(float _deltaTime);
	void End() override {};

	void CardDraw();
	void ColorChange(Appear _Value);
	


	
};

