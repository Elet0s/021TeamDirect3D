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
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sMaxHp = std::to_string(PlayerInfo_.maxHp_).substr(0, std::to_string(PlayerInfo_.maxHp_).find(".") );
	std::string sMaxHpNext = std::to_string(PlayerInfo_.maxHp_ + 35.f).substr(0, std::to_string(PlayerInfo_.maxHp_ + 35.f).find("."));

	etc_ = sMaxHp + " -> " + sMaxHpNext + " 최대 체력 ";
}

void IronWill::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->maxHp_ += 35.f;
}