#pragma once
#include "Skill.h"
//(범위) 주변의 적에게 피해 치명타가 발생하지 않음
class DeathAura : public Skill
{
public:
	DeathAura();
	~DeathAura();

	DeathAura(const DeathAura& _Other) = delete;
	DeathAura(DeathAura&& _Other) noexcept = delete;
	DeathAura& operator=(const DeathAura& _Other) = delete;
	DeathAura& operator=(DeathAura&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

	CollisionReturn DeatAuraToMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	void RotateRenderer(float _deltaTime);

	void  StateSet();
private:
	GameEngineTextureRenderer* circleRendererA_;
	GameEngineTextureRenderer* circleRendererB_;
	GameEngineTextureRenderer* circleRendererC_;
	GameEngineTextureRenderer* circleRendererD_;
	GameEngineTextureRenderer* circleCenterRenderer_;

	GameEngineCollision* deathAuraCollision01_;
	GameEngineCollision* deathAuraCollision02_;
	GameEngineCollision* deathAuraCollision03_;

	WeaponInfo deathAuraWeaponInfo_;//무기 스탯


	float atkTimer_;

	float addRadian_;
	float damege;
	float attackSpeed;
	float rangeSize;
};

