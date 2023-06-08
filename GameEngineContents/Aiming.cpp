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
	PlayerPassiveInfo PlayPInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();

	std::string sAttackMultiple = std::to_string(ceil(PlayPInfo_.atkMultiple_Result)).substr(0, std::to_string(ceil(PlayPInfo_.atkMultiple_Result)).find(".")) + "%";
	std::string sAttackMultipleNext = std::to_string(PlayPInfo_.atkMultiple_Result + 18.0f).substr(0, std::to_string(PlayPInfo_.atkMultiple_Result + 18.f).find(".")) + "%";
	std::string sAttackSpeed = std::to_string(PlayPInfo_.attackSpeed_Result).substr(0, std::to_string(PlayPInfo_.attackSpeed_Result).find(".")) + "%";
	std::string sAttackSpeedNext = std::to_string(ceil(PlayPInfo_.attackSpeed_Result * 0.95f)).substr(0, std::to_string(ceil(PlayPInfo_.attackSpeed_Result * 0.95f)).find(".")) + "%";

	etc_ = sAttackMultiple + " -> " + sAttackMultipleNext + " 피해 배수\n"
		+ sAttackSpeed + " -> " + sAttackSpeedNext + " 공격 속도 ";

}

void Aiming::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerPassiveInfo* PlayPInfo_ = &Player::GetPlayerInst().GetPlayerPassiveInfo();
	PlayPInfo_->attackSpeed_ = PlayPInfo_->attackSpeed_  * 0.95f;
	PlayPInfo_->atkMultiple_Per += 18.0f;
	PlayPInfo_->attackSpeed_Result *= 0.95f;
	PlayPInfo_->attackSpeed_Result = ceil(PlayPInfo_->attackSpeed_Result);
	PlayPInfo_->atkMultiple_Result += 18.0f;
}