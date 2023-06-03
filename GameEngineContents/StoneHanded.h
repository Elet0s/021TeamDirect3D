#pragma once
#include "Skill.h"

// 설명 :
class StoneHanded : public Skill
{
public:
	// constrcuter destructer
	StoneHanded();
	~StoneHanded();

	// delete Function
	StoneHanded(const StoneHanded& _Other) = delete;
	StoneHanded(StoneHanded&& _Other) noexcept = delete;
	StoneHanded& operator=(const StoneHanded& _Other) = delete;
	StoneHanded& operator=(StoneHanded&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

protected:

private:

};

