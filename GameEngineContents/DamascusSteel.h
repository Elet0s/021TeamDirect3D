#pragma once
#include "Skill.h"

class DamascusSteel : public Skill
{
public:
	// constrcuter destructer
	DamascusSteel();
	~DamascusSteel();

	// delete Function
	DamascusSteel(const DamascusSteel& _Other) = delete;
	DamascusSteel(DamascusSteel&& _Other) noexcept = delete;
	DamascusSteel& operator=(const DamascusSteel& _Other) = delete;
	DamascusSteel& operator=(DamascusSteel&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

