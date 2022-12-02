#pragma once
#include "Skill.h"

// Ό³Έν :
class Range : public Skill
{
public:
	// constrcuter destructer
	Range();
	~Range();

	// delete Function
	Range(const Range& _Other) = delete;
	Range(Range&& _Other) noexcept = delete;
	Range& operator=(const Range& _Other) = delete;
	Range& operator=(Range&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

