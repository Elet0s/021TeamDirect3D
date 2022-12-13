#include "PreCompile.h"
#include "Cardio.h"
#include "Player.h"


Cardio::Cardio() 
{
	name_ = "����ҿ";
	SetName(std::string_view("Cardio"));
	maxLevel_ = 999;
	myRank_ = Rank::Spotted;
}

Cardio::~Cardio() 
{
}

void Cardio::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().get()->GetPlayerPassiveInfo();

	float AttackSpeed = PlayerPInfo_.attackSpeed_Per * PlayerPInfo_.attackSpeed_ / 100;

	std::string sAttackSpeed = std::to_string(AttackSpeed).substr(0, std::to_string(AttackSpeed).find(".")) + "%";
	std::string sDamegeNext = std::to_string(AttackSpeed + 1.01f).substr(0, std::to_string(AttackSpeed + 1.01f).find(".")) + "%";
	
	etc_ = sAttackSpeed + " -> " + sDamegeNext + " ���� �ӵ�";
	
}

void Cardio::Effect()
{
	currentlevel_ += 1;
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().get()->GetPlayerPassiveInfo();
	PlayerPInfo_->attackSpeed_ *= 1.01f;

}