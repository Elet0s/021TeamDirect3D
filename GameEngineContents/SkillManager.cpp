#include "PreCompile.h"
#include "SkillManager.h"
#include "Spear.h"
#include "Shuriken.h"
#include"DeathAura.h"

SkillManager::SkillManager()
{
	
}
SkillManager::~SkillManager()
{
}

void SkillManager::CreatePlayerAllSkill()
{
	skillList_.reserve(68);  
	std::shared_ptr<Skill> Skill00 = myLevel_->CreateActor<Shuriken>(ObjectOrder::Skill); //스킬 생성
	skillList_.push_back(Skill00);


}

void SkillManager::SkillLevelCheak()
{
	if (skillList_[0]->nowLevel_ > 0 && skillList_[0]->IsUpdate() == false) 
	{
		skillList_[0]->On();
	}
}
