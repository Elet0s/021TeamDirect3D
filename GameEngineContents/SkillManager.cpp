#include "PreCompile.h"
#include "SkillManager.h"
#include "Spear.h"
#include "Shuriken.h"
#include"DeathAura.h"
#include "Player.h"

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
		std::dynamic_pointer_cast<Shuriken>(skillList_[0])->shuriKenRenderer_->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y, -100);
		std::dynamic_pointer_cast<Shuriken>(skillList_[0])->shuriKenCol_->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y, -100);
		skillList_[0]->On();
	}
}
