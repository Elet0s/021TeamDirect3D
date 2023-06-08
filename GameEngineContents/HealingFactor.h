#pragma once
#include "Skill.h"

// Ό³Έν :
class HealingFactor : public Skill
{
public:
	// constrcuter destructer
	HealingFactor();
	~HealingFactor();

	// delete Function
	HealingFactor(const HealingFactor& _Other) = delete;
	HealingFactor(HealingFactor&& _Other) noexcept = delete;
	HealingFactor& operator=(const HealingFactor& _Other) = delete;
	HealingFactor& operator=(HealingFactor&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

