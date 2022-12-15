#include "PreCompile.h"
#include "DashCooldown.h"
#include "Player.h"

DashCooldown::DashCooldown() 
{
	name_ = "�뽬 ��Ÿ�� ����";
	SetName(std::string_view("DashCoolDown"));
	myRank_ = Rank::Rare;
	maxLevel_ = 3;
}

DashCooldown::~DashCooldown() 
{
}

void DashCooldown::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sDashReChargeTime = std::to_string(PlayerInfo_.dashReChargeTime_).substr(0, std::to_string(PlayerInfo_.dashReChargeTime_).find(".") +3 );
	std::string sDashReChargeTimeNext = std::to_string(PlayerInfo_.dashReChargeTime_ * 0.8).substr(0, std::to_string(PlayerInfo_.dashReChargeTime_ * 0.8).find(".") + 3);



	etc_ = sDashReChargeTime + " -> " + sDashReChargeTimeNext + " �뽬\n ������ �ð� ";
}

void DashCooldown::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->dashReChargeTime_ *= 0.80f;
	
}