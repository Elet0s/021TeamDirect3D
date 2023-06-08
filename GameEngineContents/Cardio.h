#pragma once
#include "Skill.h"

class Cardio : public Skill
{
public:
	// constrcuter destructer
	Cardio();
	~Cardio();

	// delete Function
	Cardio(const Cardio& _Other) = delete;
	Cardio(Cardio&& _Other) noexcept = delete;
	Cardio& operator=(const Cardio& _Other) = delete;
	Cardio& operator=(Cardio&& _Other) noexcept = delete;
	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

