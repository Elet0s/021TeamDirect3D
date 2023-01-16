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
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();
	

	std::string sAttackMultiple = std::to_string(PlayerPInfo_.atkMultiple_Result).substr(0, std::to_string(PlayerPInfo_.atkMultiple_Result).find(".")) + "%";
	std::string sAttackMultipleNext = std::to_string(PlayerPInfo_.atkMultiple_Result + 5.0f).substr(0, std::to_string(PlayerPInfo_.atkMultiple_Result + 5.0f).find(".")) + "%";
	
	etc_ = sAttackMultiple + " -> " + sAttackMultipleNext + " 피해 배수 ";
	
}

void DamascusSteel::Effect()
{
	currentlevel_ += 1;
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().GetPlayerPassiveInfo();
	PlayerPInfo_->atkMultiple_Per += 5.0f;
	PlayerPInfo_->atkMultiple_Result += 5.0f;;

}