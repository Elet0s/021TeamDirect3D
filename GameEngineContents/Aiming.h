#pragma once
#include "Skill.h"

class Aiming : public Skill
{
public:
	// constrcuter destructer
	Aiming();
	~Aiming();

	// delete Function
	Aiming(const Aiming& _Other) = delete;
	Aiming(Aiming&& _Other) noexcept = delete;
	Aiming& operator=(const Aiming& _Other) = delete;
	Aiming& operator=(Aiming&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

