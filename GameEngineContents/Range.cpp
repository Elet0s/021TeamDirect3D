#include "PreCompile.h"
#include "Range.h"
#include "Player.h"

Range::Range() 
{
	name_ = "�����Ÿ�";
	SetName(std::string_view("Range"));
	maxLevel_ = 6;
	myRank_ = Rank::Normal;
}

Range::~Range() 
{
}

void Range::Init()
{
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();

	std::string sProjectileDuration = std::to_string(PlayerPInfo_.projectileDuration_Result).substr(0, std::to_string(PlayerPInfo_.projectileDuration_Result).find(".") ) + "%";
	std::string sProjectileDurationNext = std::to_string(PlayerPInfo_.projectileDuration_Result + 20).substr(0, std::to_string(PlayerPInfo_.projectileDuration_Result + 20).find(".") ) + "%";
	
	etc_ = sProjectileDuration + "-> " + sProjectileDurationNext + " ����ü\n ���� �ð� ";
}

void Range::Effect()
{
	currentlevel_ += 1;
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().GetPlayerPassiveInfo();
	PlayerPInfo_->projectileDuration_Per += 20.f;
	PlayerPInfo_->projectileDuration_Result += 20.f;

}