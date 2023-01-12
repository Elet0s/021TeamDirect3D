#include"PreCompile.h"
#include"ThunderStaf.h"
#include "Player.h"

ThunderStaf::ThunderStaf()
{
	name_ = "���� ������";
	SetName(std::string_view("ThunderStaf"));
	myRank_ = Rank::Rare;
	maxLevel_ = 7;
}
ThunderStaf::~ThunderStaf()
{

}
void ThunderStaf::Init()
{
	StateSet();
	std::string sDamege = std::to_string(static_cast<int>(floor(ThunderStafWeaponInfo_.weaponAtk_)));
	std::string sAttackSpeed = std::to_string(ThunderStafWeaponInfo_.weaponAtkSpeed_).substr(0, std::to_string(ThunderStafWeaponInfo_.weaponAtkSpeed_).find(".") + 3);
	std::string sTime = std::to_string(ThunderStafWeaponInfo_.weaponDuration_ /100).substr(0, std::to_string(ThunderStafWeaponInfo_.weaponDuration_ / 100).find(".") + 3);

	etc_ = "�ڽ��� �߽����� �����ϴ�\n���� ��ü�� ��ȯ�մϴ�\n" + sDamege + "�� ����\n" + sAttackSpeed + "�� ���� ����\n����ü" + std::to_string(ThunderStafWeaponInfo_.weaponProjectileNum_) + "��\n"
		+ sTime + "�� ����ü ���� �ð� ";
}
void ThunderStaf::Effect()
{
	currentlevel_ += 1;
}
void ThunderStaf::Start()
{

}

void ThunderStaf::StateSet()
{
	PlayerInfo* Info = &Player::GetPlayerInst()->GetPlayerInfo();
	PlayerPassiveInfo* PInfo = &Player::GetPlayerInst()->GetPlayerPassiveInfo();

	ThunderStafWeaponInfo_.weaponAtk_ = round((1.f + currentlevel_) * Info->atk_ * PInfo->atkMultiple_Result / 100);
	ThunderStafWeaponInfo_.weaponAtkSpeed_ = round(500.f / (Info->attackSpeed_ * PInfo->attackSpeed_Result));
	ThunderStafWeaponInfo_.weaponPassAtk_ = 0;
	ThunderStafWeaponInfo_.weaponRange_ = 1.f * Info->rangeSize_;
	ThunderStafWeaponInfo_.weaponProjectileNum_ = 3 + Info->addProjectile_;
	ThunderStafWeaponInfo_.weaponPassNum_ = 2 + Info->passProjectile_;

	ThunderStafWeaponInfo_.weaponSize_ = 1 * Info->projectileSize_ * PInfo->projectileSize_Result / 100;
	ThunderStafWeaponInfo_.weaponDuration_ = 250 + (30.f * currentlevel_);
	ThunderStafWeaponInfo_.weaponSpeed_ = 100 * Info->projectilespeed_ * PInfo->projectileSpeed_Result;

	if (currentlevel_ < 5)
	{
		ThunderStafWeaponInfo_.weaponProjectileNum_ = 3 + currentlevel_ + Info->addProjectile_;
	}
	else
	{
		ThunderStafWeaponInfo_.weaponProjectileNum_ = 7 + Info->addProjectile_;
	}

	if (currentlevel_ > 5)
	{
		ThunderStafWeaponInfo_.weaponSpeed_ = (100 + (20.f * (currentlevel_ - 5))) * Info->projectilespeed_ * PInfo->projectileSpeed_Result;
	}

}


void ThunderStaf::Update(float _deltaTime)
{

}
void ThunderStaf::End()
{

}