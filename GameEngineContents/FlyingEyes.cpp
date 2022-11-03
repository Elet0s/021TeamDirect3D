#include"PreCompile.h"
#include"FlyingEyes.h"
#include "GlobalContentsValue.h"
FlyingEyes::FlyingEyes()
{

}
FlyingEyes::~FlyingEyes()
{

}
void FlyingEyes::Start()
{
	if (nullptr == GameEngineTexture::Find("flyingEyes.png"))
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
	}
		///////////////텍스처로드///////////////

		GameEngineTexture::Cut("flyingEyes.png", 6, 1);
		///////////////텍스처 cut///////////////
	

	MonRenderer_ = CreateComponent<GameEngineTextureRenderer>();

	MonRenderer_->GetTransform().SetLocalScale(100, 100, 100);
	MonRenderer_->GetTransform().SetLocalPosition(0, 0, -100);
	MonRenderer_->CreateFrameAnimation_CutTexture("flyingEyes", FrameAnimation_Desc("flyingEyes.png", 0, 5, 0.1f));
	MonRenderer_->ChangeFrameAnimation("flyingEyes");

	MonCollision_ = CreateComponent<GameEngineCollision>();
	MonCollision_->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
	MonCollision_->ChangeOrder(ObjectOrder::Monster);
	SummonMon();

}
void FlyingEyes::Update(float _deltaTime)
{
	Chaseplayer(_deltaTime);
}
void FlyingEyes::End()
{

}