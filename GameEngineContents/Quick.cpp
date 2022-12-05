#include "PreCompile.h"
#include "Quick.h"
#include "Player.h"

Quick::Quick() 
{
	name_ = "�ż�";
	SetName(std::string_view("Quick"));
	myRank_ = Rank::UnCommon;
	maxLevel_ = 1;
}

Quick::~Quick() 
{
}

void Quick::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sProjectileSpeed = std::to_string(PlayerInfo_.projectilespeed_).substr(0, std::to_string(PlayerInfo_.projectilespeed_).find(".")) + "%";
	std::string sProjectileSpeedNext = std::to_string(PlayerInfo_.projectilespeed_ + 25.0f).substr(0, std::to_string(PlayerInfo_.projectilespeed_ + 25.0f).find(".")) + "%";
	std::string sSpeed = std::to_string(PlayerInfo_.speed_).substr(0, std::to_string(PlayerInfo_.speed_).find("."));
	std::string sSpeedNext = std::to_string(PlayerInfo_.speed_ * 1.25f).substr(0, std::to_string(PlayerInfo_.speed_ + 1.25f).find("."));
	std::string sProjectileSize = std::to_string(PlayerInfo_.projectileSize_).substr(0, std::to_string(PlayerInfo_.projectileSize_).find(".")) + "%";
	std::string sProjectileSizeNext = std::to_string(PlayerInfo_.projectileSize_ - 25.0f).substr(0, std::to_string(PlayerInfo_.projectileSize_ - 25.0f).find(".")) + "%";

	
	etc_ = sProjectileSpeed + " -> " + sProjectileSpeedNext + " ����ü �ӵ�\n"
		+ sSpeed + " -> " + sSpeedNext + "�̵��ӵ�\n"
		+ sProjectileSize + " -> " + sProjectileSizeNext + " ����ü ũ�� ";

}

void Quick::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->projectilespeed_ += 25.0f;
	PlayerInfo_->speed_ *= 1.25f;
	PlayerInfo_->projectileSize_ -= 25.0f;

}