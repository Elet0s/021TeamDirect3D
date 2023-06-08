#pragma once
#include "Skill.h"

// Ό³Έν :
class Durability : public Skill
{
public:
	// constrcuter destructer
	Durability();
	~Durability();

	// delete Function
	Durability(const Durability& _Other) = delete;
	Durability(Durability&& _Other) noexcept = delete;
	Durability& operator=(const Durability& _Other) = delete;
	Durability& operator=(Durability&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

