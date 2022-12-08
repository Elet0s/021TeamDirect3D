#pragma once
#include "Skill.h"

class SkillManager // 스킬매니저의 역할 = 게임시작할때 모든 스킬을 하나씩 만들고 스킬레벨에 따라 활성시켜주는 역할
{
public:

	SkillManager();
	~SkillManager();


	SkillManager(const SkillManager& _Other) = delete;
	SkillManager(SkillManager&& _Other) noexcept = delete;
	SkillManager& operator=(const SkillManager& _Other) = delete;
	SkillManager& operator=(SkillManager&& _Other) noexcept = delete;


	void SetLevel(GameEngineLevel* _thisLevel)
	{
		myLevel_ = _thisLevel;
	}

	void CreatePlayerAllSkill();
protected:

private:

	 GameEngineLevel* myLevel_;
	std::vector < std::shared_ptr <Skill>> skillList_;
};