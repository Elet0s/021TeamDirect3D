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
	float PlayerAttackSpeed = PlayPInfo_.attackSpeed_Per * PlayPInfo_.attackSpeed_;
	float PlayerAttackMul = PlayPInfo_.atkMultiple_ * PlayPInfo_.atkMultiple_Per;

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
	PlayPInfo_->attackSpeed_ = std::ceil(PlayPInfo_->attackSpeed_  * 0.95f * 100)/100;
	PlayPInfo_->atkMultiple_Per += 18.0f;
	PlayPInfo_->attackSpeed_Result = round(PlayPInfo_->attackSpeed_Per * PlayPInfo_->attackSpeed_);
	PlayPInfo_->atkMultiple_Result = round(PlayPInfo_->atkMultiple_Per * PlayPInfo_->atkMultiple_);
}