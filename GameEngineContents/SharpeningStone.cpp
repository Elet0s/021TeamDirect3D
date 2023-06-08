#include "PreCompile.h"
#include "SharpeningStone.h"
#include "Player.h"

SharpeningStone::SharpeningStone() 
{
	name_ = "숫돌";
	SetName(std::string_view("SharpeningStone"));
	myRank_ = Rank::Normal;
}

SharpeningStone::~SharpeningStone() 
{
}

void SharpeningStone::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();

	std::string sDamege = std::to_string(PlayerInfo_.atk_).substr(0, std::to_string(PlayerInfo_.atk_).find(".") + 3);
	std::string sDamegeNext = std::to_string(PlayerInfo_.atk_ + 0.1f).substr(0, std::to_string(PlayerInfo_.atk_ + 0.1f).find(".") + 3);
		
	etc_ = sDamege + "-> " + sDamegeNext + "기본 피해";
}

void SharpeningStone::Effect()
{
	currentlevel_ += 1;
	PlayerInfo *PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerInfo_->atk_ = round(PlayerInfo_->atk_ * 100) / 100;
	PlayerInfo_->atk_ += 0.1f;		

}