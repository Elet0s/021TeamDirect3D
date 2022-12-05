#pragma once
#include "Skill.h"


class GodsWrath : public Skill
{
public:
	// constrcuter destructer
	GodsWrath();
	~GodsWrath();

	// delete Function
	GodsWrath(const GodsWrath& _Other) = delete;
	GodsWrath(GodsWrath&& _Other) noexcept = delete;
	GodsWrath& operator=(const GodsWrath& _Other) = delete;
	GodsWrath& operator=(GodsWrath&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

