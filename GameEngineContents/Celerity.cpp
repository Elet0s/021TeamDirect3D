#include "PreCompile.h"
#include "Celerity.h"
#include "Player.h"

Celerity::Celerity() 
{
	name_ = "가속";
	SetName(std::string_view("Celerity"));
	myRank_ = Rank::Rare;
	maxLevel_ = 4;
}

Celerity::~Celerity() 
{
}

void Celerity::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sAttackSpeed = std::to_string(PlayerInfo_.attackSpeed_).substr(0, std::to_string(PlayerInfo_.attackSpeed_).find(".")) + "%";
	std::string sAttackSpeedNext = std::to_string(PlayerInfo_.attackSpeed_ + 8.0f).substr(0, std::to_string(PlayerInfo_.attackSpeed_ + 8.0f).find(".")) + "%";


	etc_ = sAttackSpeed + " -> " + sAttackSpeedNext + " 공격 속도 ";
}

void Celerity::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->attackSpeed_ += 8.0f;
}