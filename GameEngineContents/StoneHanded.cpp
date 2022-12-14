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
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().get()->GetPlayerPassiveInfo();

	std::string sAddProjectile = std::to_string(PlayerInfo_.addProjectile_).substr(0, std::to_string(PlayerInfo_.addProjectile_).find("."));
	std::string sAtkSpeed = std::to_string(PlayerPInfo_.attackSpeed_Result).substr(0, std::to_string(PlayerPInfo_.attackSpeed_Result).find("."));
	std::string sProjectileDuration = std::to_string(PlayerPInfo_.projectileDuration_Result).substr(0, std::to_string(PlayerPInfo_.projectileDuration_Result).find("."));
	std::string sAddProjectileNext = std::to_string(PlayerInfo_.addProjectile_ + 3).substr(0, std::to_string(PlayerInfo_.addProjectile_ + 3).find("."));
	std::string sAtkSpeedNext = std::to_string(ceil(PlayerPInfo_.attackSpeed_Result * 0.75f)).substr(0, std::to_string(ceil(PlayerPInfo_.attackSpeed_Result * 0.75f)).find(".") );
	std::string sProjectileDurationNext = std::to_string(ceil(PlayerPInfo_.projectileDuration_Result * 0.7f)).substr(0, std::to_string(ceil(PlayerPInfo_.projectileDuration_Result * 0.7f)).find("."));

	etc_ = sAddProjectile + " -> " + sAddProjectileNext + " 추가 투사체\n"
		+ sProjectileDuration + "% ->" + sProjectileDurationNext + "% 투사체\n지속시간\n"
		+ sAtkSpeed + "% ->" + sAtkSpeedNext + "% 공격 속도 ";
}

void StoneHanded::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().get()->GetPlayerPassiveInfo();
	PlayerInfo_->addProjectile_ += 3;
	PlayerPInfo_->projectileDuration_ *= 0.7f;
	PlayerPInfo_->attackSpeed_ *= 0.75f;
	PlayerPInfo_->projectileDuration_Result *= 0.7f;
	PlayerPInfo_->attackSpeed_Result *= 0.75f;
	PlayerPInfo_->projectileDuration_ = ceil(PlayerPInfo_->projectileDuration_);
	PlayerPInfo_->attackSpeed_ = ceil(PlayerPInfo_->attackSpeed_);

}