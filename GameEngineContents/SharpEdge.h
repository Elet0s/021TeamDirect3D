#pragma once
#include "Skill.h"

// Ό³Έν :
class SharpEdge : public Skill
{
public:
	// constrcuter destructer
	SharpEdge();
	~SharpEdge();

	// delete Function
	SharpEdge(const SharpEdge& _Other) = delete;
	SharpEdge(SharpEdge&& _Other) noexcept = delete;
	SharpEdge& operator=(const SharpEdge& _Other) = delete;
	SharpEdge& operator=(SharpEdge&& _Other) noexcept = delete;
	
	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}
protected:

private:

};

