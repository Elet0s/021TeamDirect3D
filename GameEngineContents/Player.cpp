#include "PreCompile.h"
#include "Player.h"
#include "GlobalContentsValue.h"
#include "GameEngineCore/GameEngineCollision.h"

Player* Player::mainplayer_ = nullptr;

Player::Player()
	: playerrenderer_(nullptr)
	,speed_(200.0f)
{
	mainplayer_ = this;
	//SetLevelOverOn();
}

Player::~Player()
{
}

void Player::Start()
{
	
		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("Player");
		
		std::vector<GameEngineFile> Shaders = Dir.GetAllFiles();
		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());

		}
		///////////////텍스처로드///////////////

		GameEngineTexture::Cut("PlayerIdle.png", 11, 1);
		GameEngineTexture::Cut("PlayerRun.png", 10, 1);
		///////////////텍스처 cut///////////////
		if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
		{
			GameEngineInput::GetInst()->CreateKey("PlayerLeft", VK_LEFT);
			GameEngineInput::GetInst()->CreateKey("PlayerRight", VK_RIGHT);
			GameEngineInput::GetInst()->CreateKey("PlayerUp", VK_UP);
			GameEngineInput::GetInst()->CreateKey("PlayerDown", VK_DOWN);
		}
		{
			collision_ = CreateComponent<GameEngineCollision>();
			collision_->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
			collision_->ChangeOrder(ObjectOrder::Player);
		}

		playerrenderer_ = CreateComponent<GameEngineTextureRenderer>();
		playerrenderer_->GetTransform().SetLocalScale(100, 100, 100);
		playerrenderer_->GetTransform().SetLocalPosition(0,0,-100);
		playerrenderer_->CreateFrameAnimation_CutTexture("PlayerIdle", FrameAnimation_Desc("PlayerIdle.png", 0, 10, 0.2f));
		playerrenderer_->CreateFrameAnimation_CutTexture("PlayerRun", FrameAnimation_Desc("PlayerRun.png", 0, 9, 0.2f));
		//playerrenderer_->ChangeFrameAnimation("PlayerIdle");
		
		{
			statemanager_.CreateState("Idle"
				, std::bind(&Player::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
				, std::bind(&Player::IdleStart, this, std::placeholders::_1)
			);

			statemanager_.CreateState("Move"
				, std::bind(&Player::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
				, [/*&*/=](const StateInfo& _Info)
				{
					playerrenderer_->ChangeFrameAnimation("PlayerRun");
				});
			statemanager_.ChangeState("Idle");
		}

}

void Player::IdleStart(const StateInfo& _Info)
{
	playerrenderer_->ChangeFrameAnimation("PlayerIdle");
}

void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (true == GameEngineInput::GetInst()->IsPressed("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPressed("PlayerRight") ||
		true == GameEngineInput::GetInst()->IsPressed("PlayerUp") ||
		true == GameEngineInput::GetInst()->IsPressed("PlayerDown"))
	{
		statemanager_.ChangeState("Move");
	}
}

void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsPressed("PlayerLeft") &&
		false == GameEngineInput::GetInst()->IsPressed("PlayerRight") &&
		false == GameEngineInput::GetInst()->IsPressed("PlayerUp") &&
		false == GameEngineInput::GetInst()->IsPressed("PlayerDown"))
	{
		statemanager_.ChangeState("Idle");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPressed("PlayerLeft"))
	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * speed_ * _DeltaTime);
		playerrenderer_->GetTransform().PixLocalNegativeX();
	}

	if (true == GameEngineInput::GetInst()->IsPressed("PlayerRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * speed_ * _DeltaTime);
		playerrenderer_->GetTransform().PixLocalPositiveX();
	}
	if (true == GameEngineInput::GetInst()->IsPressed("PlayerUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * speed_ * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressed("PlayerDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * speed_ * _DeltaTime);
	}
}

void Player::Update(float _deltaTime)
{
	statemanager_.Update(_deltaTime);

	if (false == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		GetLevel()->GetMainCameraActor()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, -100);
	}
}

void Player::End()
{
}

void Player::SetLevel(GameEngineLevel* _NowLevel)
{
	nowlevel_ = _NowLevel;
}