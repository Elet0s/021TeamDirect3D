#include "PreCompile.h"
#include "SkillManager.h"
#include "Spear.h"

SkillManager::SkillManager()
{
	
}
SkillManager::~SkillManager()
{
}

void SkillManager::CreatePlayerAllSkill()
{
	skillList_.reserve(68);

		std::shared_ptr<Skill> A = myLevel_->CreateActor<Spear>(ObjectOrder::Skill);
		skillList_.push_back(A);
	

}
