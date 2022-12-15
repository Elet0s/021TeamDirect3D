#include "PreCompile.h"
#include "DashCooldown.h"
#include "Player.h"

DashCooldown::DashCooldown() 
{
	name_ = "대쉬 쿨타임 감소";
	SetName(std::string_view("DashCoolDown"));
	myRank_ = Rank::Rare;
	maxLevel_ = 3;
}

DashCooldown::~DashCooldown() 
{
}

void DashCooldown::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sDashReChargeTime = std::to_string(PlayerInfo_.dashReChargeTime_).substr(0, std::to_string(PlayerInfo_.dashReChargeTime_).find(".") +3 );
	std::string sDashReChargeTimeNext = std::to_string(PlayerInfo_.dashReChargeTime_ * 0.8).substr(0, std::to_string(PlayerInfo_.dashReChargeTime_ * 0.8).find(".") + 3);



	etc_ = sDashReChargeTime + " -> " + sDashReChargeTimeNext + " 대쉬\n 재충전 시간 ";
}

void DashCooldown::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->dashReChargeTime_ *= 0.80f;
	
}