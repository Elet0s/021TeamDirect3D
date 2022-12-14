#pragma once
#include "Skill.h"

// Ό³Έν :
class Castle : public Skill
{
public:
	// constrcuter destructer
	Castle();
	~Castle();

	// delete Function
	Castle(const Castle& _Other) = delete;
	Castle(Castle&& _Other) noexcept = delete;
	Castle& operator=(const Castle& _Other) = delete;
	Castle& operator=(Castle&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

