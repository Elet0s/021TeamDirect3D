#include "PreCompile.h"
#include "Overloaded.h"
#include "Player.h"

Overloaded::Overloaded() 
{
	name_ = "과부화";
	SetName(std::string_view("Overladed"));
	
}

Overloaded::~Overloaded() 
{
}

void Overloaded::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sProjectileSize = std::to_string(PlayerInfo_.projectileSize_).substr(0, std::to_string(PlayerInfo_.projectileSize_).find(".") + 3);
	std::string sProjectileSizeNext = std::to_string(PlayerInfo_.projectileSize_ + 0.15f).substr(0, std::to_string(PlayerInfo_.projectileSize_ + 0.15f).find(".") + 3);

	etc_ = sProjectileSize + "% -> " + sProjectileSizeNext + "% 투사체\n크기 ";
}

void Overloaded::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->projectileSize_ += 0.15f;
}