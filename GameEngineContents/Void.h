#pragma once
#include "Skill.h"

// Ό³Έν :
class Void : public Skill
{
public:
	// constrcuter destructer
	Void();
	~Void();

	// delete Function
	Void(const Void& _Other) = delete;
	Void(Void&& _Other) noexcept = delete;
	Void& operator=(const Void& _Other) = delete;
	Void& operator=(Void&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

