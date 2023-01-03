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

// Rank : Spotted [0]

#include "LowPressure.h"
#include "Healthy.h"
#include "Durability.h"
#include "Durability.h"
#include "StoneSkin.h"
#include "SharpeningStone.h"
#include "Cardio.h"

// Rank : Nomal [1]

#include "Agility.h"
#include "Void.h"
#include "Student.h"
#include "IronWill.h"
#include "HealingFactor.h"
#include "BlackBlood.h"
#include "LightArmor.h"
#include "SharpEdge.h"
#include "Range.h"
#include "TensString.h"
#include "Momentum.h"
#include "Muscle.h"
#include "Compromise.h"
#include "Practice.h"
#include "DamascusSteel.h"

// Rank : UnCommon [2]
#include "Dash.h"
#include "IronSkin.h"
#include "SlipperySkin.h"
#include "Impenetrable.h"
#include "Aiming.h"
#include "Area.h"
#include "Quick.h"
#include "Clumsy.h"
#include "TradeOff.h"

// Rank : Rare [3]
#include "DashCooldown.h"
#include "Tower.h"
#include "SteelSkin.h"
#include "Celerity.h"
#include "GodsWrath.h"
#include "Penetration.h"

// Rank : Epic [4]
#include "SingleHanded.h"
#include "LightHand.h"
#include "Hypersonic.h"
#include "StoneHanded.h"
#include "Castle.h"



#include "Player.h"

SkillManager::SkillManager()
{
	
}
SkillManager::~SkillManager()
{
}

