#pragma once
#include "Skill.h"

// Ό³Έν :
class Dash : public Skill
{
public:
	// constrcuter destructer
	Dash();
	~Dash();

	// delete Function
	Dash(const Dash& _Other) = delete;
	Dash(Dash&& _Other) noexcept = delete;
	Dash& operator=(const Dash& _Other) = delete;
	Dash& operator=(Dash&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

