#include"PreCompile.h"
#include"Green.h"
#include "GlobalContentsValue.h"
Green::Green()
{

}
Green::~Green()
{

}
void Green::Start()
{
	if (nullptr == GameEngineTexture::Find("Green.png"))
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

		GameEngineTexture::Cut("Green.png", 8, 1);
		///////////////텍스처 cut///////////////
	

		MonRenderer_ = CreateComponent<GameEngineTextureRenderer>();

		MonRenderer_->GetTransform().SetLocalScale(100, 100, 100);
		MonRenderer_->GetTransform().SetLocalPosition(0, 0, -100);
		MonRenderer_->CreateFrameAnimation_CutTexture("Green", FrameAnimation_Desc("Green.png", 0, 7, 0.1f));
		MonRenderer_->ChangeFrameAnimation("Green");

		MonCollision_ = CreateComponent<GameEngineCollision>();
		MonCollision_->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
		MonCollision_->ChangeOrder(ObjectOrder::Monster);
	SummonMon();

}
void Green::Update(float _deltaTime)
{
	Chaseplayer(_deltaTime);
}
void Green::End()
{

}