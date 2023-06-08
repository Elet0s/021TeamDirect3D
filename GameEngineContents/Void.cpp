#include "PreCompile.h"
#include "Void.h"
#include "Player.h"

Void::Void() 
{
	name_ = "°øÇã";
	SetName(std::string_view("Void"));
	myRank_ = Rank::Normal;
	maxLevel_ = 3;
}

Void::~Void() 
{
}

void Void::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();

	std::string sRuting_Range = std::to_string(PlayerInfo_.ruting_Range_).substr(0, std::to_string(PlayerInfo_.ruting_Range_).find(".") + 2);
	std::string sRuting_RangeNext = std::to_string(PlayerInfo_.ruting_Range_ + 1.5f).substr(0, std::to_string(PlayerInfo_.ruting_Range_ + 1.5f).find(".") + 2);



	etc_ = sRuting_Range + "m -> " + sRuting_RangeNext + "m È¹µæ ¹İ°æ ";
}

void Void::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerInfo_->ruting_Range_ += 1.5f;

}