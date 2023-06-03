#include "PreCompile.h"
#include "LowPressure.h"
#include "Player.h"

LowPressure::LowPressure() 
{
	name_ = "저기압";
	SetName(std::string_view("LowPressure"));
	myRank_ = Rank::Spotted;
	maxLevel_ = 999;
}

LowPressure::~LowPressure() 
{
}

void LowPressure::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();

	std::string sRuting_Range = std::to_string(PlayerInfo_.ruting_Range_).substr(0, std::to_string(PlayerInfo_.ruting_Range_).find(".") + 2);
	std::string sRuting_RangeNext = std::to_string(PlayerInfo_.ruting_Range_ + 0.5f).substr(0, std::to_string(PlayerInfo_.ruting_Range_ + 0.5f).find(".") + 2);



	etc_ = sRuting_Range + "m -> " + sRuting_RangeNext + "m 획득 반경 ";
}

void LowPressure::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerInfo_->ruting_Range_ += 0.5f;
}