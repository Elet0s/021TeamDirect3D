#include"PreCompile.h"
#include"TitleLevel.h"
#include "Enums.h"
TitleLevel::TitleLevel()
{

}
TitleLevel::~TitleLevel()
{

}
void TitleLevel::Start()
{
}
void TitleLevel::Update(float _deltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChangeKey"))
	{
		GEngine::ChangeLevel("WorldMap");
	}
}
void TitleLevel::End()
{

}
void TitleLevel::LevelStartEvent()
{

}