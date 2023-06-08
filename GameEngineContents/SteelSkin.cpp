#include "PreCompile.h"
#include "SteelSkin.h"
#include "Player.h"

SteelSkin::SteelSkin() 
{
	name_ = "강철 피부";
	SetName(std::string_view("SteelSkin"));
	myRank_ = Rank::Rare;
	maxLevel_ = 2;
}

SteelSkin::~SteelSkin() 
{
}

void SteelSkin::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();

	std::string sDef = std::to_string(PlayerInfo_.def_).substr(0, std::to_string(PlayerInfo_.def_).find(".") + 3);
	std::string sDefNext = std::to_string(PlayerInfo_.def_ + 1.5f).substr(0, std::to_string(PlayerInfo_.def_ + 1.5f).find(".") + 3);

	etc_ = sDef + " -> " + sDefNext + " 방어력 ";
}

void SteelSkin::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerInfo_->def_ += 1.5f;
}