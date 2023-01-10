#include "PreCompile.h"
#include "GlobalContentsValue.h"
#include "PlayerObject.h"
#include "Player.h"

PlayerObject::PlayerObject() 
	: mode_(PlayerObjectMode::Idle),
	//col_(nullptr),
	renderer_(nullptr)
{
}

PlayerObject::~PlayerObject() 
{
}

void PlayerObject::Start()
{
	//col_ = CreateComponent<GameEngineCollision>();
	//col_->SetDebugSetting(CollisionType::CT_OBB, float4::Red);
	//col_->GetTransform().SetLocalScale({ 70.f, 70.f, 100.0f });
	//col_->GetTransform().SetLocalPosition({ 0.f, 45.f, 0.0f });
	//col_->ChangeOrder(ObjectOrder::Player);	

	renderer_ = CreateComponent<GameEngineTextureRenderer>();
	renderer_->SetPivot(PivotMode::Bot);
	renderer_->SetRenderingOrder(static_cast<int>(ObjectOrder::Player));
	renderer_->GetTransform().SetLocalScale(90, 90, 0);
	renderer_->CreateFrameAnimation_CutTexture("PlayerIdle", FrameAnimation_Desc("PlayerIdle.png", 0, 10, 0.2f));
	renderer_->CreateFrameAnimation_CutTexture("PlayerRun", FrameAnimation_Desc("PlayerRun.png", 0, 9, 0.2f));
	renderer_->ChangeFrameAnimation("PlayerIdle");
}

void PlayerObject::Update(float _deltaTime)
{
	//float4 PosK = GetTransform().GetWorldPosition();
	//PosK = GetLevel()->GetMainCamera()->ConvertWorldPositionToScreenPosition(PosK);
	//col_->GetTransform().SetWorldPosition(PosK);

	if (mode_ == PlayerObjectMode::Move)
	{
		GetTransform().SetLocalMove(moveDir_.Normalize3D() * 150.f * _deltaTime);

		if (true == GetTransform().GetWorldPosition().IY() >= checkPos_.IY())
		{
			GEngine::ChangeLevel("Test");
			
			Player::GetPlayerInst()->GetPlayerInfo().stage_ += 1;
			
			mode_ = PlayerObjectMode::Idle;
			renderer_->ChangeFrameAnimation("PlayerIdle");
		}
	}
}

void PlayerObject::LevelStartEvent()
{
	if(Player::GetPlayerInst()->GetPlayerInfo().stage_ != 0)
	{
		float4 Pos = GetLevel()->GetMainCameraActorTransform().GetWorldPosition();
		if (GetTransform().GetWorldPosition().x <= 500.f)
		{
			GetLevel()->GetMainCameraActorTransform().SetWorldPosition(500.f, Pos.y, Pos.z);
		}
		else if (GetTransform().GetWorldPosition().x >= 1250.f)
		{
			GetLevel()->GetMainCameraActorTransform().SetWorldPosition(1250.f, Pos.y, Pos.z);
		}
		else
		{
			GetLevel()->GetMainCameraActorTransform().SetWorldPosition(GetTransform().GetWorldPosition().x, Pos.y, Pos.z);
		}
		GetLevel()->GetMainCameraActorTransform().SetWorldMove(float4(0.f, 200.f * sinf(30.f * GameEngineMath::DegreeToRadian), 200.f * cosf(30.f * GameEngineMath::DegreeToRadian)));
	}
}

void PlayerObject::End()
{

}

void PlayerObject::SetMoveDir(float4 _dir)
{
	moveDir_ = _dir;
	if (moveDir_.x < 0.f)
	{
		renderer_->GetTransform().PixLocalNegativeX();
	}
	else
	{
		renderer_->GetTransform().PixLocalPositiveX();
	}
	checkPos_ = _dir + GetTransform().GetWorldPosition();
	mode_ = PlayerObjectMode::Move;
	renderer_->ChangeFrameAnimation("PlayerRun");
}
