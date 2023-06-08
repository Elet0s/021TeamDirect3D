#pragma once

enum class Appear
{
	True,
	False,
};

// 설명 :
class Skill;
class SoulCardUI : public GameEngineActor
{
	friend class SoulCardSelectBox;
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

	void CardRelease();
protected:

private:
	GameEngineTextureRenderer* linerenderer_;
	GameEngineTextureRenderer* template_;
	GameEngineTextureRenderer* icon_;
	std::vector<GameEngineFontRenderer*> etc_;
	GameEngineFontRenderer* skillName_;
	GameEngineFontRenderer* Level_;
	GameEngineFontRenderer* Rank_;
	GameEngineCollision* cardColision_;

	Skill* mySkill_;

	float alphaTexture_;
	float4 TextColor_;
	float4 RankColor_;
	bool soundCheck_;
	Appear ColorCheck_;


	void Start() override;
	void Update(float _deltaTime);
	void End() override {};

	void CardDraw();
	void WeaponDraw();
	void ColorChange(Appear _Value);




};

