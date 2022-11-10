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
	////////////Load////////////
	if (nullptr == GameEngineTexture::Find("BlackEyes.png"))
	{
		Monster::Start();
	}
	////////////Cut////////////

		GameEngineTexture::Cut("Brown.png", 8, 1);
	
		monRenderer_ = CreateComponent<GameEngineTextureRenderer>();

		monRenderer_->GetTransform().SetLocalScale(100, 100, 100);
		monRenderer_->GetTransform().SetLocalPosition(0, 0, -100);
		monRenderer_->CreateFrameAnimation_CutTexture("Brown", FrameAnimation_Desc("Brown.png", 0, 7, 0.1f));
		monRenderer_->ChangeFrameAnimation("Brown");

		monCollision_ = CreateComponent<GameEngineCollision>();
		monCollision_->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
		monCollision_->ChangeOrder(ObjectOrder::Monster);
	SummonMon();

}
void Brown::Update(float _deltaTime)
{
	Chaseplayer(_deltaTime);
}
void Brown::End()
{

}