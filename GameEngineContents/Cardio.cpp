#include "PreCompile.h"
#include "Cardio.h"
#include "Player.h"


Cardio::Cardio() 
{
	name_ = "����ҿ";
	SetName(std::string_view("Cardio"));
	maxLevel_ = 999;
	myRank_ = Rank::Spotted;
}

Cardio::~Cardio() 
{
}

void Cardio::Init()
{
	PlayerPassiveInfo PlayerPInfo_ = Player::GetPlayerInst().get()->GetPlayerPassiveInfo();


	std::string sAttackSpeed = std::to_string(PlayerPInfo_.attackSpeed_Result).substr(0, std::to_string(PlayerPInfo_.attackSpeed_Result).find(".")) + "%";
	std::string sDamegeNext = std::to_string(ceil(PlayerPInfo_.attackSpeed_Result * 1.01f)).substr(0, std::to_string(ceil(PlayerPInfo_.attackSpeed_Result * 1.01f)).find(".")) + "%";
	
	etc_ = sAttackSpeed + " -> " + sDamegeNext + " ���� �ӵ�";
	
}

void Cardio::Effect()
{
	currentlevel_ += 1;
	PlayerPassiveInfo* PlayerPInfo_ = &Player::GetPlayerInst().get()->GetPlayerPassiveInfo();
	PlayerPInfo_->attackSpeed_ *= 1.01f;
	PlayerPInfo_->attackSpeed_Result *= 1.01f;
	PlayerPInfo_->attackSpeed_Result = ceil(PlayerPInfo_->attackSpeed_Result);

}