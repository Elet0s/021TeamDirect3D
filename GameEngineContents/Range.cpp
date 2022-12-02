#include "PreCompile.h"
#include "Range.h"
#include "Player.h"

Range::Range() 
{
	SetName(std::string_view("�����Ÿ�"));
	maxLevel_ = 6;
}

Range::~Range() 
{
}

void Range::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sAttackSpeed = std::to_string(PlayerInfo_.speed_).substr(0, std::to_string(PlayerInfo_.speed_).find(".") ) + "%";

	if (level_ == 0)
	{
		etc_ = sAttackSpeed + "����ü ���� �ð�";
	}
	else
	{
		std::string sDamegeNext = std::to_string(PlayerInfo_.speed_ + 20).substr(0, std::to_string(PlayerInfo_.speed_ + 20).find(".") ) + "%";
		etc_ = sAttackSpeed + "-> " + sDamegeNext + "����ü\n ���� �ð� ";
	}
}

void Range::Effect()
{
	level_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->speed_ = round(PlayerInfo_->speed_ * 10) / 10;
	PlayerInfo_->speed_ += 20;

}