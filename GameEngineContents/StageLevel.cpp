#include"PreCompile.h"
#include"StageLevel.h"
#include "SoulCardSelectBox.h"
#include "Mouse.h"

StageLevel::StageLevel()
	:PlayerRenderer()
{

}
StageLevel::~StageLevel()
{

}
void StageLevel::Start()
{

////////////���ҽ�//////////
//GameEngineDirectory Dir;
//Dir.MoveParentToExistChildDirectory("ContentsResources");
//Dir.MoveToChild("ContentsResources");
//Dir.MoveToChild("Player");
//std::vector<GameEngineFile> Textures = Dir.GetAllFiles();
//for (size_t i = 0; i < Textures.size(); i++)
//{
//	GameEngineTexture::Load(Textures[i].GetFullPath());
//}
////////////Cut//////////
//GameEngineTexture::Cut("Player_Idle.png", 11, 1);

	CreateActor<SoulCardSelectBox>();
	CreateActor<Mouse>();
}
void StageLevel::Update(float _deltaTime)
{

}
void StageLevel::End()
{

}
void StageLevel::LevelStartEvent()
{

}