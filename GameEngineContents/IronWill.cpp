#include "PreCompile.h"
#include "IronWill.h"
#include "Player.h"

IronWill::IronWill() 
{
	name_ = "불굴의 의지";
	SetName(std::string_view("IronWill"));
	myRank_ = Rank::Normal;
	maxLevel_ = 4;
}

IronWill::~IronWill() 
{
}

void IronWill::Init()
{
	PlayerPassiveInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();

	std::string sMaxHp = std::to_string(PlayerInfo_.hpMax_Result).substr(0, std::to_string(PlayerInfo_.hpMax_Result).find(".") );
	std::string sMaxHpNext = std::to_string(PlayerInfo_.hpMax_Result + 35.f).substr(0, std::to_string(PlayerInfo_.hpMax_Result + 35.f).find("."));

	etc_ = sMaxHp + "% -> " + sMaxHpNext + "% 최대 체력 ";
}

void IronWill::Effect()
{
	currentlevel_ += 1;
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().GetPlayerPassiveInfo();
	PlayerPInfo_->hpMax_Per += 35.f;
	PlayerPInfo_->hpMax_Result += 35.f;
}