void SkillManager::CreatePlayerAllSkill()
{
	skillList_.resize(6);

	skillList_[5].reserve(16);
	{
		std::shared_ptr<Skill> Skill00 = myLevel_->CreateActor<Cleaver>(ObjectOrder::Skill);
		skillList_[5].push_back(Skill00);
		std::shared_ptr<Skill> Skill01 = myLevel_->CreateActor<Kunai>(ObjectOrder::Skill);
		skillList_[5].push_back(Skill01);
		std::shared_ptr<Skill> Skill02 = myLevel_->CreateActor<Pike>(ObjectOrder::Skill);
		skillList_[5].push_back(Skill02);
		std::shared_ptr<Skill> Skill03 = myLevel_->CreateActor<Spear>(ObjectOrder::Skill);
		skillList_[5].push_back(Skill03);

		std::shared_ptr<Skill> Skill04 = myLevel_->CreateActor<DeathAura>(ObjectOrder::Skill);
		skillList_[5].push_back(Skill04);
		std::shared_ptr<Skill> Skill05 = myLevel_->CreateActor<Firering>(ObjectOrder::Skill);
		skillList_[5].push_back(Skill05);
		std::shared_ptr<Skill> Skill06 = myLevel_->CreateActor<ShamanStaff>(ObjectOrder::Skill);
		skillList_[5].push_back(Skill06);
		std::shared_ptr<Skill> Skill07 = myLevel_->CreateActor<Swordrang>(ObjectOrder::Skill);
		skillList_[5].push_back(Skill07);
		std::shared_ptr<Skill> Skill08 = myLevel_->CreateActor<ThunderStaf>(ObjectOrder::Skill);
		skillList_[5].push_back(Skill08);
		std::shared_ptr<Skill> Skill09 = myLevel_->CreateActor<WindsBlade>(ObjectOrder::Skill);
		skillList_[5].push_back(Skill09);

		std::shared_ptr<Skill> Skill10 = myLevel_->CreateActor<Bow>(ObjectOrder::Skill);
		skillList_[5].push_back(Skill10);
		std::shared_ptr<Skill> Skill11 = myLevel_->CreateActor<Crossbow>(ObjectOrder::Skill);
		skillList_[5].push_back(Skill11);
		std::shared_ptr<Skill> Skill12 = myLevel_->CreateActor<Katana>(ObjectOrder::Skill);
		skillList_[5].push_back(Skill12);
		std::shared_ptr<Skill> Skill13 = myLevel_->CreateActor<MagicWand>(ObjectOrder::Skill);
		skillList_[5].push_back(Skill13);
		std::shared_ptr<Skill> Skill14 = myLevel_->CreateActor<MagicWisp>(ObjectOrder::Skill);
		skillList_[5].push_back(Skill14);
		std::shared_ptr<Skill> Skill15 = myLevel_->CreateActor<Shuriken>(ObjectOrder::Skill);
		skillList_[5].push_back(Skill15);
	}


	// �������� ��ũ 
	skillList_[0].reserve(7);
	{
		std::shared_ptr<Skill> Skill00 = myLevel_->CreateActor<LowPressure>();
		skillList_[0].push_back(Skill00);

		std::shared_ptr<Skill> Skill01 = myLevel_->CreateActor<Healthy>();
		skillList_[0].push_back(Skill01);

		std::shared_ptr<Skill> Skill02 = myLevel_->CreateActor<Durability>();
		skillList_[0].push_back(Skill02);

		std::shared_ptr<Skill> Skill03 = myLevel_->CreateActor<Durability>();
		skillList_[0].push_back(Skill03);

		std::shared_ptr<Skill> Skill04 = myLevel_->CreateActor<StoneSkin>();
		skillList_[0].push_back(Skill04);

		std::shared_ptr<Skill> Skill05 = myLevel_->CreateActor<SharpeningStone>();
		skillList_[0].push_back(Skill05);

		std::shared_ptr<Skill> Skill06 = myLevel_->CreateActor<Cardio>();
		skillList_[0].push_back(Skill06);
	}

	// �븻 ��ũ
	skillList_[1].reserve(17);
	{
		std::shared_ptr<Skill> Skill00 = myLevel_->CreateActor<Agility>();
		skillList_[1].push_back(Skill00);
		
		std::shared_ptr<Skill> Skill01 = myLevel_->CreateActor<Void>();
		skillList_[1].push_back(Skill01);

		std::shared_ptr<Skill> Skill02 = myLevel_->CreateActor<Student>();
		skillList_[1].push_back(Skill02);

		std::shared_ptr<Skill> Skill03 = myLevel_->CreateActor<IronWill>();
		skillList_[1].push_back(Skill03);

		std::shared_ptr<Skill> Skill04 = myLevel_->CreateActor<HealingFactor>();
		skillList_[1].push_back(Skill04);

		std::shared_ptr<Skill> Skill05 = myLevel_->CreateActor<HealingFactor>();
		skillList_[1].push_back(Skill05);

		std::shared_ptr<Skill> Skill06 = myLevel_->CreateActor<BlackBlood>();
		skillList_[1].push_back(Skill06);

		std::shared_ptr<Skill> Skill07 = myLevel_->CreateActor<LightArmor>();
		skillList_[1].push_back(Skill07);

		std::shared_ptr<Skill> Skill08 = myLevel_->CreateActor<SharpEdge>();
		skillList_[1].push_back(Skill08);

		std::shared_ptr<Skill> Skill09 = myLevel_->CreateActor<Range>();
		skillList_[1].push_back(Skill09);

		std::shared_ptr<Skill> Skill10 = myLevel_->CreateActor<TensString>();
		skillList_[1].push_back(Skill10);

		std::shared_ptr<Skill> Skill11 = myLevel_->CreateActor<Momentum>();
		skillList_[1].push_back(Skill11);

		std::shared_ptr<Skill> Skill12 = myLevel_->CreateActor<Muscle>();
		skillList_[1].push_back(Skill12);

		std::shared_ptr<Skill> Skill13 = myLevel_->CreateActor<Compromise>();
		skillList_[1].push_back(Skill13);

		std::shared_ptr<Skill> Skill15 = myLevel_->CreateActor<Practice>();
		skillList_[1].push_back(Skill15);

		std::shared_ptr<Skill> Skill16 = myLevel_->CreateActor<DamascusSteel>();
		skillList_[1].push_back(Skill16);
	}


	// ��Ŀ�� ��ũ
	skillList_[2].reserve(9);
	{
		std::shared_ptr<Skill> Skill00 = myLevel_->CreateActor<Dash>();
		skillList_[2].push_back(Skill00);

		std::shared_ptr<Skill> Skill01 = myLevel_->CreateActor<IronSkin>();
		skillList_[2].push_back(Skill01);

		std::shared_ptr<Skill> Skill02 = myLevel_->CreateActor<SlipperySkin>();
		skillList_[2].push_back(Skill02);

		std::shared_ptr<Skill> Skill03 = myLevel_->CreateActor<Impenetrable>();
		skillList_[2].push_back(Skill03);

		std::shared_ptr<Skill> Skill04 = myLevel_->CreateActor<Aiming>();
		skillList_[2].push_back(Skill04);

		std::shared_ptr<Skill> Skill05 = myLevel_->CreateActor<Area>();
		skillList_[2].push_back(Skill05);

		std::shared_ptr<Skill> Skill06 = myLevel_->CreateActor<Quick>();
		skillList_[2].push_back(Skill06);

		std::shared_ptr<Skill> Skill07 = myLevel_->CreateActor<Clumsy>();
		skillList_[2].push_back(Skill07);

		std::shared_ptr<Skill> Skill08 = myLevel_->CreateActor<TradeOff>();
		skillList_[2].push_back(Skill08);
	}

	// ���� ��ũ
	skillList_[3].reserve(6);
	{
		std::shared_ptr<Skill> Skill00 = myLevel_->CreateActor<DashCooldown>();
		skillList_[3].push_back(Skill00);

		std::shared_ptr<Skill> Skill01 = myLevel_->CreateActor<Tower>();
		skillList_[3].push_back(Skill01);

		std::shared_ptr<Skill> Skill02 = myLevel_->CreateActor<SteelSkin>();
		skillList_[3].push_back(Skill02);


		std::shared_ptr<Skill> Skill03 = myLevel_->CreateActor<Celerity>();
		skillList_[3].push_back(Skill03);


		std::shared_ptr<Skill> Skill04 = myLevel_->CreateActor<GodsWrath>();
		skillList_[3].push_back(Skill04);

		std::shared_ptr<Skill> Skill05 = myLevel_->CreateActor<Penetration>();
		skillList_[3].push_back(Skill05);

		
	}

	// ���� ��ũ
	skillList_[4].reserve(4);
	{
		std::shared_ptr<Skill> Skill00 = myLevel_->CreateActor<SingleHanded>();
		skillList_[3].push_back(Skill00);

		std::shared_ptr<Skill> Skill01 = myLevel_->CreateActor<LightHand>();
		skillList_[3].push_back(Skill01);

		std::shared_ptr<Skill> Skill02 = myLevel_->CreateActor<Hypersonic>();
		skillList_[3].push_back(Skill02);

		std::shared_ptr<Skill> Skill03 = myLevel_->CreateActor<Castle>();
		skillList_[3].push_back(Skill03);
	}
}

