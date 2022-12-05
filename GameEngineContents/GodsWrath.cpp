#include "PreCompile.h"
#include "GodsWrath.h"
#include "Player.h"

GodsWrath::GodsWrath() 
{
	name_ = "신의 격노";
	SetName(std::string_view("GodsWrath"));
	myRank_ = Rank::Rare;
	maxLevel_ = 4;
}

GodsWrath::~GodsWrath() 
{
}

void GodsWrath::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sAttackMultiple = std::to_string(PlayerInfo_.atkMultiple_).substr(0, std::to_string(PlayerInfo_.atkMultiple_).find(".")) + "%";
	std::string sAttackMultipleNext = std::to_string(PlayerInfo_.atkMultiple_ + 15.0f).substr(0, std::to_string(PlayerInfo_.atkMultiple_ + 15.0f).find(".")) + "%";

	etc_ = sAttackMultiple + " -> " + sAttackMultipleNext + " 피해 배수 ";
}

void GodsWrath::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->atkMultiple_ += 15.0f;
}