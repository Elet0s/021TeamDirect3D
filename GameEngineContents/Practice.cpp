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
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();

	std::string sAttackSpeed = std::to_string(PlayerPInfo_.attackSpeed_Result).substr(0, std::to_string(PlayerPInfo_.attackSpeed_Result).find(".")) + "%";
	std::string sAttackMultiple = std::to_string(PlayerPInfo_.atkMultiple_Result).substr(0, std::to_string(PlayerPInfo_.atkMultiple_Result).find(".")) + "%";
	std::string sAttackSpeedNext = std::to_string(PlayerPInfo_.attackSpeed_Result + 1.0f).substr(0, std::to_string(PlayerPInfo_.attackSpeed_Result + 1.0f).find(".")) + "%";
	std::string sAttackMultipleNext = std::to_string(PlayerPInfo_.atkMultiple_Result + 3.0f).substr(0, std::to_string(PlayerPInfo_.atkMultiple_Result + 3.f).find(".")) + "%";
	
	etc_ = sAttackSpeed + " -> " + sAttackSpeedNext + " 공격 속도\n"
			+ sAttackMultiple + " -> " + sAttackMultipleNext + " 피해 배수 ";
	
}

void Practice::Effect()
{
	currentlevel_ += 1;
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().GetPlayerPassiveInfo();
	PlayerPInfo_->attackSpeed_Per += 1.0f;
	PlayerPInfo_->atkMultiple_Per += 3.0f;
	PlayerPInfo_->attackSpeed_Result += 1.0f;
	PlayerPInfo_->atkMultiple_Result += 3.0f;
}