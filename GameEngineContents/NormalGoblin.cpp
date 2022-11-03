#include"PreCompile.h"
#include"NormalGoblin.h"
#include "GlobalContentsValue.h"
NormalGoblin::NormalGoblin()
{

}
NormalGoblin::~NormalGoblin()
{

}
void NormalGoblin::Start()
{
	if (nullptr == GameEngineTexture::Find("NormalGoblin.png"))
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

		GameEngineTexture::Cut("NormalGoblin.png", 8, 1);
		///////////////텍스처 cut///////////////
	

		MonRenderer_ = CreateComponent<GameEngineTextureRenderer>();

		MonRenderer_->GetTransform().SetLocalScale(100, 100, 100);
		MonRenderer_->GetTransform().SetLocalPosition(0, 0, -100);
		MonRenderer_->CreateFrameAnimation_CutTexture("NormalGoblin", FrameAnimation_Desc("NormalGoblin.png", 0, 7, 0.1f));
		MonRenderer_->ChangeFrameAnimation("NormalGoblin");

		MonCollision_ = CreateComponent<GameEngineCollision>();
		MonCollision_->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
		MonCollision_->ChangeOrder(ObjectOrder::Monster);
	SummonMon();

}
void NormalGoblin::Update(float _deltaTime)
{
	Chaseplayer(_deltaTime);
}
void NormalGoblin::End()
{

}