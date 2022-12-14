#include "PreCompile.h"
#include "BlackBlood.h"
#include "Player.h"

BlackBlood::BlackBlood() 
{
	name_ = "검은 피";
	SetName(std::string_view("BlackBlood"));
	myRank_ = Rank::Normal;
	maxLevel_ = 5;
}

BlackBlood::~BlackBlood() 
{
}

void BlackBlood::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sHealing = std::to_string(PlayerInfo_.hpRecuvere_).substr(0, std::to_string(PlayerInfo_.hpRecuvere_).find(".") + 3);
	std::string sHealingNext = std::to_string(PlayerInfo_.hpRecuvere_ + 1.0f).substr(0, std::to_string(PlayerInfo_.hpRecuvere_ + 1.f).find(".") + 3);
	std::string sMaxHp = std::to_string(PlayerInfo_.maxHp_).substr(0, std::to_string(PlayerInfo_.maxHp_).find("."));
	std::string sMaxHpNext = std::to_string(PlayerInfo_.maxHp_ - 5.0f).substr(0, std::to_string(PlayerInfo_.maxHp_ - 5.f).find("."));


	etc_ = sHealing + " -> " + sHealingNext + " 체력 재생\n"
		+ sMaxHp + " ->" + sMaxHpNext + " 최대 체력 ";
}

void BlackBlood::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->hpRecuvere_ += 1.f;
	PlayerInfo_->maxHp_ -= 5.f;
}