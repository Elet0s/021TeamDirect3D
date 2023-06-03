#include "PreCompile.h"
#include "Impenetrable.h"
#include "Player.h"

Impenetrable::Impenetrable() 
{
	name_ = "뚫어보시지";
	SetName(std::string_view("Impenetrable"));
	myRank_ = Rank::UnCommon;
	maxLevel_ = 5;
}

Impenetrable::~Impenetrable() 
{
}

void Impenetrable::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().GetPlayerPassiveInfo();

	std::string sDefMul = std::to_string(PlayerPInfo_.defMul_Result).substr(0, std::to_string(PlayerPInfo_.defMul_Result).find("."));
	std::string sDefMulNext = std::to_string(PlayerPInfo_.defMul_Result + 10.f).substr(0, std::to_string(PlayerPInfo_.defMul_Result + 10.f).find("."));
	std::string sdamageMitigation_ = std::to_string(PlayerInfo_.damageMitigation_).substr(0, std::to_string(PlayerInfo_.damageMitigation_).find(".") + 2);
	std::string sdamageMitigation_Next = std::to_string(PlayerInfo_.damageMitigation_ + 5.f).substr(0, std::to_string(PlayerInfo_.damageMitigation_ + 5.f).find(".") + 2);


	etc_ = sDefMul + "% -> " + sDefMulNext + "% 방어력\n"
		+ sdamageMitigation_ + "% -> " + sdamageMitigation_Next + "% 피해\n완화 ";
}

void Impenetrable::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().GetPlayerPassiveInfo();
	PlayerInfo_->damageMitigation_ += 5.f;
	PlayerPInfo_->defMul_Per += 10.f;
	PlayerPInfo_->defMul_Result += 10.f;
}