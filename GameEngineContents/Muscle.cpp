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
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sProjectileSize = std::to_string(PlayerInfo_.projectileSize_).substr(0, std::to_string(PlayerInfo_.projectileSize_).find(".") + 3);
	std::string sProjectileSizeNext = std::to_string(PlayerInfo_.projectileSize_ + 0.15f).substr(0, std::to_string(PlayerInfo_.projectileSize_ + 0.15f).find(".") + 3);
	
	etc_ = sProjectileSize + "% -> " + sProjectileSizeNext + "% 투사체\n크기 ";
}

void Muscle::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->projectileSize_ += 0.15f;
}