#pragma once
#include "Skill.h"

class Penetration : public Skill
{
public:
	// constrcuter destructer
	Penetration();
	~Penetration();

	// delete Function
	Penetration(const Penetration& _Other) = delete;
	Penetration(Penetration&& _Other) noexcept = delete;
	Penetration& operator=(const Penetration& _Other) = delete;
	Penetration& operator=(Penetration&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

