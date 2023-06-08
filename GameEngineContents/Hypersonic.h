#pragma once
#include "Skill.h"

// Ό³Έν :
class Hypersonic : public Skill
{
public:
	// constrcuter destructer
	Hypersonic();
	~Hypersonic();

	// delete Function
	Hypersonic(const Hypersonic& _Other) = delete;
	Hypersonic(Hypersonic&& _Other) noexcept = delete;
	Hypersonic& operator=(const Hypersonic& _Other) = delete;
	Hypersonic& operator=(Hypersonic&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

