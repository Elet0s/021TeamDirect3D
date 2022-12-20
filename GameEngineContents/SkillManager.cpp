#include "PreCompile.h"
#include "SkillManager.h"

#include"Cleaver.h"
#include"Kunai.h"
#include"Pike.h"
#include "Spear.h"

#include"DeathAura.h"
#include"Firering.h"
#include"ShamanStaff.h"
#include"Swordrang.h"
#include"ThunderStaf.h"
#include"WindsBlade.h"

#include "Shuriken.h"
#include"MagicWisp.h"
#include"MagicWand.h"
#include"Katana.h"
#include"Crossbow.h"
#include"Bow.h"

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

	std::shared_ptr<Skill> Skill00 = myLevel_->CreateActor<Cleaver>(ObjectOrder::Skill); 
	skillList_.push_back(Skill00);
	std::shared_ptr<Skill> Skill01 = myLevel_->CreateActor<Kunai>(ObjectOrder::Skill); 
	skillList_.push_back(Skill01);
	std::shared_ptr<Skill> Skill02 = myLevel_->CreateActor<Pike>(ObjectOrder::Skill);
	skillList_.push_back(Skill02);
	std::shared_ptr<Skill> Skill03 = myLevel_->CreateActor<Spear>(ObjectOrder::Skill); 
	skillList_.push_back(Skill03);

	std::shared_ptr<Skill> Skill04 = myLevel_->CreateActor<DeathAura>(ObjectOrder::Skill);
	skillList_.push_back(Skill04);
	std::shared_ptr<Skill> Skill05 = myLevel_->CreateActor<Firering>(ObjectOrder::Skill); 
	skillList_.push_back(Skill05);
	std::shared_ptr<Skill> Skill06 = myLevel_->CreateActor<ShamanStaff>(ObjectOrder::Skill);
	skillList_.push_back(Skill06);
	std::shared_ptr<Skill> Skill07 = myLevel_->CreateActor<Swordrang>(ObjectOrder::Skill);
	skillList_.push_back(Skill07);
	std::shared_ptr<Skill> Skill08 = myLevel_->CreateActor<ThunderStaf>(ObjectOrder::Skill); 
	skillList_.push_back(Skill08);
	std::shared_ptr<Skill> Skill09 = myLevel_->CreateActor<WindsBlade>(ObjectOrder::Skill); 
	skillList_.push_back(Skill09);

	std::shared_ptr<Skill> Skill10 = myLevel_->CreateActor<Bow>(ObjectOrder::Skill);
	skillList_.push_back(Skill10);
	std::shared_ptr<Skill> Skill11 = myLevel_->CreateActor<Crossbow>(ObjectOrder::Skill);
	skillList_.push_back(Skill11);
	std::shared_ptr<Skill> Skill12 = myLevel_->CreateActor<Katana>(ObjectOrder::Skill); 
	skillList_.push_back(Skill12);
	std::shared_ptr<Skill> Skill13 = myLevel_->CreateActor<MagicWand>(ObjectOrder::Skill); 
	skillList_.push_back(Skill13);
	std::shared_ptr<Skill> Skill14 = myLevel_->CreateActor<MagicWisp>(ObjectOrder::Skill);
	skillList_.push_back(Skill14);
	std::shared_ptr<Skill> Skill15 = myLevel_->CreateActor<Shuriken>(ObjectOrder::Skill);
	skillList_.push_back(Skill15);

}

void SkillManager::SkillLevelCheak()
{
	if (skillList_[15]->nowLevel_ > 0 && skillList_[15]->IsUpdate() == false) //스킬 레벨 체크이 0보다크고 업데이트가 돌지 않고있으면
	{
		skillList_[15]->On();
		//플레이어 위치로 이동시키고 on
		for (size_t i = 0; i < std::dynamic_pointer_cast<Shuriken>(skillList_[15])->projectileGroupList_.size(); i++)
		{
			std::dynamic_pointer_cast<Shuriken>(skillList_[15])->projectileGroupList_[i].first->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y, -100);
			std::dynamic_pointer_cast<Shuriken>(skillList_[15])->projectileGroupList_[i].second->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y, -100);
		}

	}
}
