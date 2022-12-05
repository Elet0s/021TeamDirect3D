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

	std::string sAttackSpeed = std::to_string(PlayerInfo_.attackSpeed_).substr(0, std::to_string(PlayerInfo_.attackSpeed_).find(".")) + "%";
	std::string sDamegeNext = std::to_string(PlayerInfo_.attackSpeed_ + 1.0f).substr(0, std::to_string(PlayerInfo_.attackSpeed_ + 1.0f).find(".")) + "%";
	
	etc_ = sAttackSpeed + " -> " + sDamegeNext + " ���� �ӵ�";
	
}

void Cardio::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->attackSpeed_ += 1.0f;

}