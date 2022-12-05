#include "PreCompile.h"
#include "Range.h"
#include "Player.h"

Range::Range() 
{
	name_ = "사정거리";
	SetName(std::string_view("Range"));
	maxLevel_ = 6;
	myRank_ = Rank::Normal;
}

Range::~Range() 
{
}

void Range::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sAttackSpeed = std::to_string(PlayerInfo_.attackSpeed_).substr(0, std::to_string(PlayerInfo_.speed_).find(".") ) + "%";
	std::string sDamegeNext = std::to_string(PlayerInfo_.attackSpeed_ + 20).substr(0, std::to_string(PlayerInfo_.attackSpeed_ + 20).find(".") ) + "%";
	
	etc_ = sAttackSpeed + "-> " + sDamegeNext + " 투사체\n 지속 시간 ";
}

void Range::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	//PlayerInfo_->attackSpeed_ = round(PlayerInfo_->attackSpeed_ * 10) / 10;
	PlayerInfo_->attackSpeed_ += 20;

}