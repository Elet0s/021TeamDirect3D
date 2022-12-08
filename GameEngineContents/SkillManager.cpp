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

void SkillManager::SkillLevelCheak()
{
	for (size_t i = 0; i < 1; i++)
	{
		if (skillList_[i]->nowLevel_ > 0 && skillList_[i]->IsUpdate() == false)
		{
			skillList_[i]->On();
		}
	}
}
