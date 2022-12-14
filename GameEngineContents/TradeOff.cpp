#include "PreCompile.h"
#include "TradeOff.h"
#include "Player.h"

TradeOff::TradeOff() 
{
	name_ = "절충";
	SetName(std::string_view("TradeOff"));
	myRank_ = Rank::UnCommon;
	maxLevel_ = 2;
}

TradeOff::~TradeOff() 
{
}

void TradeOff::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().get()->GetPlayerPassiveInfo();

	std::string sAddProjectile = std::to_string(PlayerInfo_.addProjectile_).substr(0, std::to_string(PlayerInfo_.addProjectile_).find("."));
	std::string sAttackSpeed = std::to_string(PlayerPInfo_.attackSpeed_Result).substr(0, std::to_string(PlayerPInfo_.attackSpeed_Result).find(".")) + "%";
	std::string sAddProjectileNext = std::to_string(PlayerInfo_.addProjectile_ - 1).substr(0, std::to_string(PlayerInfo_.addProjectile_ - 1).find("."));
	std::string sAttackSpeedNext = std::to_string(ceil(PlayerPInfo_.attackSpeed_Result * 1.25f)).substr(0, std::to_string(ceil(PlayerPInfo_.attackSpeed_Result * 1.25f)).find(".")) + "%";


	etc_ = sAttackSpeed + " -> " + sAttackSpeedNext + " 공격 속도\n"
		+ sAddProjectile + " -> " + sAddProjectileNext + " 추가 투사체 ";
}

void TradeOff::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().get()->GetPlayerPassiveInfo();
	PlayerInfo_->addProjectile_ -= 1;
	PlayerPInfo_->attackSpeed_ *= 1.25f;
	PlayerPInfo_->attackSpeed_Result *= 1.25f;
	PlayerPInfo_->attackSpeed_Result = ceil(PlayerPInfo_->attackSpeed_Result);
}