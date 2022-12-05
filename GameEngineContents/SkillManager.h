#pragma once
#include "Skill.h"

class SkillManager
{
public:
	SkillManager();
	~SkillManager();


	SkillManager(const SkillManager& _Other) = delete;
	SkillManager(SkillManager&& _Other) noexcept = delete;
	SkillManager& operator=(const SkillManager& _Other) = delete;
	SkillManager& operator=(SkillManager&& _Other) noexcept = delete;

	void CreatePlayerAllSkill();

protected:

private:
	std::vector < std::shared_ptr <Skill>> skillList_;
};