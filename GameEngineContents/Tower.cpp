#include "PreCompile.h"
#include "Tower.h"
#include "Player.h"

Tower::Tower() 
{
	name_ = "타워";
	SetName(std::string_view("Tower"));
	myRank_ = Rank::Rare;
	maxLevel_ = 2;
}

Tower::~Tower() 
{
}

void Tower::Init()
{
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().get()->GetPlayerPassiveInfo();

	std::string sMaxHp = std::to_string(PlayerPInfo_.hpMax_Result).substr(0, std::to_string(PlayerPInfo_.hpMax_Result).find("."));
	std::string sMaxHpNext = std::to_string(PlayerPInfo_.hpMax_Result + 75.f).substr(0, std::to_string(PlayerPInfo_.hpMax_Result + 75.f).find("."));

	etc_ = sMaxHp + "% -> " + sMaxHpNext + "% 최대 체력 ";
}

void Tower::Effect()
{
	currentlevel_ += 1;
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().get()->GetPlayerPassiveInfo();
	PlayerPInfo_->hpMax_Per += 75.f;
	PlayerPInfo_->hpMax_Result += 75.f;
}