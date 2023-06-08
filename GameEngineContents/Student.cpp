#include "PreCompile.h"
#include "Student.h"
#include "Player.h"

Student::Student() 
{
	name_ = "�л�";
	SetName(std::string_view("Student"));
	myRank_ = Rank::Normal;
	maxLevel_ = 3;
}

Student::~Student() 
{
}

void Student::Init()
{
	PlayerInfo PlayerInfo_ = Player::GetPlayerInst().GetPlayerInfo();

	std::string sExpMul = std::to_string(PlayerInfo_.expMultiple_).substr(0, std::to_string(PlayerInfo_.expMultiple_).find(".") + 2);
	std::string sExpMulNext = std::to_string(PlayerInfo_.expMultiple_ + 10.f).substr(0, std::to_string(PlayerInfo_.expMultiple_ + 10.f).find(".") + 2);



	etc_ = sExpMul + "% -> " + sExpMulNext + "% ����ġ\n��� ";
}

void Student::Effect()
{
	currentlevel_ += 1;
	PlayerInfo* PlayerInfo_ = &Player::GetPlayerInst().GetPlayerInfo();
	PlayerInfo_->expMultiple_ += 10.f;

}