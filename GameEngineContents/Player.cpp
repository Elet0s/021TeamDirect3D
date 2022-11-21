#include "PreCompile.h"
#include "Player.h"
#include "GlobalContentsValue.h"
#include "Texture2DShadowRenderer.h"

std::shared_ptr<Player> Player::mainPlayer_ = nullptr;
bool Player::isInitialized_ = false;

Player::Player()
	: nowLevel_(nullptr),
	playerRenderer_(nullptr),
	speed_(200.0f),
	maxHp_(30),
	hp_(30),
	maxExp_(100),
	exp_(0),
	atk_(10),
	def_(10),
	range_(10)
{
	if (true == isInitialized_ && nullptr == mainPlayer_)
	{
		//플레이어 정상 생성.
	}
	else
	{
		MsgBoxAssert("플레이어 생성자를 직접 호출하지 마세요.");
		return;
	}

}

Player::~Player()
{
}

void Player::Start()
{


		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("Actor");
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
			collision_->SetDebugSetting(CollisionType::CT_OBB2D, float4::Red);
			collision_->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });
			collision_->ChangeOrder(ObjectOrder::Player);
	
		}
		std::shared_ptr< GameEngineCollision> col = CreateComponent<GameEngineCollision>();
		col->GetTransform().SetWorldScale(float4{ 1280,720 });
		col->ChangeOrder(ObjectOrder::Camera);
		col->SetDebugSetting(CollisionType::CT_OBB2D, float4::Green);


		playerRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		playerRenderer_->GetTransform().SetLocalScale(100, 100, 100);
		playerRenderer_->GetTransform().SetLocalPosition(0,0,-100);
		playerRenderer_->CreateFrameAnimation_CutTexture("PlayerIdle", FrameAnimation_Desc("PlayerIdle.png", 0, 10, 0.1f));
		playerRenderer_->CreateFrameAnimation_CutTexture("PlayerRun", FrameAnimation_Desc("PlayerRun.png", 0, 9, 0.1f));
		playerRenderer_->ChangeFrameAnimation("PlayerIdle");

		std::shared_ptr<Texture2DShadowRenderer> shadowRenderer = CreateComponent<Texture2DShadowRenderer>();
		shadowRenderer->SetTextureRenderer(playerRenderer_);

//	{
//		stateManager_.CreateState("Idle"
//			, std::bind(&Player::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
//			, std::bind(&Player::IdleStart, this, std::placeholders::_1)
//		);
//
//		stateManager_.CreateState("Move"
//			, std::bind(&Player::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
//			, [/*&*/=](const StateInfo& _Info)
//			{
//				playerRenderer_->ChangeFrameAnimation("PlayerRun");
//			});
//		stateManager_.ChangeState("Idle");
//	}


}

//void Player::IdleStart(const StateInfo& _Info)
//{
//	playerRenderer_->ChangeFrameAnimation("PlayerIdle");
//}
//
//void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
//{
//
//	if (true == GameEngineInput::GetInst()->IsPressed("PlayerLeft") ||
//		true == GameEngineInput::GetInst()->IsPressed("PlayerRight") ||
//		true == GameEngineInput::GetInst()->IsPressed("PlayerUp") ||
//		true == GameEngineInput::GetInst()->IsPressed("PlayerDown"))
//	{
//		stateManager_.ChangeState("Move");
//	}
//}
//
//void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
//{
//	if (false == GameEngineInput::GetInst()->IsPressed("PlayerLeft") &&
//		false == GameEngineInput::GetInst()->IsPressed("PlayerRight") &&
//		false == GameEngineInput::GetInst()->IsPressed("PlayerUp") &&
//		false == GameEngineInput::GetInst()->IsPressed("PlayerDown"))
//	{
//		stateManager_.ChangeState("Idle");
//		return;
//	}
//
//	if (true == GameEngineInput::GetInst()->IsPressed("PlayerLeft"))
//	{
//		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * speed_ * _DeltaTime);
//		playerRenderer_->GetTransform().PixLocalNegativeX();
//	}
//
//	if (true == GameEngineInput::GetInst()->IsPressed("PlayerRight"))
//	{
//		GetTransform().SetWorldMove(GetTransform().GetRightVector() * speed_ * _DeltaTime);
//		playerRenderer_->GetTransform().PixLocalPositiveX();
//	}
//	if (true == GameEngineInput::GetInst()->IsPressed("PlayerUp"))
//	{
//		GetTransform().SetWorldMove(GetTransform().GetUpVector() * speed_ * _DeltaTime);
//	}
//	if (true == GameEngineInput::GetInst()->IsPressed("PlayerDown"))
//	{
//		GetTransform().SetWorldMove(GetTransform().GetDownVector() * speed_ * _DeltaTime);
//	}
//
//}

