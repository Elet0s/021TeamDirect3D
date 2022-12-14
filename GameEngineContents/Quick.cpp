#include "PreCompile.h"
#include "Quick.h"
#include "Player.h"

Quick::Quick() 
{
	name_ = "신속";
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
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().get()->GetPlayerPassiveInfo();

	std::string sProjectileSpeed = std::to_string(PlayerPInfo_.projectileSpeed_Result).substr(0, std::to_string(PlayerPInfo_.projectileSpeed_Result).find(".")) + "%";
	std::string sProjectileSpeedNext = std::to_string(PlayerPInfo_.projectileSpeed_Result + 25.0f).substr(0, std::to_string(PlayerPInfo_.projectileSpeed_Result + 25.0f).find(".")) + "%";
	std::string sSpeed = std::to_string(ceil(PlayerInfo_.speed_ * PlayerPInfo_.speed_Per / 100)).substr(0, std::to_string(ceil(PlayerInfo_.speed_ * PlayerPInfo_.speed_Per / 100)).find("."));
	std::string sSpeedNext = std::to_string(ceil(PlayerInfo_.speed_ * (PlayerPInfo_.speed_Per + 25.f) / 100)).substr(0, std::to_string(ceil(PlayerInfo_.speed_ *( PlayerPInfo_.speed_Per + 25.f) / 100)).find("."));
	std::string sProjectileSize = std::to_string(PlayerPInfo_.projectileSize_Result).substr(0, std::to_string(PlayerPInfo_.projectileSize_Result).find(".")) + "%";
	std::string sProjectileSizeNext = std::to_string(PlayerPInfo_.projectileSize_Result - 25.0f).substr(0, std::to_string(PlayerPInfo_.projectileSize_Result - 25.0f).find(".")) + "%";

	
	etc_ = sProjectileSpeed + " -> " + sProjectileSpeedNext + " 투사체 속도\n"
		+ sSpeed + " -> " + sSpeedNext + " 이동속도\n"
		+ sProjectileSize + " -> " + sProjectileSizeNext + " 투사체 크기 ";

}

void Quick::Effect()
{
	currentlevel_ += 1;
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().get()->GetPlayerPassiveInfo();
	PlayerPInfo_->speed_Per += 25.f;
	PlayerPInfo_->speed_Per;
	PlayerPInfo_->projectileSpeed_Per += 25.0f;
	PlayerPInfo_->projectileSize_Per -= 25.0f;
	PlayerPInfo_->projectileSpeed_Result += 25.0f;
	PlayerPInfo_->projectileSize_Result -= 25.0f;
}