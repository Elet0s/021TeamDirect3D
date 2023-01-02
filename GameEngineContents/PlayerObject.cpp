#include "PreCompile.h"
#include "GlobalContentsValue.h"
#include "PlayerObject.h"

PlayerObject::PlayerObject() 
{
}

PlayerObject::~PlayerObject() 
{
}

void PlayerObject::Start()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistChildDirectory("ContentsResources");
	Dir.MoveToChild("ContentsResources");
	Dir.MoveToChild("Actor");
	Dir.MoveToChild("Player");

	std::vector<GameEngineFile> playerTexture = Dir.GetAllFiles();
	for (size_t i = 0; i < playerTexture.size(); i++)
	{
		GameEngineTexture::Load(playerTexture[i].GetFullPath());
	}
	///////////////텍스처로드///////////////

	GameEngineTexture::Cut("PlayerIdle.png", 11, 1);
	GameEngineTexture::Cut("PlayerRun.png", 10, 1);

	col_ = CreateComponent<GameEngineCollision>();
	col_->SetDebugSetting(CollisionType::CT_OBB, float4::Red);
	col_->GetTransform().SetLocalScale({ 70.f, 70.f, 100.0f });
	col_->GetTransform().SetLocalPosition({ 0.f, 45.f, 0.0f });
	col_->ChangeOrder(ObjectOrder::Player);
	

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
	if (mode_ == PlayerObjectMode::Move)
	{
		GetTransform().SetLocalMove(moveDir_.Normalize3D() * 100.f * _deltaTime);

		if (true == GetTransform().GetWorldPosition().IY() >= checkPos_.IY())
		{
			mode_ = PlayerObjectMode::Idle;
			renderer_->ChangeFrameAnimation("PlayerIdle");
			GEngine::ChangeLevel("Test");
		}
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
	checkPos_ = _dir + GetTransform().GetWorldPosition();
	mode_ = PlayerObjectMode::Move;
	renderer_->ChangeFrameAnimation("PlayerRun");
}
