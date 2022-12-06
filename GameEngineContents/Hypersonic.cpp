#include "PreCompile.h"
#include "Hypersonic.h"
#include "Player.h"

Hypersonic::Hypersonic() 
{
	name_ = "초음속";
	SetName(std::string_view("Hypersonic"));
	myRank_ = Rank::Epic;
	maxLevel_ = 1;
}

Hypersonic::~Hypersonic() 
{
}

void Hypersonic::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sProjectileSpeed = std::to_string(PlayerInfo_.projectilespeed_).substr(0, std::to_string(PlayerInfo_.projectilespeed_).find(".")) + "%";
	std::string sProjectileSpeedNext = std::to_string(PlayerInfo_.projectilespeed_ + 70.0f).substr(0, std::to_string(PlayerInfo_.projectilespeed_ + 70.0f).find(".")) + "%";
	std::string sProjectileDuration = std::to_string(PlayerInfo_.projectileduration_).substr(0, std::to_string(PlayerInfo_.projectileduration_).find(".")) + "%";
	std::string sAProjectileDurationNext = std::to_string(PlayerInfo_.projectileduration_ * 0.7f).substr(0, std::to_string(PlayerInfo_.projectileduration_ * 0.7f).find(".")) + "%";

	etc_ = sProjectileSpeed + " -> " + sProjectileSpeedNext + " 투사체\n속도\n"
		+ sProjectileDuration + " -> " + sAProjectileDurationNext + " 투사체\n지속시간 ";
}

void Hypersonic::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->projectilespeed_ += 70.f;
	PlayerInfo_->projectileduration_ *= 0.7f;
}