CollisionReturn Player::MonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	_Other->GetRoot()->Off();
	return CollisionReturn::Stop;
}

void Player::MoveDirectionUpdate(float _deltaTime)
{
	if (true == GameEngineInput::GetInst()->IsPressed("PlayerLeft"))
	{
		if (true == GameEngineInput::GetInst()->IsPressed("PlayerRight"))
		{
			moveDirection_.x = 0;
		}
		else
		{
			playerRenderer_->GetTransform().PixLocalNegativeX();
			moveDirection_ += moveDirection_.Left;
		}
	}
	else if (true == GameEngineInput::GetInst()->IsUp("PlayerLeft"))
	{
		moveDirection_.x = 0;
	}

	if (true == GameEngineInput::GetInst()->IsPressed("PlayerRight"))
	{
		if (true == GameEngineInput::GetInst()->IsPressed("PlayerLeft"))
		{
			moveDirection_.x = 0;
		}
		else
		{
			playerRenderer_->GetTransform().PixLocalPositiveX();
			moveDirection_ += moveDirection_.Right;
		}
	}
	else if (true == GameEngineInput::GetInst()->IsUp("PlayerRight"))
	{
		moveDirection_.x = 0;
	}

	if (true == GameEngineInput::GetInst()->IsPressed("PlayerUp"))
	{
		if (true == GameEngineInput::GetInst()->IsPressed("PlayerDown"))
		{
			moveDirection_.y = 0;
		}
		else
		{
			moveDirection_ += moveDirection_.Up;
		}
	}
	else if (true == GameEngineInput::GetInst()->IsUp("PlayerUp"))
	{
		moveDirection_.y = 0;
	}
	if (true == GameEngineInput::GetInst()->IsPressed("PlayerDown"))
	{
		if (true == GameEngineInput::GetInst()->IsPressed("PlayerUp"))
		{
			moveDirection_.y = 0;
		}
		else
		{
			moveDirection_ += moveDirection_.Down;
		}
	}
	else if (true == GameEngineInput::GetInst()->IsUp("PlayerDown"))
	{
		moveDirection_.y = 0;
	}

	if (moveDirection_ != 0)
	{
		playerRenderer_->ChangeFrameAnimation("PlayerRun");
		GetTransform().SetWorldMove(moveDirection_.Normalize3D() * speed_ * _deltaTime);
	}
	else
	{
		playerRenderer_->ChangeFrameAnimation("PlayerIdle");
	}
}

void Player::Update(float _deltaTime)
{
	//stateManager_.Update(_deltaTime);

	MoveDirectionUpdate(_deltaTime);
	collision_->IsCollision(CollisionType::CT_OBB2D, ObjectOrder::Monster, CollisionType::CT_OBB2D, std::bind(&Player::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
}

void Player::End()
{
}

void Player::SetLevel(GameEngineLevel* _NowLevel)
{
	nowLevel_ = _NowLevel;
}

void Player::CreatePlayer(
	GameEngineLevel* _thisLevel,
	const float4& _initPosition,
	const std::string_view& _playerName /*= "MainPlayer"*/
)
{
	if (nullptr != mainPlayer_)
	{
		MsgBoxAssert("플레이어를 이미 생성했습니다.");
		return;
	}

	isInitialized_ = true;

	mainPlayer_ = _thisLevel->CreateActor<Player>(ObjectOrder::Player, _playerName);

	mainPlayer_->SetLevel(_thisLevel);
	mainPlayer_->SetLevelOverOn();
	mainPlayer_->GetTransform().SetWorldPosition(_initPosition);
	_thisLevel->GetMainCameraActor()->GetTransform().SetWorldPosition(
		mainPlayer_->GetTransform().GetWorldPosition().x,
		mainPlayer_->GetTransform().GetWorldPosition().y,
		-100.f
	);
}
