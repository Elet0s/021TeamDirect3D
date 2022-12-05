#include "PreCompile.h"
#include "DamascusSteel.h"
#include "Player.h"


DamascusSteel::DamascusSteel() 
{
	name_ = "다마스쿠스 강철";
	SetName(std::string_view("DamascusSteel"));
	myRank_ = Rank::Normal;
	maxLevel_ = 6;
}

DamascusSteel::~DamascusSteel() 
{
}

void DamascusSteel::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sAttackMultiple = std::to_string(PlayerInfo_.atkMultiple_).substr(0, std::to_string(PlayerInfo_.atkMultiple_).find(".")) + "%";
	std::string sAttackMultipleNext = std::to_string(PlayerInfo_.atkMultiple_ + 5.0f).substr(0, std::to_string(PlayerInfo_.atkMultiple_ + 5.0f).find(".")) + "%";
	
	etc_ = sAttackMultiple + " -> " + sAttackMultiple + " 피해 배수 ";
	
}

void DamascusSteel::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->atkMultiple_ += 5.0f;

}