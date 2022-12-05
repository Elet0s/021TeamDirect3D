#include "PreCompile.h"
#include "Clumsy.h"
#include "Player.h"

Clumsy::Clumsy() 
{
	name_ = "���";
	SetName(std::string_view("Clumsy"));
	myRank_ = Rank::UnCommon;
	maxLevel_ = 1;
}

Clumsy::~Clumsy() 
{
}

void Clumsy::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sAddProjectile = std::to_string(PlayerInfo_.addProjectile_).substr(0, std::to_string(PlayerInfo_.addProjectile_).find("."));
	std::string sDef = std::to_string(PlayerInfo_.def_).substr(0, std::to_string(PlayerInfo_.def_).find("."));
	std::string sAddProjectileNext = std::to_string(PlayerInfo_.addProjectile_ + 1.0f).substr(0, std::to_string(PlayerInfo_.addProjectile_ + 1.0f).find("."));
	std::string sDefNext = std::to_string(PlayerInfo_.def_ - 2.f).substr(0, std::to_string(PlayerInfo_.def_ - 2.0f).find("."));


	etc_ = sAddProjectile + " -> " + sAddProjectileNext + " �߰� ����ü \n"
		+ sDef + " -> " + sDefNext + "���� ";

}

void Clumsy::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->addProjectile_ += 1.0f;
	PlayerInfo_->def_ -= 2.0f;

}