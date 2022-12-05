#pragma once
#include "Skill.h"

// Ό³Έν :
class Momentum : public Skill
{
public:
	// constrcuter destructer
	Momentum();
	~Momentum();

	// delete Function
	Momentum(const Momentum& _Other) = delete;
	Momentum(Momentum&& _Other) noexcept = delete;
	Momentum& operator=(const Momentum& _Other) = delete;
	Momentum& operator=(Momentum&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

