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

	std::string sAttackSpeed = std::to_string(PlayerInfo_.attackSpeed_).substr(0, std::to_string(PlayerInfo_.attackSpeed_).find(".")) + "%";
	std::string sAttackMultiple = std::to_string(PlayerInfo_.atkMultiple_).substr(0, std::to_string(PlayerInfo_.atkMultiple_).find(".")) + "%";
	std::string sAttackSpeedNext = std::to_string(ceil(PlayerInfo_.attackSpeed_ * 0.95f)).substr(0, std::to_string(PlayerInfo_.attackSpeed_ + 1.0f).find(".")) + "%";
	std::string sAttackMultipleNext = std::to_string(PlayerInfo_.atkMultiple_ + 18.0f).substr(0, std::to_string(PlayerInfo_.atkMultiple_).find(".")) + "%";
		
	etc_ = sAttackMultiple + " -> " + sAttackMultiple + " 피해 배수\n"
			+ sAttackSpeed + " -> " + sAttackSpeedNext + " 공격 속도 ";
	
}

void Aiming::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->attackSpeed_ *= 0.95f;
	PlayerInfo_->attackSpeed_ = ceil(PlayerInfo_->attackSpeed_);
	PlayerInfo_->atkMultiple_ += 18.0f;
}