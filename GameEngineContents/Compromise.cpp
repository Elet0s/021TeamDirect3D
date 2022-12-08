#include "PreCompile.h"
#include "Compromise.h"
#include "Player.h"

Compromise::Compromise() 
{
	name_ = "Ÿ��";
	SetName(std::string_view("Compromise"));
	myRank_ = Rank::Normal;
	maxLevel_ = 1;
}

Compromise::~Compromise() 
{
}

void Compromise::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sAddProjectile = std::to_string(PlayerInfo_.addProjectile_).substr(0, std::to_string(PlayerInfo_.addProjectile_).find("."));
	std::string sAttack = std::to_string(PlayerInfo_.atk_).substr(0, std::to_string(PlayerInfo_.atk_).find(".") + 3);
	std::string sAddProjectileNext = std::to_string(PlayerInfo_.addProjectile_ + 1.0f).substr(0, std::to_string(PlayerInfo_.addProjectile_ + 1.0f).find("."));
	std::string sAttackNext = std::to_string(PlayerInfo_.atk_ -0.35f).substr(0, std::to_string(PlayerInfo_.atk_ -0.35f).find(".") + 3);


	etc_ = sAddProjectile + " -> " + sAddProjectileNext + " �߰� ����ü\n"
		+ sAttack + " -> " + sAttackNext + " �⺻ ���� ";
	
}

void Compromise::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->addProjectile_ += 1;
	PlayerInfo_->atk_ -= 0.35f;
}