#pragma once
#include "Skill.h"

// Ό³Έν :
class Practice : public Skill
{
public:
	// constrcuter destructer
	Practice();
	~Practice();

	// delete Function
	Practice(const Practice& _Other) = delete;
	Practice(Practice&& _Other) noexcept = delete;
	Practice& operator=(const Practice& _Other) = delete;
	Practice& operator=(Practice&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

