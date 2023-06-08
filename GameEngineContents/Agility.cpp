#include "PreCompile.h"
#include "Agility.h"
#include "Player.h"

Agility::Agility() 
{
	name_ = "민첩함";
	SetName(std::string_view("Agility"));
	myRank_ = Rank::Normal;
	maxLevel_ = 4;
}

Agility::~Agility() 
{
}

void Agility::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();

	std::string sSpeed = std::to_string(ceil(PlayerInfo_.speed_ * PlayerPInfo_.speed_Per / 100)).substr(0, std::to_string(ceil(PlayerInfo_.speed_ * PlayerPInfo_.speed_Per / 100)).find("."));
	std::string sSpeedNext = std::to_string(ceil(PlayerInfo_.speed_ * (PlayerPInfo_.speed_Per + 10.f) / 100)).substr(0, std::to_string(ceil(PlayerInfo_.speed_ * (PlayerPInfo_.speed_Per + 25.f) / 100)).find("."));



	etc_ = sSpeed + " -> " + sSpeedNext + " 이동 속도 ";
}

void Agility::Effect()
{
	currentlevel_ += 1;
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().GetPlayerPassiveInfo();
	PlayerPInfo_->speed_Per += 10.f;

}