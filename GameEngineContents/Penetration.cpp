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
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sAddProjectile = std::to_string(PlayerInfo_.addProjectile_).substr(0, std::to_string(PlayerInfo_.addProjectile_).find("."));
	std::string sAddProjectileNext = std::to_string(PlayerInfo_.addProjectile_ + 1.0f).substr(0, std::to_string(PlayerInfo_.addProjectile_ + 1.0f).find("."));
	std::string sAttackMultiple = std::to_string(PlayerInfo_.atkMultiple_).substr(0, std::to_string(PlayerInfo_.atkMultiple_).find(".")) + "%";
	std::string sAttackMultipleNext = std::to_string(PlayerInfo_.atkMultiple_ + 4.0f).substr(0, std::to_string(PlayerInfo_.atkMultiple_ + 4.0f).find(".")) + "%";

	etc_ = sAddProjectile + " -> " + sAddProjectileNext + " 추가 투사체\n"
		+ sAttackMultiple + " -> " + sAttackMultipleNext + " 피해 배수 ";

}

void Penetration::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->addProjectile_ += 1;
	PlayerInfo_->atkMultiple_ += 4.0f;
}