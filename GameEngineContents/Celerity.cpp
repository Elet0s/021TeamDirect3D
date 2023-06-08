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
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();

	std::string sAttackSpeed = std::to_string(PlayerPInfo_.attackSpeed_Result).substr(0, std::to_string(PlayerPInfo_.attackSpeed_Result).find(".")) + "%";
	std::string sAttackSpeedNext = std::to_string(ceil(PlayerPInfo_.attackSpeed_Result * 1.08f)).substr(0, std::to_string(ceil(PlayerPInfo_.attackSpeed_Result * 1.08f)).find(".")) + "%";


	etc_ = sAttackSpeed + " -> " + sAttackSpeedNext + " 공격 속도 ";
}

void Celerity::Effect()
{
	currentlevel_ += 1;
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().GetPlayerPassiveInfo();
	PlayerPInfo_->attackSpeed_ *= 1.08f;
	PlayerPInfo_->attackSpeed_Result *= 1.08f;
	PlayerPInfo_->attackSpeed_Result = ceil(PlayerPInfo_->attackSpeed_Result);
}