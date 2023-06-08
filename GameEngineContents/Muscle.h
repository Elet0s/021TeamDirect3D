#pragma once
#include "Skill.h"

// ���� :
class Muscle : public Skill
{
public:
	// constrcuter destructer
	Muscle();
	~Muscle();

	// delete Function
	Muscle(const Muscle& _Other) = delete;
	Muscle(Muscle&& _Other) noexcept = delete;
	Muscle& operator=(const Muscle& _Other) = delete;
	Muscle& operator=(Muscle&& _Other) noexcept = delete;
	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

