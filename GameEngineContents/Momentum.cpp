#include "PreCompile.h"
#include "Momentum.h"
#include "Player.h"

Momentum::Momentum() 
{
	name_ = "추진력";
	SetName(std::string_view("Momentum"));
	maxLevel_ = 5;
	myRank_ = Rank::Normal;
}

Momentum::~Momentum() 
{
}

void Momentum::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sProjectileSize = std::to_string(PlayerInfo_.projectileSize_).substr(0, std::to_string(PlayerInfo_.projectileSize_).find("."));
	std::string sKnockBack = std::to_string(PlayerInfo_.knockBack_).substr(0, std::to_string(PlayerInfo_.knockBack_).find("."));	
	std::string sProjectileSizeNext = std::to_string(PlayerInfo_.projectileSize_ + 5.f).substr(0, std::to_string(PlayerInfo_.projectileSize_ + 5.f).find("."));
	std::string sKnockBackNext = std::to_string(PlayerInfo_.knockBack_ +10.0f).substr(0, std::to_string(PlayerInfo_.knockBack_ + 10.f).find("."));
	
	etc_ = sProjectileSize + "% -> " + sProjectileSizeNext + "% 투사체\n크기\n"
			+ sKnockBack + "% ->" + sKnockBackNext + "% 넉백 " ;
}

void Momentum::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	//PlayerInfo_->projectileSize_ = round(PlayerInfo_->projectileSize_ * 100) / 100;
	PlayerInfo_->projectileSize_ += 5.0f;
	//PlayerInfo_->knockBack_ = round(PlayerInfo_->atk_ * 100) / 100;
	PlayerInfo_->knockBack_ += 10.0f;

}