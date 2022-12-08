#include "PreCompile.h"
#include "Healthy.h"
#include "Player.h"

Healthy::Healthy() 
{
	name_ = "건강";
	SetName(std::string_view("Healthy"));
	myRank_ = Rank::Spotted;
	maxLevel_ = 999;
}

Healthy::~Healthy() 
{
}

void Healthy::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sProjectileSize = std::to_string(PlayerInfo_.projectileSize_).substr(0, std::to_string(PlayerInfo_.projectileSize_).find(".") + 3);
	std::string sProjectileSizeNext = std::to_string(PlayerInfo_.projectileSize_ + 0.15f).substr(0, std::to_string(PlayerInfo_.projectileSize_ + 0.15f).find(".") + 3);

	etc_ = sProjectileSize + "% -> " + sProjectileSizeNext + "% 투사체\n크기 ";
}

void Healthy::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->projectileSize_ += 0.15f;
}