#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <string>
// Ό³Έν :
class Skill : public GameEngineNameObject
{
public:
	// constrcuter destructer
	Skill();
	virtual ~Skill();

	// delete Function
	Skill(const Skill& _Other) = delete;
	Skill(Skill&& _Other) noexcept = delete;
	Skill& operator=(const Skill& _Other) = delete;
	Skill& operator=(Skill&& _Other) noexcept = delete;
	
	
	virtual void Init() {};
	virtual void Effect() {};

protected:


	std::string etc_;
	int level_;
private:
};

