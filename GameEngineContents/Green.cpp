#include"PreCompile.h"
#include"Green.h"
#include "GlobalContentsValue.h"
#include "Texture2DShadowRenderer.h"

Green::Green()
{

}
Green::~Green()
{

}
void Green::Start()
{
	////////////Load////////////
	if (nullptr == GameEngineTexture::Find("BlackEyes.png"))
	{
		Monster::Start();
	}
	////////////Cut////////////
	GameEngineTexture::Cut("Green.png", 8, 1);



	monRenderer_ = CreateComponent<GameEngineTextureRenderer>();

	monRenderer_->GetTransform().SetLocalScale(100, 100, 100);
	monRenderer_->GetTransform().SetLocalPosition(0, 0, -100);
	monRenderer_->CreateFrameAnimation_CutTexture("Green", FrameAnimation_Desc("Green.png", 0, 7, 0.1f));
	monRenderer_->ChangeFrameAnimation("Green");

	shadowRenderer_ = CreateComponent<Texture2DShadowRenderer>();
	shadowRenderer_->SetTextureRenderer(monRenderer_);

	monCollision_ = CreateComponent<GameEngineCollision>();
	monCollision_->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
	monCollision_->ChangeOrder(ObjectOrder::Monster);
	SummonMon();

}
void Green::Update(float _deltaTime)
{
	Chaseplayer(_deltaTime);
}
void Green::End()
{

}