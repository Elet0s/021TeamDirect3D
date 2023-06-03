#include "PreCompile.h"
#include "IronSkin.h"
#include "Player.h"

IronSkin::IronSkin() 
{
	name_ = "철갑 피부";
	SetName(std::string_view("IronSkin"));
	myRank_ = Rank::UnCommon;
	maxLevel_ = 4;
}

IronSkin::~IronSkin() 
{
}

void IronSkin::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();

	std::string sDef = std::to_string(PlayerInfo_.def_).substr(0, std::to_string(PlayerInfo_.def_).find(".") + 3);
	std::string sDefNext = std::to_string(PlayerInfo_.def_ + 0.75f).substr(0, std::to_string(PlayerInfo_.def_ + 0.75f).find(".") + 3);

	etc_ = sDef + " -> " + sDefNext + " 방어력 ";
}

void IronSkin::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerInfo_->def_ += 0.75f;
}