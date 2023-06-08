#pragma once
#include "Skill.h"

// 설명 :
class StoneSkin : public Skill
{
public:
	// constrcuter destructer
	StoneSkin();
	~StoneSkin();

	// delete Function
	StoneSkin(const StoneSkin& _Other) = delete;
	StoneSkin(StoneSkin&& _Other) noexcept = delete;
	StoneSkin& operator=(const StoneSkin& _Other) = delete;
	StoneSkin& operator=(StoneSkin&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

