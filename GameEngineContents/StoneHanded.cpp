#include "PreCompile.h"
#include "StoneHanded.h"
#include "Player.h"

StoneHanded::StoneHanded() 
{
	name_ = "바위 손";
	SetName(std::string_view("StoneHanded"));
	myRank_ = Rank::Epic;
	maxLevel_ = 1;
}

StoneHanded::~StoneHanded() 
{
}

void StoneHanded::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sAddProjectile = std::to_string(PlayerInfo_.addProjectile_).substr(0, std::to_string(PlayerInfo_.addProjectile_).find("."));
	std::string sAtkSpeed = std::to_string(PlayerInfo_.attackSpeed_).substr(0, std::to_string(PlayerInfo_.attackSpeed_).find("."));
	std::string sProjectileDuration = std::to_string(PlayerInfo_.projectileduration_).substr(0, std::to_string(PlayerInfo_.projectileduration_).find("."));
	std::string sAddProjectileNext = std::to_string(PlayerInfo_.addProjectile_ + 3.f).substr(0, std::to_string(PlayerInfo_.addProjectile_ + 3.f).find("."));
	std::string sAtkSpeedNext = std::to_string(PlayerInfo_.attackSpeed_ * 0.75f).substr(0, std::to_string(PlayerInfo_.attackSpeed_ * 0.75f).find(".") );
	std::string sProjectileDurationNext = std::to_string(PlayerInfo_.projectileduration_ * 0.7f).substr(0, std::to_string(PlayerInfo_.projectileduration_).find(".") -1);

	etc_ = sAddProjectile + " -> " + sAddProjectileNext + " 추가 투사체\n"
		+ sProjectileDuration + "% ->" + sProjectileDurationNext + "% 투사체\n지속시간\n"
		+ sAtkSpeed + "% ->" + sAtkSpeedNext + "% 공격 속도 ";
}

void StoneHanded::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	//PlayerInfo_->projectileSize_ = round(PlayerInfo_->projectileSize_ * 100) / 100;
	PlayerInfo_->addProjectile_ += 3.0f;
	PlayerInfo_->projectileduration_ *= 0.7f;
	PlayerInfo_->attackSpeed_ *= 0.75f;

}