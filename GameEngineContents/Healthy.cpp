#include "PreCompile.h"
#include "Healthy.h"
#include "Player.h"

Healthy::Healthy() 
{
	name_ = "건강";
	SetName(std::string_view("Healthy"));
	myRank_ = Rank::Spotted;
	maxLevel_ = 999;
}

Healthy::~Healthy() 
{
}

void Healthy::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();

	std::string sHealing = std::to_string(PlayerInfo_.hpRecuvere_).substr(0, std::to_string(PlayerInfo_.hpRecuvere_).find(".") + 3);
	std::string sHealingNext = std::to_string(PlayerInfo_.hpRecuvere_ + 0.1f).substr(0, std::to_string(PlayerInfo_.hpRecuvere_ + 0.1f).find(".") + 3);

	etc_ = sHealing + " -> " + sHealingNext + " 체력 재생 ";
}

void Healthy::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerInfo_->hpRecuvere_ += 0.1f;
	PlayerInfo_->hpRecuvere_ = ceil(PlayerInfo_->hpRecuvere_ * 100) / 100;
}