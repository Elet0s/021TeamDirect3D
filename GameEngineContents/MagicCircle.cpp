#include "PreCompile.h"
#include"MagicCircle.h"
#include"GlobalContentsValue.h"

MagicCircle::MagicCircle()
	:magicCircle01_(),
	magicCircle02_(),
	magicCircle03_(),
	timer_(0)
{

}
MagicCircle::~MagicCircle()
{

}
void MagicCircle::Start()
{
	magicCircle01_ = CreateComponent<GameEngineTextureRenderer>();
	magicCircle01_->SetTexture("MagicCircle1.png");
	magicCircle01_->GetTransform().SetWorldScale(150, 150, 0);
	magicCircle01_->GetPixelData().mulColor_ = float4(1.f, 1.f, 1.f, 0.5f);
	magicCircle01_->ChangeCamera(CameraOrder::MidCamera);
	magicCircle01_->Off();

	magicCircle02_ = CreateComponent<GameEngineTextureRenderer>();
	magicCircle02_->SetTexture("MagicCircle2.png");
	magicCircle02_->GetTransform().SetWorldScale(150, 150, 0);
	magicCircle02_->GetTransform().SetWorldPosition(0.f, 0.f, -1.f);
	magicCircle02_->GetPixelData().mulColor_ = float4(1.f, 1.f, 1.f, 0.5f);
	magicCircle02_->ChangeCamera(CameraOrder::MidCamera);
	magicCircle02_->Off();

	magicCircle03_ = CreateComponent<GameEngineTextureRenderer>();
	magicCircle03_->SetTexture("MagicCircle3.png");
	magicCircle03_->GetTransform().SetWorldScale(150, 150, 0);
	magicCircle03_->GetTransform().SetWorldPosition(0.f, 0.f, -2.f);
	magicCircle03_->GetPixelData().mulColor_ = float4(1.f, 1.f, 1.f, 0.5f);
	magicCircle03_->ChangeCamera(CameraOrder::MidCamera);
	magicCircle03_->Off();
}
void MagicCircle::Update(float _deltaTime)
{
	RotateRenderer(_deltaTime);
	TimeOff(_deltaTime);
}
void MagicCircle::End()
{

}

void MagicCircle::TimeOff(float _deltaTime)
{

		if (timer_ < 3.f)
		{
			timer_ += _deltaTime;
		}
		else
		{
			Death();
		}
}
void MagicCircle::RotateRenderer(float _deltaTime)
{

	if (addRadian_ < 360)
	{
		addRadian_ += 10 * _deltaTime;
	}
	else
	{
		addRadian_ = 0;
	}

	magicCircle01_->GetTransform().SetWorldRotation(60, 0, addRadian_);
	magicCircle02_->GetTransform().SetWorldRotation(60, 0, -addRadian_);
	magicCircle03_->GetTransform().SetWorldRotation(60, 0, addRadian_);

	if (magicCircle01_->IsUpdate() == false)
	{
		magicCircle01_->On();
		magicCircle02_->On();
		magicCircle03_->On();
	}
}