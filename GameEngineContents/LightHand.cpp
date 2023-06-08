#include "PreCompile.h"
#include "LightHand.h"
#include "Player.h"

LightHand::LightHand() 
{
	name_ = "가벼운 손";
	SetName(std::string_view("LightHand"));
	myRank_ = Rank::Epic;
	maxLevel_ = 1;
}

LightHand::~LightHand() 
{
}

void LightHand::Init()
{
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();

	std::string sAttackSpeed = std::to_string(PlayerPInfo_.attackSpeed_Result).substr(0, std::to_string(PlayerPInfo_.attackSpeed_Result).find(".")) + "%";
	std::string sAttackSpeedNext = std::to_string(ceil(PlayerPInfo_.attackSpeed_Result * 1.33f)).substr(0, std::to_string(ceil(PlayerPInfo_.attackSpeed_Result * 1.33f)).find(".")) + "%";
	std::string sAttackMul = std::to_string(PlayerPInfo_.atkMultiple_Result).substr(0, std::to_string(PlayerPInfo_.atkMultiple_Result).find(".")) + "%";
	std::string sAttackMulNext = std::to_string(ceil(PlayerPInfo_.atkMultiple_Result * 0.8f)).substr(0, std::to_string(ceil(PlayerPInfo_.atkMultiple_Result * 0.8f)).find(".")) + "%";

	etc_ = sAttackSpeed + " -> " + sAttackSpeedNext + " 공격속도\n"
		+ sAttackMul + " -> " + sAttackMulNext + " 피해\n배수 ";
}

void LightHand::Effect()
{
	currentlevel_ += 1;
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().GetPlayerPassiveInfo();
	PlayerPInfo_->attackSpeed_ *= 1.33f;
	PlayerPInfo_->atkMultiple_ *= 0.8f;

	PlayerPInfo_->attackSpeed_Result *= 1.33f;
	PlayerPInfo_->atkMultiple_Result *= 0.8f;
	PlayerPInfo_->attackSpeed_Result = ceil(PlayerPInfo_->attackSpeed_Result);
	PlayerPInfo_->atkMultiple_Result = ceil(PlayerPInfo_->atkMultiple_Result);
}