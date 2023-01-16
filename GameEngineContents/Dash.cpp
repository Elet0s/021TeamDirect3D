#include "PreCompile.h"
#include "Dash.h"
#include "Player.h"

Dash::Dash() 
{
	name_ = "�뽬";
	SetName(std::string_view("Dash"));
	myRank_ = Rank::UnCommon;
	maxLevel_ = 3;
}

Dash::~Dash() 
{
}

void Dash::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();

	std::string sDashChargeCount = std::to_string(PlayerInfo_.dashFullCharge_).substr(0, std::to_string(PlayerInfo_.dashFullCharge_).find(".") );
	std::string sDashChargeCountNext = std::to_string(PlayerInfo_.dashFullCharge_ + 1).substr(0, std::to_string(PlayerInfo_.dashFullCharge_ + 1).find(".") );



	etc_ = sDashChargeCount + " -> " + sDashChargeCountNext + " �뽬 ���� ";
}

void Dash::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerInfo_->dashFullCharge_ += 1;

}