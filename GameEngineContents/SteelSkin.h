#pragma once
#include "Skill.h"

// 설명 :
class SteelSkin : public Skill
{
public:
	// constrcuter destructer
	SteelSkin();
	~SteelSkin();

	// delete Function
	SteelSkin(const SteelSkin& _Other) = delete;
	SteelSkin(SteelSkin&& _Other) noexcept = delete;
	SteelSkin& operator=(const SteelSkin& _Other) = delete;
	SteelSkin& operator=(SteelSkin&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

