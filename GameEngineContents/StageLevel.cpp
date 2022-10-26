#include"PreCompile.h"
#include"StageLevel.h"

StageLevel::StageLevel()
	:PlayerRenderer()
{

}
StageLevel::~StageLevel()
{

}
void StageLevel::Start()
{

	////////////¸®¼Ò½º//////////
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