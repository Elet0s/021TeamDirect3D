#pragma once
#include "Skill.h"

// 설명 :
class SlipperySkin : public Skill
{
public:
	// constrcuter destructer
	SlipperySkin();
	~SlipperySkin();

	// delete Function
	SlipperySkin(const SlipperySkin& _Other) = delete;
	SlipperySkin(SlipperySkin&& _Other) noexcept = delete;
	SlipperySkin& operator=(const SlipperySkin& _Other) = delete;
	SlipperySkin& operator=(SlipperySkin&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

