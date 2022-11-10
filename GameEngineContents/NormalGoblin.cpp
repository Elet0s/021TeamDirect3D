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
	////////////Load////////////
	if (nullptr == GameEngineTexture::Find("BlackEyes.png"))
	{
		Monster::Start();
	}
	////////////Cut////////////
	GameEngineTexture::Cut("NormalGoblin.png", 8, 1);





	monRenderer_ = CreateComponent<GameEngineTextureRenderer>();

	monRenderer_->GetTransform().SetLocalScale(100, 100, 100);
	monRenderer_->GetTransform().SetLocalPosition(0, 0, -100);
	monRenderer_->CreateFrameAnimation_CutTexture("NormalGoblin", FrameAnimation_Desc("NormalGoblin.png", 0, 7, 0.1f));
	monRenderer_->ChangeFrameAnimation("NormalGoblin");

	monCollision_ = CreateComponent<GameEngineCollision>();
	monCollision_->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
	monCollision_->ChangeOrder(ObjectOrder::Monster);
	SummonMon();

}
void NormalGoblin::Update(float _deltaTime)
{
	Chaseplayer(_deltaTime);
}
void NormalGoblin::End()
{

}