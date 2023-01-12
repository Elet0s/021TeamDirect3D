#include"PreCompile.h"
#include"Cleaver.h"
#include"Player.h"

Cleaver::Cleaver()
{
	name_ = "대검";
	SetName(std::string_view("Cleaver"));
	myRank_ = Rank::UnCommon;
	maxLevel_ = 7;
}
Cleaver::~Cleaver()
{

}


void Cleaver::Init()
{
	StateSet();
	std::string sDamege = std::to_string(static_cast<int>(floor(cleaverWeaponInfo_.weaponAtk_)));
	std::string sAttackSpeed = std::to_string(cleaverWeaponInfo_.weaponAtkSpeed_).substr(0, std::to_string(cleaverWeaponInfo_.weaponAtkSpeed_).find(".") + 3);

	
	etc_ = "조준된 방향으로\n 적을 밀어내는\n약하지만 큰\n투사체를 발사합니다\n" + sDamege + "의 피해\n" + sAttackSpeed + "초 마다 공격 ";
}
void Cleaver::Effect()
{
	currentlevel_ += 1;
}

void Cleaver::StateSet()
{
	PlayerInfo* Info = &Player::GetPlayerInst()->GetPlayerInfo();
	PlayerPassiveInfo* PInfo = &Player::GetPlayerInst()->GetPlayerPassiveInfo();

	cleaverWeaponInfo_.weaponAtk_ = round((1.f + 2.f * currentlevel_) * Info->atk_ * PInfo->atkMultiple_Result / 100);
	cleaverWeaponInfo_.weaponAtkSpeed_ = (200.f - (currentlevel_ * 25.f))  / (Info->attackSpeed_ * PInfo->attackSpeed_Result);
	cleaverWeaponInfo_.weaponPassAtk_ = 0;
	cleaverWeaponInfo_.weaponRange_ = 1.f * Info->projectileSize_;
	cleaverWeaponInfo_.weaponProjectileNum_ = 3 + Info->addProjectile_;
	cleaverWeaponInfo_.weaponPassNum_ = 2 + Info->passProjectile_;

	cleaverWeaponInfo_.weaponSize_ = 100 * Info->projectileSize_ * PInfo->projectileSize_Result / 100;
	cleaverWeaponInfo_.weaponDuration_ = 100 * Info->projectileduration_ * PInfo->projectileDuration_Result / 100; ;
	cleaverWeaponInfo_.weaponSpeed_ = 100 * Info->projectilespeed_ * PInfo->projectileSpeed_Result / 100;

	
}

void Cleaver::Start()
{

}
void Cleaver::Update(float _deltaTime)
{

}
void Cleaver::End()
{

}