#pragma once
#include "Skill.h"

class Healthy : public Skill
{
public:
	// constrcuter destructer
	Healthy();
	~Healthy();

	// delete Function
	Healthy(const Healthy& _Other) = delete;
	Healthy(Healthy&& _Other) noexcept = delete;
	Healthy& operator=(const Healthy& _Other) = delete;
	Healthy& operator=(Healthy&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

