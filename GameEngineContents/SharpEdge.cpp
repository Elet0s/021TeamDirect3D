#include "PreCompile.h"
#include "SharpEdge.h"
#include "Player.h"

SharpEdge::SharpEdge() 
{
	name_ = "날카로운 칼날";
	SetName(std::string_view("SharpEdge"));
	maxLevel_ = 6;
	myRank_ = Rank::Normal;
}

SharpEdge::~SharpEdge() 
{
}

void SharpEdge::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();

	std::string sDamege = std::to_string(PlayerInfo_.atk_).substr(0, std::to_string(PlayerInfo_.atk_).find(".") + 3);
	std::string sDamegeNext = std::to_string(PlayerInfo_.atk_ + 0.25f).substr(0, std::to_string(PlayerInfo_.atk_ + 0.25f).find(".") + 3);
		
	etc_ = sDamege + "-> " + sDamegeNext + "기본 피해";
}

void SharpEdge::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerInfo_->atk_ = ceil(PlayerInfo_->atk_ * 100) / 100;
	PlayerInfo_->atk_ += 0.25f;

}