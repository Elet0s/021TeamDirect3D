#include "PreCompile.h"
#include "SlipperySkin.h"
#include "Player.h"

SlipperySkin::SlipperySkin() 
{
	name_ = "�̲����� �Ǻ�";
	SetName(std::string_view("SlipperySkin"));
	myRank_ = Rank::UnCommon;
	maxLevel_ = 3;
}

SlipperySkin::~SlipperySkin() 
{
}


void SlipperySkin::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sdamageMitigation_ = std::to_string(PlayerInfo_.damageMitigation_).substr(0, std::to_string(PlayerInfo_.damageMitigation_).find(".") + 2);
	std::string sdamageMitigation_Next = std::to_string(PlayerInfo_.damageMitigation_ + 10.f).substr(0, std::to_string(PlayerInfo_.damageMitigation_ + 10.f).find(".") + 2);

	etc_ = sdamageMitigation_ + "% -> " + sdamageMitigation_Next + "% ����\n��ȭ ";
}

void SlipperySkin::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->damageMitigation_ += 10.f;
}