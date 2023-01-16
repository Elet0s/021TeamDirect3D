#include "PreCompile.h"
#include "SingleHanded.h"
#include "Player.h"
SingleHanded::SingleHanded() 
{
	name_ = "한손잡이";
	SetName(std::string_view("SingleHanded"));
	myRank_ = Rank::Epic;
	maxLevel_ = 1;
}

SingleHanded::~SingleHanded() 
{
}

void SingleHanded::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();

	std::string sAddProjectile = std::to_string(PlayerInfo_.addProjectile_).substr(0, std::to_string(PlayerInfo_.addProjectile_).find("."));
	std::string sAtkMul = std::to_string(PlayerPInfo_.atkMultiple_Result).substr(0, std::to_string(PlayerPInfo_.atkMultiple_Result).find("."));
	std::string sAddProjectileNext = std::to_string(PlayerInfo_.addProjectile_ - 1).substr(0, std::to_string(PlayerInfo_.addProjectile_ - 1).find("."));
	std::string sAtkMulNext = std::to_string((PlayerPInfo_.atkMultiple_Result * 1.5f)).substr(0, std::to_string((PlayerPInfo_.atkMultiple_Result * 1.5f)).find("."));

	etc_ = sAtkMul + "% -> " + sAtkMulNext + "% 피해 배수\n"
		+ sAddProjectile + " ->" + sAddProjectileNext + " 추가 투사체 ";
}

void SingleHanded::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().GetPlayerPassiveInfo();
	PlayerInfo_->addProjectile_ -= 1;
	
	PlayerPInfo_->atkMultiple_ *= 1.5f;
	PlayerPInfo_->atkMultiple_Result *= 1.5f;
	PlayerPInfo_->atkMultiple_Result = ceil(PlayerPInfo_->atkMultiple_Result);
}