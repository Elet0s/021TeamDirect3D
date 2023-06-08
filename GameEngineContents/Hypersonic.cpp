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
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();

	std::string sProjectileSpeed = std::to_string(PlayerPInfo_.projectileSpeed_Result).substr(0, std::to_string(PlayerPInfo_.projectileSpeed_Result).find(".")) + "%";
	std::string sProjectileSpeedNext = std::to_string(PlayerPInfo_.projectileSpeed_Result + 70.0f).substr(0, std::to_string(PlayerPInfo_.projectileSpeed_Result + 70.0f).find(".")) + "%";
	std::string sProjectileDuration = std::to_string(PlayerPInfo_.projectileDuration_Result).substr(0, std::to_string(PlayerPInfo_.projectileDuration_Result).find(".")) + "%";
	std::string sAProjectileDurationNext = std::to_string(ceil(PlayerPInfo_.projectileDuration_Result * 0.7f)).substr(0, std::to_string(ceil(PlayerPInfo_.projectileDuration_Result * 0.7f)).find(".")) + "%";

	etc_ = sProjectileSpeed + " -> " + sProjectileSpeedNext + " 투사체\n속도\n"
		+ sProjectileDuration + " -> " + sAProjectileDurationNext + " 투사체\n지속시간 ";
}

void Hypersonic::Effect()
{
	currentlevel_ += 1;
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().GetPlayerPassiveInfo();
	PlayerPInfo_->projectileSpeed_Per += 70.f;
	PlayerPInfo_->projectileDuration_ *= 0.7f;
	PlayerPInfo_->projectileSpeed_Result += 70.0f;
	PlayerPInfo_->projectileDuration_Result *= 0.7f;
	PlayerPInfo_->projectileDuration_Result = ceil(PlayerPInfo_->projectileDuration_Result);
}