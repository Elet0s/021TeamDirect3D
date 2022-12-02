#include "PreCompile.h"
#include "SharpEdge.h"
#include "Player.h"

SharpEdge::SharpEdge() 
{
	SetName(std::string_view("��ī�ο� Į��"));
	maxLevel_ = 6;
}

SharpEdge::~SharpEdge() 
{
}

void SharpEdge::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sDamege = std::to_string(PlayerInfo_.atk_).substr(0, std::to_string(PlayerInfo_.atk_).find(".") + 3);

	if (level_ == 0)
	{
		etc_ = sDamege + "�⺻ ����";
	}
	else
	{
		std::string sDamegeNext = std::to_string(PlayerInfo_.atk_ + 0.25f).substr(0, std::to_string(PlayerInfo_.atk_ + 0.25f).find(".") + 3);
		etc_ = sDamege + "-> " + sDamegeNext + "�⺻ ����";
	}
}

void SharpEdge::Effect()
{
	level_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->atk_ = floor(PlayerInfo_->atk_ * 100) / 100;
	PlayerInfo_->atk_ += 0.25f;

}