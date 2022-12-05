#include "PreCompile.h"
#include "Area.h"
#include "Player.h"

Area::Area() 
{
	name_ = "범위";
	SetName(std::string_view("Area"));
	myRank_ = Rank::UnCommon;
	maxLevel_ = 4;
}

Area::~Area() 
{
}

void Area::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sRangeSize = std::to_string(PlayerInfo_.rangeSize_).substr(0, std::to_string(PlayerInfo_.attackSpeed_).find(".")) + "%";
	std::string sRangeSizeNext = std::to_string(PlayerInfo_.rangeSize_ + 15.0f).substr(0, std::to_string(PlayerInfo_.attackSpeed_ + 1.0f).find(".")) + "%";

	etc_ = sRangeSize + " -> " + sRangeSizeNext + " 공격 범위\n크기 ";

}

void Area::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->rangeSize_ += 15.0f;

}