#include "PreCompile.h"
#include "LightArmor.h"
#include "Player.h"

LightArmor::LightArmor() 
{
	name_ = "경갑";
	SetName(std::string_view("LightArmor"));
	myRank_ = Rank::Normal;
	maxLevel_ = 5;
}

LightArmor::~LightArmor() 
{
}

void LightArmor::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();

	std::string sdamageMitigation_ = std::to_string(PlayerInfo_.damageMitigation_).substr(0, std::to_string(PlayerInfo_.damageMitigation_).find(".") + 2);
	std::string sdamageMitigation_Next = std::to_string(PlayerInfo_.damageMitigation_ + 2.0f).substr(0, std::to_string(PlayerInfo_.damageMitigation_ + 2.f).find(".") + 2);
	std::string sSpeed = std::to_string(ceil(PlayerInfo_.speed_ * (PlayerPInfo_.speed_Per / 100))).substr(0, std::to_string(ceil(PlayerInfo_.speed_ * (PlayerPInfo_.speed_Per / 100))).find("."));
	std::string sSpeedNext = std::to_string(ceil(PlayerInfo_.speed_ * ((PlayerPInfo_.speed_Per + 2.0f)/100))).substr(0, std::to_string(ceil(PlayerInfo_.speed_ * ((PlayerPInfo_.speed_Per + 2.0f) / 100))).find("."));


	etc_ = sdamageMitigation_ + " -> " + sdamageMitigation_Next + " 피해 완화\n"
		+ sSpeed + " ->" + sSpeedNext + "이동 속도 ";
}

void LightArmor::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().GetPlayerPassiveInfo();
	PlayerInfo_->damageMitigation_ += 2.f;
	PlayerPInfo_->speed_Per += 2.f;
}