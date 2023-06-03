#pragma once
#include "Skill.h"

class Compromise : public Skill
{
public:
	// constrcuter destructer
	Compromise();
	~Compromise();

	// delete Function
	Compromise(const Compromise& _Other) = delete;
	Compromise(Compromise&& _Other) noexcept = delete;
	Compromise& operator=(const Compromise& _Other) = delete;
	Compromise& operator=(Compromise&& _Other) noexcept = delete;
	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

