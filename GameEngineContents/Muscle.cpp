#include "PreCompile.h"
#include "Muscle.h"
#include "Player.h"


Muscle::Muscle() 
{
	name_ = "벌크업";
	SetName(std::string_view("Muscle"));
	maxLevel_ = 3;
	myRank_ = Rank::Normal;
}

Muscle::~Muscle() 
{
}

void Muscle::Init()
{
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();

	std::string sProjectileSize = std::to_string(PlayerPInfo_.projectileSize_Result).substr(0, std::to_string(PlayerPInfo_.projectileSize_Result).find("."));
	std::string sProjectileSizeNext = std::to_string(PlayerPInfo_.projectileSize_Result + 15.f).substr(0, std::to_string(PlayerPInfo_.projectileSize_Result + 15.f).find(".") );

	etc_ = sProjectileSize + "% -> " + sProjectileSizeNext + "% 투사체\n크기 ";
}

void Muscle::Effect()
{
	currentlevel_ += 1;
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().GetPlayerPassiveInfo();
	PlayerPInfo_->projectileSize_Per += 15.f;
	PlayerPInfo_->projectileSize_Result += 15.f;
}