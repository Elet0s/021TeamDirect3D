#pragma once
#include "Skill.h"
// Ό³Έν :
class Impenetrable : public Skill
{
public:
	// constrcuter destructer
	Impenetrable();
	~Impenetrable();

	// delete Function
	Impenetrable(const Impenetrable& _Other) = delete;
	Impenetrable(Impenetrable&& _Other) noexcept = delete;
	Impenetrable& operator=(const Impenetrable& _Other) = delete;
	Impenetrable& operator=(Impenetrable&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

