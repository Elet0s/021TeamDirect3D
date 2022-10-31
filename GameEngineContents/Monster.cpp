#include "PreCompile.h"
#include "Monster.h"
#include "GlobalContentsValue.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
	if (nullptr == GameEngineTexture::Find("BlackEyes.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("Monster");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFiles();
		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());

		}
		///////////////텍스처로드///////////////

		GameEngineTexture::Cut("BlackEyes.png", 6, 1);
	}
	///////////////텍스처 cut///////////////
	

	monsterrenderer_ = CreateComponent<GameEngineTextureRenderer>();
	
	monsterrenderer_->GetTransform().SetLocalScale(100, 100, 100);
	monsterrenderer_->GetTransform().SetLocalPosition((GameEngineRandom::mainRandom_.RandomInt(1, 1280)), -(GameEngineRandom::mainRandom_.RandomInt(1,640)), -100);
	monsterrenderer_->CreateFrameAnimation_CutTexture("BlackEyes", FrameAnimation_Desc("BlackEyes.png", 0, 5, 0.2f));
	monsterrenderer_->ChangeFrameAnimation("BlackEyes");

}

void Monster::Update(float _deltaTime)
{
}

void Monster::End()
{
}
