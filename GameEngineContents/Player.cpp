#include "PreCompile.h"
#include "Player.h"
#include "GlobalContentsValue.h"
#include "Texture2DShadowRenderer.h"
#include "PlayerUI.h"
#include "Monster.h"
#include "SkillManager.h"

std::shared_ptr<Player> Player::mainPlayer_ = nullptr;
bool Player::isInitialized_ = false;

Player::Player()
	:playerRenderer_(nullptr),
	collision_(nullptr),
	playerInfo_(nullptr),
	dashTimer_(0),
	dashState_(false),
	hitOnoff_(false)
	//playerSkillManager_()

{
	if (true == isInitialized_ && nullptr == mainPlayer_)
	{
		//플레이어 정상 생성.
		playerInfo_ = std::make_shared<PlayerInfo>();
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

	std::vector<GameEngineFile> playerTexture = Dir.GetAllFiles();
	for (size_t i = 0; i < playerTexture.size(); i++)
	{
		GameEngineTexture::Load(playerTexture[i].GetFullPath());
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
		GameEngineInput::GetInst()->CreateKey("PlayerDash", VK_SPACE);
	}
	{
		collision_ = CreateComponent<GameEngineCollision>();
		collision_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Red);
		collision_->GetTransform().SetLocalScale({ 70.f, 70.f, 100.0f });
		collision_->ChangeOrder(ObjectOrder::Player);
	}

	playerRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	playerRenderer_->GetTransform().SetLocalScale(90, 90, 0);
	playerRenderer_->GetTransform().SetWorldPosition(0, 0, -100);
	playerRenderer_->CreateFrameAnimation_CutTexture("PlayerIdle", FrameAnimation_Desc("PlayerIdle.png", 0, 10, 0.2f));
	playerRenderer_->CreateFrameAnimation_CutTexture("PlayerRun", FrameAnimation_Desc("PlayerRun.png", 0, 9, 0.2f));
	playerRenderer_->ChangeFrameAnimation("PlayerIdle");

	std::shared_ptr<Texture2DShadowRenderer> shadowRenderer = CreateComponent<Texture2DShadowRenderer>();
	shadowRenderer->SetTextureRenderer(playerRenderer_);
}

CollisionReturn Player::PlayerToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	//td::shared_ptr<Monster> A = std::dynamic_pointer_cast<Monster>(_Other->GetActor());
	//
	//f (playerInfo_->hp_ > 0)
	//
	//	playerInfo_->hp_ -= A->GetMonsterInfo().atk_;
	//	playerInfo_->exp_ += A->GetMonsterInfo().giveExp_;
	//
	return CollisionReturn::Stop;
}

void Player::MoveDirectionUpdate(float _deltaTime)
{
	if (false == collision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D))
	{
		playerInfo_->pushSpeed_ = 0;
	}
	if (true == GameEngineInput::GetInst()->IsPressed("PlayerLeft"))
	{
		if (true == GameEngineInput::GetInst()->IsPressed("PlayerRight"))
		{
			moveDirection_.x = 0;
		}
		else
		{
			playerInfo_->RLDirection_ = true;
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
			playerInfo_->RLDirection_ = false;
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
		playerResultDirection_ = moveDirection_.Normalize3D() * (playerInfo_->speed_ - playerInfo_->pushSpeed_);
		GetTransform().SetWorldMove(playerResultDirection_ * _deltaTime);
	}
	else
	{
		playerResultDirection_ = 0;
		playerRenderer_->ChangeFrameAnimation("PlayerIdle");
	}

}

void Player::PlayerDash(float _deltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("PlayerDash"))
	{
		dashState_ = true;
	}
	if (dashState_ == true)
	{
		dashTimer_ += _deltaTime;
		if (dashTimer_ < 0.2f)
		{

			if (true == GameEngineInput::GetInst()->IsPressed("PlayerLeft") || true == GameEngineInput::GetInst()->IsPressed("PlayerRight") || true == GameEngineInput::GetInst()->IsPressed("PlayerUp") || true == GameEngineInput::GetInst()->IsPressed("PlayerDown"))
			{
				GetTransform().SetWorldMove(moveDirection_.Normalize3D() * 1000.0f * _deltaTime);
			}
			else
			{
				if (playerInfo_->RLDirection_ == false)
				{
					GetTransform().SetWorldMove(float4{ 1000.0f,0.f,0.f,1.f }*_deltaTime);
				}
				else if (playerInfo_->RLDirection_ == true)
				{
					GetTransform().SetWorldMove(float4{ -1000.f,0.f,0.f,1.f }*_deltaTime);
				}
			}
		}
		else if (dashTimer_> 0.2f)
		{
			dashState_ = false;
			dashTimer_ = 0;
		}
	}

}

void Player::Update(float _deltaTime)
{
	MoveDirectionUpdate(_deltaTime);
	PlayerDash(_deltaTime);
	//collision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Monster, CollisionType::CT_Sphere2D, std::bind(&Player::PlayerToMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));

}

void Player::End()
{

}

void Player::CreatePlayer(GameEngineLevel* _thisLevel, const float4& _initPosition, const std::string_view& _playerName /*= "MainPlayer"*/)
{
	if (nullptr != mainPlayer_)
	{
		MsgBoxAssert("플레이어를 이미 생성했습니다.");
		return;
	}

	isInitialized_ = true;

	mainPlayer_ = _thisLevel->CreateActor<Player>(ObjectOrder::Player);
	mainPlayer_->SetLevelOverOn();
	mainPlayer_->GetTransform().SetWorldPosition(_initPosition);
	_thisLevel->GetMainCameraActor()->GetTransform().SetWorldPosition(mainPlayer_->GetTransform().GetWorldPosition().x,mainPlayer_->GetTransform().GetWorldPosition().y,-100.f);
}
