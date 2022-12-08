#include "PreCompile.h"
#include "LightArmor.h"
#include "Player.h"

LightArmor::LightArmor() 
{
	name_ = "�氩";
	SetName(std::string_view("LightArmor"));
	myRank_ = Rank::Normal;
	maxLevel_ = 5;
}

LightArmor::~LightArmor() 
{
}

void LightArmor::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sHealing = std::to_string(PlayerInfo_.hpRecuvere_).substr(0, std::to_string(PlayerInfo_.hpRecuvere_).find(".") + 3);
	std::string sHealingNext = std::to_string(PlayerInfo_.hpRecuvere_ + 1.0f).substr(0, std::to_string(PlayerInfo_.hpRecuvere_ + 1.f).find(".") + 3);
	std::string sMaxHp = std::to_string(PlayerInfo_.speed_).substr(0, std::to_string(PlayerInfo_.speed_).find("."));
	std::string sMaxHpNext = std::to_string(PlayerInfo_.speed_ - 10.0f).substr(0, std::to_string(PlayerInfo_.speed_ - 10.f).find("."));


	etc_ = sHealing + " -> " + sHealingNext + " ü�� ���\n"
		+ sMaxHp + " ->" + sMaxHpNext + "�ִ� ü�� ";
}

void LightArmor::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->hpRecuvere_ += 1.f;
	PlayerInfo_->maxHp_ -= 10.f;
}