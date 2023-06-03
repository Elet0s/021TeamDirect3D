#pragma once
#include "Skill.h"

// 설명 :
class LowPressure : public Skill
{
public:
	// constrcuter destructer
	LowPressure();
	~LowPressure();

	// delete Function
	LowPressure(const LowPressure& _Other) = delete;
	LowPressure(LowPressure&& _Other) noexcept = delete;
	LowPressure& operator=(const LowPressure& _Other) = delete;
	LowPressure& operator=(LowPressure&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

