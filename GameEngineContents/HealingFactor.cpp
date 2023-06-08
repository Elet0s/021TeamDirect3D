#include "PreCompile.h"
#include "HealingFactor.h"
#include "Player.h"

HealingFactor::HealingFactor() 
{
	name_ = "재생";
	SetName(std::string_view("HealingFactor"));
	myRank_ = Rank::Normal;
	maxLevel_ = 5;

}

HealingFactor::~HealingFactor() 
{
}

void HealingFactor::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();

	std::string sHealing = std::to_string(PlayerInfo_.hpRecuvere_).substr(0, std::to_string(PlayerInfo_.hpRecuvere_).find(".") + 3 );
	std::string sHealingNext = std::to_string(PlayerInfo_.hpRecuvere_ + 0.5f).substr(0, std::to_string(PlayerInfo_.hpRecuvere_ + 0.15f).find(".") + 3);

	etc_ = sHealing + " -> " + sHealingNext + " 체력 재생 ";
}

void HealingFactor::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerInfo_->hpRecuvere_ += 0.5f;
	PlayerInfo_->hpRecuvere_ = ceil(PlayerInfo_->hpRecuvere_ * 100) / 100;
}