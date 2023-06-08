#include "PreCompile.h"
#include "Compromise.h"
#include "Player.h"

Compromise::Compromise() 
{
	name_ = "타협";
	SetName(std::string_view("Compromise"));
	myRank_ = Rank::Normal;
	maxLevel_ = 1;
}

Compromise::~Compromise() 
{
}

void Compromise::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();

	std::string sAddProjectile = std::to_string(PlayerInfo_.addProjectile_).substr(0, std::to_string(PlayerInfo_.addProjectile_).find("."));
	std::string sAttack = std::to_string((PlayerInfo_.atk_ * PlayerPInfo_.atkMultiple_Result / 100)).substr(0, std::to_string((PlayerInfo_.atk_ * PlayerPInfo_.atkMultiple_Result / 100)).find(".") + 3);
	std::string sAddProjectileNext = std::to_string(PlayerInfo_.addProjectile_ + 1.0f).substr(0, std::to_string(PlayerInfo_.addProjectile_ + 1.0f).find("."));
	std::string sAttackNext = std::to_string((PlayerInfo_.atk_ -0.35f) * PlayerPInfo_.atkMultiple_Result / 100).substr(0, std::to_string(((PlayerInfo_.atk_ - 0.35f) * PlayerPInfo_.atkMultiple_Result / 100) -0.35f).find(".") + 3);


	etc_ = sAddProjectile + " -> " + sAddProjectileNext + " 추가 투사체\n"
		+ sAttack + " -> " + sAttackNext + " 기본 피해 ";

}

void Compromise::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerInfo_->addProjectile_ += 1;
	PlayerInfo_->atk_ -= 0.35f;
}