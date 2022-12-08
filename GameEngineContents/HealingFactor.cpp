#include "PreCompile.h"
#include "HealingFactor.h"
#include "Player.h"

HealingFactor::HealingFactor() 
{
	name_ = "���";
	SetName(std::string_view("HealingFactor"));
	myRank_ = Rank::Normal;
	maxLevel_ = 5;

}

HealingFactor::~HealingFactor() 
{
}

void HealingFactor::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sHealing = std::to_string(PlayerInfo_.hpRecuvere_).substr(0, std::to_string(PlayerInfo_.projectileSize_).find(".") + 3 );
	std::string sHealingNext = std::to_string(PlayerInfo_.hpRecuvere_ + 0.5f).substr(0, std::to_string(PlayerInfo_.projectileSize_ + 0.15f).find(".") + 3);

	etc_ = sHealing + " -> " + sHealingNext + " ü�� ��� ";
}

void HealingFactor::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->hpRecuvere_ += 0.5f;
}