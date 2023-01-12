#include "PreCompile.h"
#include "Skill.h"
#include "Player.h"
Skill::Skill()
	: currentlevel_(0)
	, maxLevel_(0)
	, myRank_()
	, valueSoulCard_(SoulCard::None)
	, Shooting(false)
	, isOn_(false)

{
	
}
Skill::~Skill() 
{

}

void Skill::Start()
{
	
}
void Skill::Update(float _deltaTime)
{
}
void Skill::End()
{

}

void  Skill::StateSet()
{

 }