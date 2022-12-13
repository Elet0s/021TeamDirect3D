#include "PreCompile.h"
#include "Celerity.h"
#include "Player.h"

Celerity::Celerity() 
{
	name_ = "가속";
	SetName(std::string_view("Celerity"));
	myRank_ = Rank::Rare;
	maxLevel_ = 4;
}

Celerity::~Celerity() 
{
}

void Celerity::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().get()->GetPlayerPassiveInfo();

	float AttackSpeed = PlayerPInfo_.attackSpeed_Per * PlayerPInfo_.attackSpeed_ ;

	std::string sAttackSpeed = std::to_string(AttackSpeed).substr(0, std::to_string(AttackSpeed).find(".")) + "%";
	std::string sAttackSpeedNext = std::to_string(AttackSpeed * 1.08f).substr(0, std::to_string(AttackSpeed * 1.08f).find(".")) + "%";


	etc_ = sAttackSpeed + " -> " + sAttackSpeedNext + " 공격 속도 ";
}

void Celerity::Effect()
{
	currentlevel_ += 1;
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().get()->GetPlayerPassiveInfo();
	PlayerPInfo_->attackSpeed_ *= 1.08f;
}