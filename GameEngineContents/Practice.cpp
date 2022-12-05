#include "PreCompile.h"
#include "Practice.h"
#include "Player.h"

Practice::Practice() 
{
	name_ = "연습";
	SetName(std::string_view("Practice"));
	myRank_ = Rank::Normal;
	maxLevel_ = 10;
}

Practice::~Practice() 
{
}

void Practice::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sAttackSpeed = std::to_string(PlayerInfo_.attackSpeed_).substr(0, std::to_string(PlayerInfo_.attackSpeed_).find(".")) + "%";
	std::string sAttackMultiple = std::to_string(PlayerInfo_.atkMultiple_).substr(0, std::to_string(PlayerInfo_.atkMultiple_).find(".")) + "%";
	std::string sAttackSpeedNext = std::to_string(PlayerInfo_.attackSpeed_ + 1.0f).substr(0, std::to_string(PlayerInfo_.attackSpeed_ + 1.0f).find(".")) + "%";
	std::string sAttackMultipleNext = std::to_string(PlayerInfo_.atkMultiple_ + 3.0f).substr(0, std::to_string(PlayerInfo_.atkMultiple_).find(".")) + "%";
	
	etc_ = sAttackSpeed + " -> " + sAttackSpeedNext + " 공격 속도\n"
			+ sAttackMultiple + " -> " + sAttackMultipleNext + " 피해 배수 ";
	
}

void Practice::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->attackSpeed_ += 1.0f;
	PlayerInfo_->atkMultiple_ += 3.0f;
}