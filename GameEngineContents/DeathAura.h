#pragma once
#include "Skill.h"
// Ό³Έν :
class DeathAura : public Skill
{
public:
	// constrcuter destructer
	DeathAura();
	~DeathAura();

	// delete Function
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

private:
	float damege;
	float attackSpeed;
	float rangeSize;
};

