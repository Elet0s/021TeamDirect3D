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
	////////////Load////////////
	if (nullptr == GameEngineTexture::Find("BlackEyes.png"))
	{
		Monster::Start();
		
	}
	////////////Cut////////////
	GameEngineTexture::Cut("flyingEyes.png", 6, 1);
	


	monRenderer_ = CreateComponent<GameEngineTextureRenderer>();

	monRenderer_->GetTransform().SetLocalScale(100, 100, 100);
	monRenderer_->GetTransform().SetLocalPosition(0, 0, -100);
	monRenderer_->CreateFrameAnimation_CutTexture("flyingEyes", FrameAnimation_Desc("flyingEyes.png", 0, 5, 0.1f));
	monRenderer_->ChangeFrameAnimation("flyingEyes");

	monCollision_ = CreateComponent<GameEngineCollision>();
	monCollision_->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
	monCollision_->ChangeOrder(ObjectOrder::Monster);
	SummonMon();

}
void FlyingEyes::Update(float _deltaTime)
{
	Chaseplayer(_deltaTime);
}
void FlyingEyes::End()
{

}