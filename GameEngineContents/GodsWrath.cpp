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
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();

	std::string sAttackMultiple = std::to_string(PlayerPInfo_.atkMultiple_Result).substr(0, std::to_string(PlayerPInfo_.atkMultiple_Result).find(".")) + "%";
	std::string sAttackMultipleNext = std::to_string(PlayerPInfo_.atkMultiple_Result + 15.0f).substr(0, std::to_string(PlayerPInfo_.atkMultiple_Result + 15.0f).find(".")) + "%";

	etc_ = sAttackMultiple + " -> " + sAttackMultipleNext + " 피해 배수 ";
}

void GodsWrath::Effect()
{
	currentlevel_ += 1;
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().GetPlayerPassiveInfo();
	PlayerPInfo_->atkMultiple_ += 15.0f;
	PlayerPInfo_->atkMultiple_Result += 15.0f;
}