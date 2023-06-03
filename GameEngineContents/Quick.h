#pragma once
#include "Skill.h"

// 설명 :
class Quick : public Skill
{
public:
	// constrcuter destructer
	Quick();
	~Quick();

	// delete Function
	Quick(const Quick& _Other) = delete;
	Quick(Quick&& _Other) noexcept = delete;
	Quick& operator=(const Quick& _Other) = delete;
	Quick& operator=(Quick&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

