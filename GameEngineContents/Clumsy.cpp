#include "PreCompile.h"
#include "Clumsy.h"
#include "Player.h"

Clumsy::Clumsy() 
{
	name_ = "어설픔";
	SetName(std::string_view("Clumsy"));
	myRank_ = Rank::UnCommon;
	maxLevel_ = 1;
}

Clumsy::~Clumsy() 
{
}

void Clumsy::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();

	std::string sAddProjectile = std::to_string(PlayerInfo_.addProjectile_).substr(0, std::to_string(PlayerInfo_.addProjectile_).find("."));
	std::string sDef = std::to_string(ceil(PlayerInfo_.def_ * PlayerPInfo_.defMul_Result/100)).substr(0, std::to_string(ceil(PlayerInfo_.def_ * PlayerPInfo_.defMul_Result / 100)).find("."));
	std::string sAddProjectileNext = std::to_string(PlayerInfo_.addProjectile_ + 1.0f).substr(0, std::to_string(PlayerInfo_.addProjectile_ + 1.0f).find("."));
	std::string sDefNext = std::to_string(ceil(PlayerInfo_.def_ * PlayerPInfo_.defMul_Result / 100) - 2.f).substr(0, std::to_string(ceil(PlayerInfo_.def_ * PlayerPInfo_.defMul_Result / 100) - 2.0f).find("."));


	etc_ = sAddProjectile + " -> " + sAddProjectileNext + " 추가 투사체 \n"
		+ sDef + " -> " + sDefNext + " 방어력 ";

}

void Clumsy::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerInfo_->addProjectile_ += 1;
	PlayerInfo_->def_ -= 2.0f;

}