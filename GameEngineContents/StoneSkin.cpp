#include "PreCompile.h"
#include "StoneSkin.h"
#include "Player.h"

StoneSkin::StoneSkin() 
{
	name_ = "단단한 피부";
	SetName(std::string_view("StoneSkin"));
	myRank_ = Rank::Spotted;
	maxLevel_ = 999;
}

StoneSkin::~StoneSkin() 
{
}

void StoneSkin::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sDef = std::to_string(PlayerInfo_.def_).substr(0, std::to_string(PlayerInfo_.def_).find(".") + 3);
	std::string sDefNext = std::to_string(PlayerInfo_.def_ + 0.25f).substr(0, std::to_string(PlayerInfo_.def_ + 0.25f).find(".") + 3);

	etc_ = sDef + " -> " + sDefNext + " 방어력 ";
}

void StoneSkin::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->def_ += 0.25f;
}