#include "PreCompile.h"
#include "SkillManager.h"
#include "Spear.h"
#include"Shuriken.h"

SkillManager::SkillManager()
{
	
}
SkillManager::~SkillManager()
{
}

void SkillManager::CreatePlayerAllSkill()
{
	skillList_.reserve(68);
	std::shared_ptr<Skill> A = myLevel_->CreateActor<Shuriken>(ObjectOrder::Skill);
	skillList_.push_back(A);	
}

void SkillManager::SkillLevelCheak()
{

	if (skillList_[0]->nowLevel_ > 0 && skillList_[0]->IsUpdate() == false)
	{
		skillList_[0]->On();
	}

}
