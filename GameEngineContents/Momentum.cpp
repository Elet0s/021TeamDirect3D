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
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();

	std::string sProjectileSize = std::to_string(PlayerPInfo_.projectileSize_Result).substr(0, std::to_string(PlayerPInfo_.projectileSize_Result).find("."));
	std::string sKnockBack = std::to_string(PlayerInfo_.knockBack_).substr(0, std::to_string(PlayerInfo_.knockBack_).find("."));	
	std::string sProjectileSizeNext = std::to_string(PlayerPInfo_.projectileSize_Result + 5.f).substr(0, std::to_string(PlayerPInfo_.projectileSize_Result + 5.f).find("."));
	std::string sKnockBackNext = std::to_string(PlayerInfo_.knockBack_ +10.0f).substr(0, std::to_string(PlayerInfo_.knockBack_ + 10.f).find("."));
	
	etc_ = sProjectileSize + "% -> " + sProjectileSizeNext + "% 투사체\n크기\n"
			+ sKnockBack + "% ->" + sKnockBackNext + "% 넉백 " ;
}

void Momentum::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().GetPlayerPassiveInfo();
	PlayerPInfo_->projectileSize_Per += 5.0f;
	PlayerPInfo_->projectileSize_Result += 5.0f;
	PlayerInfo_->knockBack_ += 10.0f;

}