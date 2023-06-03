#include "PreCompile.h"
#include "Penetration.h"
#include "Player.h"

Penetration::Penetration() 
{
	name_ = "관통";
	SetName(std::string_view("Penetration"));
	myRank_ = Rank::Rare;
	maxLevel_ = 3;
}

Penetration::~Penetration() 
{
}

void Penetration::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();

	std::string sPassProjectile_ = std::to_string(PlayerInfo_.passProjectile_).substr(0, std::to_string(PlayerInfo_.passProjectile_).find("."));
	std::string sPassProjectile_Next = std::to_string(PlayerInfo_.passProjectile_ + 1.0f).substr(0, std::to_string(PlayerInfo_.passProjectile_ + 1.0f).find("."));
	std::string sAttackMultiple = std::to_string(PlayerPInfo_.atkMultiple_Result).substr(0, std::to_string(PlayerPInfo_.atkMultiple_Result).find(".")) + "%";
	std::string sAttackMultipleNext = std::to_string(PlayerPInfo_.atkMultiple_Result + 4.0f).substr(0, std::to_string(PlayerPInfo_.atkMultiple_Result + 4.0f).find(".")) + "%";

	etc_ = sPassProjectile_ + " -> " + sPassProjectile_Next + " 투사체\n관통\n"
		+ sAttackMultiple + " -> " + sAttackMultipleNext + " 피해 배수 ";

}

void Penetration::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().GetPlayerPassiveInfo();
	PlayerInfo_->passProjectile_ += 1;
	PlayerPInfo_->atkMultiple_Per += 4.0f;
	PlayerPInfo_->atkMultiple_Result += 4.0f;
}
