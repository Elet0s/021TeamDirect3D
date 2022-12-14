#include "PreCompile.h"
#include "Castle.h"
#include "Player.h"

Castle::Castle() 
{
	name_ = "캐슬";
	SetName(std::string_view("Castle"));
	myRank_ = Rank::Epic;
	maxLevel_ = 2;
}

Castle::~Castle() 
{
}

void Castle::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sMaxHp = std::to_string(PlayerInfo_.maxHp_).substr(0, std::to_string(PlayerInfo_.maxHp_).find("."));
	std::string sMaxHpNext = std::to_string(PlayerInfo_.maxHp_ + 25.f).substr(0, std::to_string(PlayerInfo_.maxHp_ + 25.f).find("."));
	std::string sDef = std::to_string(PlayerInfo_.def_).substr(0, std::to_string(PlayerInfo_.def_).find("."));
	std::string sDefNext = std::to_string(PlayerInfo_.def_ + 1.0f).substr(0, std::to_string(PlayerInfo_.def_ + 1.0f).find(".") + 3);

	etc_ = sMaxHp + " -> " + sMaxHpNext + " 최대 체력\n"
		+ sDef + "->" + sDefNext + " 방어력 ";
}

void Castle::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->maxHp_ += 25.f;
	PlayerInfo_->def_ += 1.f;

}