void SkillManager::SkillLevelCheak()
{
	if (skillList_[5][4]->nowLevel_ > 0 && skillList_[5][4]->IsUpdate() == false) //��ų ���� üũ�� 0����ũ�� ������Ʈ�� ���� �ʰ�������
	{
		skillList_[5][4]->On();
		//�÷��̾� ��ġ�� �̵���Ű�� on

	}
	if (skillList_[5][15]->nowLevel_ > 0 && skillList_[5][15]->IsUpdate() == false) //��ų ���� üũ�� 0����ũ�� ������Ʈ�� ���� �ʰ�������
	{
		skillList_[5][15]->On();
		//�÷��̾� ��ġ�� �̵���Ű�� on
		for (size_t i = 0; i < std::dynamic_pointer_cast<Shuriken>(skillList_[5][15])->projectileGroupList_.size(); i++)
		{
			std::dynamic_pointer_cast<Shuriken>(skillList_[5][15])->projectileGroupList_[i].first->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y, -100);
			std::dynamic_pointer_cast<Shuriken>(skillList_[5][15])->projectileGroupList_[i].second->GetTransform().SetWorldPosition(Player::GetPlayerInst()->GetTransform().GetWorldPosition().x, Player::GetPlayerInst()->GetTransform().GetWorldPosition().y, -100);
		}

	}
}
