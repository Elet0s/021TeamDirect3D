#pragma once
#include "Skill.h"

// 설명 :
class DashCooldown : public Skill
{
public:
	// constrcuter destructer
	DashCooldown();
	~DashCooldown();

	// delete Function
	DashCooldown(const DashCooldown& _Other) = delete;
	DashCooldown(DashCooldown&& _Other) noexcept = delete;
	DashCooldown& operator=(const DashCooldown& _Other) = delete;
	DashCooldown& operator=(DashCooldown&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

