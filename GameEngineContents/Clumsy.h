#pragma once
#include "Skill.h"

// Ό³Έν :
class Clumsy : public Skill
{
public:
	// constrcuter destructer
	Clumsy();
	~Clumsy();

	// delete Function
	Clumsy(const Clumsy& _Other) = delete;
	Clumsy(Clumsy&& _Other) noexcept = delete;
	Clumsy& operator=(const Clumsy& _Other) = delete;
	Clumsy& operator=(Clumsy&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

