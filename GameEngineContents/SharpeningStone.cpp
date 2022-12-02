#include "PreCompile.h"
#include "SharpeningStone.h"
#include "Player.h"

SharpeningStone::SharpeningStone() 
{
	SetName(std::string_view("숫돌"));
}

SharpeningStone::~SharpeningStone() 
{
}

void SharpeningStone::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sDamege = std::to_string(PlayerInfo_.atk_).substr(0, std::to_string(PlayerInfo_.atk_).find(".") + 3);

	if (level_ == 0)
	{
		etc_ = sDamege + "기본 피해";
	}
	else
	{
		std::string sDamegeNext = std::to_string(PlayerInfo_.atk_ + 0.1f).substr(0, std::to_string(PlayerInfo_.atk_ + 0.1f).find(".") + 3);
		etc_ = sDamege + "-> " + sDamegeNext + "기본 피해";
	}
}

void SharpeningStone::Effect()
{
	level_ += 1;
	PlayerInfo *PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->atk_ = round(PlayerInfo_->atk_ * 10) / 10;
	PlayerInfo_->atk_ += 0.1f;		

}