#include"PreCompile.h"
#include"TitleLevel.h"
#include "TitleActor.h"
TitleLevel::TitleLevel()
{

}
TitleLevel::~TitleLevel()
{

}
void TitleLevel::Start()
{
	CreateActor<TitleActor>();
}
void TitleLevel::Update(float _deltaTime)
{
	
}
void TitleLevel::End()
{

}
void TitleLevel::LevelStartEvent()
{

}