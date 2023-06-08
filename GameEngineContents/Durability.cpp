#include "PreCompile.h"
#include "Durability.h"
#include "Player.h"

Durability::Durability() 
{
	name_ = "내구성";
	SetName(std::string_view("Durability"));
	myRank_ = Rank::Spotted;
	maxLevel_ = 999;
}

Durability::~Durability() 
{
}

void Durability::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();

	std::string sHealing = std::to_string(PlayerInfo_.maxHp_).substr(0, std::to_string(PlayerInfo_.maxHp_).find("."));
	std::string sHealingNext = std::to_string(PlayerInfo_.maxHp_ + 10.f).substr(0, std::to_string(PlayerInfo_.maxHp_ + 10.f).find("."));

	etc_ = sHealing + " -> " + sHealingNext + " 최대 체력 ";
}

void Durability::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerInfo_->maxHp_ += 10.f;
}