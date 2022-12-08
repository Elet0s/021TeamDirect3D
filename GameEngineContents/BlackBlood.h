#pragma once
#include "Skill.h"

// Ό³Έν :
class BlackBlood : public Skill
{
public:
	// constrcuter destructer
	BlackBlood();
	~BlackBlood();

	// delete Function
	BlackBlood(const BlackBlood& _Other) = delete;
	BlackBlood(BlackBlood&& _Other) noexcept = delete;
	BlackBlood& operator=(const BlackBlood& _Other) = delete;
	BlackBlood& operator=(BlackBlood&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

