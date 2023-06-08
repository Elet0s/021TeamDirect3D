#pragma once
#include "Skill.h"

class Celerity : public Skill
{
public:
	// constrcuter destructer
	Celerity();
	~Celerity();

	// delete Function
	Celerity(const Celerity& _Other) = delete;
	Celerity(Celerity&& _Other) noexcept = delete;
	Celerity& operator=(const Celerity& _Other) = delete;
	Celerity& operator=(Celerity&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

