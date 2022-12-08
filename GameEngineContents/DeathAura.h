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
protected:
	std::shared_ptr<GameEngineCollision> Collision_;
private:
	float damege;
	float attackSpeed;
	float rangeSize;
};

