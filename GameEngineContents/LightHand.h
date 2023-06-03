#pragma once
#include "Skill.h"

// 설명 :
class LightHand : public Skill
{
public:
	// constrcuter destructer
	LightHand();
	~LightHand();

	// delete Function
	LightHand(const LightHand& _Other) = delete;
	LightHand(LightHand&& _Other) noexcept = delete;
	LightHand& operator=(const LightHand& _Other) = delete;
	LightHand& operator=(LightHand&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

