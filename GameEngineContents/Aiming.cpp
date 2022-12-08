#include "PreCompile.h"
#include "Aiming.h"
#include "Player.h"


Aiming::Aiming() 
{
	name_ = "조준";
	SetName(std::string_view("Aiming"));
	myRank_ = Rank::UnCommon;
	maxLevel_ = 4;
}

Aiming::~Aiming() 
{
}

void Aiming::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerPassiveInfo PlayPInfo_ = Player::GetPlayerInst().get()->GetPlayerPassiveInfo();
	float PlayerAttackSpeed = PlayerInfo_.attackSpeed_ * (PlayPInfo_.attackSpeed_/100);
	float PlayerAttackMul = PlayerInfo_.atkMultiple_ * 100 / PlayPInfo_.atkMultiple_;

	std::string sAttackMultiple = std::to_string(PlayerAttackMul).substr(0, std::to_string(PlayerAttackMul).find(".")) + "%";
	std::string sAttackMultipleNext = std::to_string(PlayerAttackMul + 18.0f).substr(0, std::to_string(PlayerAttackMul + 18.f).find(".")) + "%";
	std::string sAttackSpeed = std::to_string(PlayerAttackSpeed).substr(0, std::to_string(PlayerAttackSpeed).find(".")) + "%";
	std::string sAttackSpeedNext = std::to_string(ceil(PlayerAttackSpeed * 0.95f)).substr(0, std::to_string(ceil(PlayerAttackSpeed * 0.95f)).find(".")) + "%";

	etc_ = sAttackMultiple + " -> " + sAttackMultipleNext + " 피해 배수\n"
			+ sAttackSpeed + " -> " + sAttackSpeedNext + " 공격 속도 ";
	
}

void Aiming::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerPassiveInfo* PlayPInfo_ = &Player::GetPlayerInst().get()->GetPlayerPassiveInfo();
	PlayPInfo_->attackSpeed_ *= 0.95f;
	PlayPInfo_->attackSpeed_ = ceil(PlayPInfo_->attackSpeed_);
	PlayerInfo_->atkMultiple_ += 18.0f;
}