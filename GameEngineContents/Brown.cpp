#include"PreCompile.h"
#include"Brown.h"
#include "GlobalContentsValue.h"

Brown::Brown()
{

}
Brown::~Brown()
{

}
void Brown::Start()
{
	if (nullptr == GameEngineTexture::Find("Brown.png"))
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

		GameEngineTexture::Cut("Brown.png", 8, 1);
		///////////////텍스처 cut///////////////
	

		MonRenderer_ = CreateComponent<GameEngineTextureRenderer>();

		MonRenderer_->GetTransform().SetLocalScale(100, 100, 100);
		MonRenderer_->GetTransform().SetLocalPosition(0, 0, -100);
		MonRenderer_->CreateFrameAnimation_CutTexture("Brown", FrameAnimation_Desc("Brown.png", 0, 7, 0.1f));
		MonRenderer_->ChangeFrameAnimation("Brown");

		MonCollision_ = CreateComponent<GameEngineCollision>();
		MonCollision_->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
		MonCollision_->ChangeOrder(ObjectOrder::Monster);
	SummonMon();

}
void Brown::Update(float _deltaTime)
{
	Chaseplayer(_deltaTime);
}
void Brown::End()
{

}