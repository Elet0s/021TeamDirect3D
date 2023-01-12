#include"PreCompile.h"
#include"Swordrang.h"
#include "Player.h"

Swordrang::Swordrang()
{
	name_ = "칼메랑";
	SetName(std::string_view("Swordrang"));
	myRank_ = Rank::Epic;
	maxLevel_ = 7;
}
Swordrang::~Swordrang()
{

}
void Swordrang::Init()
{
	StateSet();
	std::string sDamege = std::to_string(static_cast<int>(floor(SwordrangWeaponInfo_.weaponAtk_)));
	std::string sAttackSpeed = std::to_string(SwordrangWeaponInfo_.weaponAtkSpeed_).substr(0, std::to_string(SwordrangWeaponInfo_.weaponAtkSpeed_).find(".") + 3);

	etc_ = "자신의 주변으로 적을\n관통하고 돌아오는 검을\n던집니다\n" + sDamege + "의 피해\n" + sAttackSpeed + "초 마다 공격\n투사체 " + std::to_string(SwordrangWeaponInfo_.weaponProjectileNum_) + " 개 \n" + std::to_string(SwordrangWeaponInfo_.weaponPassNum_) + "관통 ";

}
void Swordrang::Effect()
{
	currentlevel_ += 1;
}

void Swordrang::StateSet()
{
	PlayerInfo* Info = &Player::GetPlayerInst()->GetPlayerInfo();
	PlayerPassiveInfo* PInfo = &Player::GetPlayerInst()->GetPlayerPassiveInfo();

	SwordrangWeaponInfo_.weaponAtk_ = round((5.f + currentlevel_ * 0.5f) * Info->atk_ * PInfo->atkMultiple_Result / 100);
	SwordrangWeaponInfo_.weaponAtkSpeed_ = 125.f / (Info->attackSpeed_ * PInfo->attackSpeed_Result);
	SwordrangWeaponInfo_.weaponPassAtk_ = 0;
	SwordrangWeaponInfo_.weaponPassNum_ = 4 + currentlevel_ * 2 + Info->passProjectile_;
	SwordrangWeaponInfo_.weaponProjectileNum_ = 2 + Info->addProjectile_;
	SwordrangWeaponInfo_.weaponSize_ = 1 * Info->projectileSize_ * PInfo->projectileSize_Result / 100;
	SwordrangWeaponInfo_.weaponDuration_ = 100 * Info->projectileduration_ * PInfo->projectileDuration_Result / 100;
	SwordrangWeaponInfo_.weaponSpeed_ = 100 * Info->projectilespeed_ * PInfo->projectileSpeed_Result / 100;
	SwordrangWeaponInfo_.weaponknockback_ = 100;
	SwordrangWeaponInfo_.weponConsecutiveAtkNum_ = 1;

	if (currentlevel_ > 4)
	{
		SwordrangWeaponInfo_.weponConsecutiveAtkNum_ = 2 + currentlevel_ + Info->addProjectile_;
	}
	else
	{
		SwordrangWeaponInfo_.weponConsecutiveAtkNum_ = 5 + currentlevel_ + Info->addProjectile_;
	}
}
void Swordrang::Start()
{

}
void Swordrang::Update(float _deltaTime)
{

}
void Swordrang::End()
{

}

