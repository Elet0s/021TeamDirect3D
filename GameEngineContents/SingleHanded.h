#pragma once
#include "Skill.h"

// Ό³Έν :
class SingleHanded : public Skill
{
public:
	// constrcuter destructer
	SingleHanded();
	~SingleHanded();

	// delete Function
	SingleHanded(const SingleHanded& _Other) = delete;
	SingleHanded(SingleHanded&& _Other) noexcept = delete;
	SingleHanded& operator=(const SingleHanded& _Other) = delete;
	SingleHanded& operator=(SingleHanded&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

