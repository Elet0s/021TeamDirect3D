#pragma once
#include "Skill.h"

// Ό³Έν :
class Overloaded : public Skill
{
public:
	// constrcuter destructer
	Overloaded();
	~Overloaded();

	// delete Function
	Overloaded(const Overloaded& _Other) = delete;
	Overloaded(Overloaded&& _Other) noexcept = delete;
	Overloaded& operator=(const Overloaded& _Other) = delete;
	Overloaded& operator=(Overloaded&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

