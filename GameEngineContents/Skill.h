#pragma once
#include "GlobalContentsValue.h"

class Skill : public GameEngineActor
{
public:
	Skill();
	virtual ~Skill();

	Skill(const Skill& _Other) = delete;
	Skill(Skill&& _Other) noexcept = delete;
	Skill& operator=(const Skill& _Other) = delete;
	Skill& operator=(Skill&& _Other) noexcept = delete;
	
	
	virtual void Init() {};
	virtual void Effect() {};

	std::string_view GetSkillName()
	{
		return name_;
	}

	Rank GetRank()
	{
		return myRank_;
	}

	int GetCurrentlevel()
	{
		return currentlevel_;
	}

	int GetMaxLevel()
	{
		return maxLevel_;
	}


	template <typename SkillValue>
	void createSkill()
	{
	}

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	std::string name_;
	std::string etc_;
	int currentlevel_;
	int maxLevel_;
	Rank myRank_;
private:
};

