#include "PreCompile.h"
#include "TensString.h"
#include "Player.h"

TensString::TensString() 
{
	name_ = "���";
	SetName(std::string_view("TenseString"));
	maxLevel_ = 3;
	myRank_ = Rank::UnCommon;
}

TensString::~TensString() 
{
}

void TensString::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sDamege = std::to_string(PlayerInfo_.atk_).substr(0, std::to_string(PlayerInfo_.atk_).find(".") + 3);

	if (currentlevel_ == 0)
	{
		etc_ = sDamege + "�⺻ ����";
	}
	else
	{
		std::string sDamegeNext = std::to_string(PlayerInfo_.atk_ + 0.1f).substr(0, std::to_string(PlayerInfo_.atk_ + 0.1f).find(".") + 3);
		etc_ = sDamege + "-> " + sDamegeNext + "�⺻ ����";
	}
}

void TensString::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->atk_ = round(PlayerInfo_->atk_ * 10) / 10;
	PlayerInfo_->atk_ += 0.1f;

}