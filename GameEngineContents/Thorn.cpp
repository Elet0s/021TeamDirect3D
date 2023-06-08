#include "PreCompile.h"
#include "Thorn.h"
#include "Player.h"

Thorn::Thorn() 
{
	name_ = "가시";
	SetName(std::string_view("Thorn"));
	myRank_ = Rank::Epic;
	maxLevel_ = 7;
}

Thorn::~Thorn() 
{
}

void Thorn::Init()
{
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();

	std::string sProjectileDuration = std::to_string(PlayerPInfo_.projectileDuration_Result).substr(0, std::to_string(PlayerPInfo_.projectileDuration_Result).find(".")) + "%";
	std::string sProjectileDurationNext = std::to_string(PlayerPInfo_.projectileDuration_Result + 20).substr(0, std::to_string(PlayerPInfo_.projectileDuration_Result + 20).find(".")) + "%";

	etc_ = sProjectileDuration + "-> " + sProjectileDurationNext + " 투사체\n 지속 시간 ";
}

void Thorn::Effect()
{
	currentlevel_ += 1;
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().GetPlayerPassiveInfo();
	PlayerPInfo_->projectileDuration_Per += 20.f;
	PlayerPInfo_->projectileDuration_Result += 20.f;

}