#pragma once
#include "Skill.h"

// Ό³Έν :
class Agility : public Skill
{
public:
	// constrcuter destructer
	Agility();
	~Agility();

	// delete Function
	Agility(const Agility& _Other) = delete;
	Agility(Agility&& _Other) noexcept = delete;
	Agility& operator=(const Agility& _Other) = delete;
	Agility& operator=(Agility&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

