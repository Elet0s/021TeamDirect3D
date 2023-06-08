#pragma once
#include "Skill.h"

class IronWill : public Skill
{
public:
	// constrcuter destructer
	IronWill();
	~IronWill();

	// delete Function
	IronWill(const IronWill& _Other) = delete;
	IronWill(IronWill&& _Other) noexcept = delete;
	IronWill& operator=(const IronWill& _Other) = delete;
	IronWill& operator=(IronWill&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

