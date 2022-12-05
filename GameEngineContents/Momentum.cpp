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

	std::string sProjectileSize = std::to_string(PlayerInfo_.projectileSize_).substr(0, std::to_string(PlayerInfo_.projectileSize_).find(".") + 3);
	std::string sKnockBack = std::to_string(PlayerInfo_.knockBack_).substr(0, std::to_string(PlayerInfo_.knockBack_).find(".") + 3);

	if (currentlevel_ == 0)
	{
		etc_ = sProjectileSize + "% 투사체 크기\n" + sKnockBack + "넉백 ";
	}
	else
	{
		std::string sProjectileSizeNext = std::to_string(PlayerInfo_.projectileSize_ + 0.05f).substr(0, std::to_string(PlayerInfo_.projectileSize_ + 0.05f).find(".") + 3);
		std::string sKnockBackNext = std::to_string(PlayerInfo_.knockBack_ + 0.1f).substr(0, std::to_string(PlayerInfo_.knockBack_ + 0.1f).find(".") + 3);
		etc_ = sProjectileSize + "% -> " + sProjectileSizeNext + "% 투사체\n크기\n"
			+ sKnockBack + "% ->" + sKnockBackNext + "% 넉백 " ;
	}
}

void Momentum::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->projectileSize_ = round(PlayerInfo_->projectileSize_ * 100) / 100;
	PlayerInfo_->projectileSize_ += 0.05f;
	//PlayerInfo_->knockBack_ = round(PlayerInfo_->atk_ * 100) / 100;
	PlayerInfo_->knockBack_ += 0.1f;

}