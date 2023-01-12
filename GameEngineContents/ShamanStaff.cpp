#include"PreCompile.h"
#include"ShamanStaff.h"

ShamanStaff::ShamanStaff()
{
	name_ = "주술 지팡이";
	SetName(std::string_view("ShamanStaff"));
	myRank_ = Rank::Epic;
	maxLevel_ = 7;
}
ShamanStaff::~ShamanStaff()
{

}
void ShamanStaff::Init()
{

}
void ShamanStaff::Effect()
{
	currentlevel_ += 1;
}
void ShamanStaff::Start()
{

}
void ShamanStaff::Update(float _deltaTime)
{

}
void ShamanStaff::End()
{

}