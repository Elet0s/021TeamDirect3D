#include"PreCompile.h"
#include"RedFlyingEyes.h"
#include "GlobalContentsValue.h"
RedFlyingEyes::RedFlyingEyes()
{

}
RedFlyingEyes::~RedFlyingEyes()
{

}
void RedFlyingEyes::Start()
{
	if (nullptr == GameEngineTexture::Find("RedFlyingEyes.png"))
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

		GameEngineTexture::Cut("RedFlyingEyes.png", 6, 1);
		///////////////텍스처 cut///////////////
	

		MonRenderer_ = CreateComponent<GameEngineTextureRenderer>();

		MonRenderer_->GetTransform().SetLocalScale(100, 100, 100);
		MonRenderer_->GetTransform().SetLocalPosition(0, 0, -100);
		MonRenderer_->CreateFrameAnimation_CutTexture("RedFlyingEyes", FrameAnimation_Desc("RedFlyingEyes.png", 0, 5, 0.1f));
		MonRenderer_->ChangeFrameAnimation("RedFlyingEyes");

		MonCollision_ = CreateComponent<GameEngineCollision>();
		MonCollision_->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
		MonCollision_->ChangeOrder(ObjectOrder::Monster);
	SummonMon();

}
void RedFlyingEyes::Update(float _deltaTime)
{
	Chaseplayer(_deltaTime);
}
void RedFlyingEyes::End()
{

}