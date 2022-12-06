#include "PreCompile.h"
#include "LightHand.h"
#include "Player.h"

LightHand::LightHand() 
{
	name_ = "������ ��";
	SetName(std::string_view("LightHand"));
	myRank_ = Rank::Epic;
	maxLevel_ = 1;
}

LightHand::~LightHand() 
{
}

void LightHand::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().get()->GetPlayerInfo();

	std::string sAttackSpeed = std::to_string(PlayerInfo_.attackSpeed_).substr(0, std::to_string(PlayerInfo_.attackSpeed_).find(".")) + "%";
	std::string sAttackSpeedNext = std::to_string(PlayerInfo_.attackSpeed_ * 1.33f).substr(0, std::to_string(PlayerInfo_.attackSpeed_ * 1.33f).find(".")) + "%";
	std::string sAttackMul = std::to_string(PlayerInfo_.atkMultiple_).substr(0, std::to_string(PlayerInfo_.atkMultiple_).find(".") + 3) + "%";
	std::string sAttackMulNext = std::to_string(PlayerInfo_.atkMultiple_ * 0.8f).substr(0, std::to_string(PlayerInfo_.atkMultiple_ * 0.8f).find(".") + 3) + "%";

	etc_ = sAttackSpeed + " -> " + sAttackSpeedNext + " ���ݼӵ�\n"
		+ sAttackMul + " -> " + sAttackMulNext + " ����\n��� ";
}

void LightHand::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().get()->GetPlayerInfo();
	PlayerInfo_->attackSpeed_ *= 1.33f;
	PlayerInfo_->atkMultiple_ *= 0.8f;
}