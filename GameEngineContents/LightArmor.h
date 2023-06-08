#pragma once
#include "Skill.h"

// Ό³Έν :
class LightArmor : public Skill
{
public:
	// constrcuter destructer
	LightArmor();
	~LightArmor();

	// delete Function
	LightArmor(const LightArmor& _Other) = delete;
	LightArmor(LightArmor&& _Other) noexcept = delete;
	LightArmor& operator=(const LightArmor& _Other) = delete;
	LightArmor& operator=(LightArmor&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

