#pragma once
#include "Skill.h"

// Ό³Έν :
class SharpeningStone : public Skill
{
public:
	// constrcuter destructer
	SharpeningStone();
	~SharpeningStone();

	// delete Function
	SharpeningStone(const SharpeningStone& _Other) = delete;
	SharpeningStone(SharpeningStone&& _Other) noexcept = delete;
	SharpeningStone& operator=(const SharpeningStone& _Other) = delete;
	SharpeningStone& operator=(SharpeningStone&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:
};

