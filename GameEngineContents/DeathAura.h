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

	CollisionReturn ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

private:
	std::shared_ptr<GameEngineTextureRenderer> circleRendererA_;
	std::shared_ptr<GameEngineTextureRenderer> circleRendererB_;
	std::shared_ptr<GameEngineTextureRenderer> circleRendererC_;
	std::shared_ptr<GameEngineTextureRenderer> circleRendererD_;
	std::shared_ptr<GameEngineTextureRenderer> circleCenterRenderer_;
	std::shared_ptr<GameEngineCollision> deathAuraCollision_;
	float damege;
	float attackSpeed;
	float rangeSize;
};

