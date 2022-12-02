#include "PreCompile.h"
#include "Cardio.h"
#include "Player.h"


Cardio::Cardio() 
{
	SetName(std::string_view("����� �"));
	maxLevel_ = 999;
}

Cardio::~Cardio() 
{
}

void Cardio::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sAttackSpeed = std::to_string(PlayerInfo_.speed_).substr(0, std::to_string(PlayerInfo_.speed_).find(".") + 3);

	if (level_ == 0)
	{
		etc_ = sAttackSpeed + "���� �ӵ�";
	}
	else
	{
		std::string sDamegeNext = std::to_string(PlayerInfo_.speed_ + 0.01f).substr(0, std::to_string(PlayerInfo_.speed_ + 0.01f).find(".") + 3);
		etc_ = sAttackSpeed + "-> " + sDamegeNext + "���� �ӵ�";
	}
}

void Cardio::Effect()
{
	level_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->speed_ = round(PlayerInfo_->speed_ * 10) / 10;
	PlayerInfo_->speed_ += 0.01f;

}