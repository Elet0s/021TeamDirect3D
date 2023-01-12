#include "PreCompile.h"
#include "Player.h"
#include "GlobalContentsValue.h"
#include "Texture2DShadowRenderer.h"
#include "PlayerUI.h"
#include "Monster.h"
#include "SoulCardSelectBox.h"

std::shared_ptr<Player> Player::mainPlayer_ = nullptr;
bool Player::isInitialized_ = false;
std::shared_ptr<SkillManager> Player::playerSkillManager_ = std::shared_ptr<SkillManager>(new SkillManager);

Player::Player()
	:playerRenderer_(nullptr),
	collision_(nullptr),
	itemRangeCollision_(nullptr),
	playerInfo_(nullptr),
	dashTimer_(0),
	dashState_(false),
	hitOnoff_(false),
	serchCloseMonster_(),
	flash_(false),
	flashLoop_(false),
	flashTimer_(0)
	
{
	if (true == isInitialized_ && nullptr == mainPlayer_)
	{
		//플레이어 정상 생성.
		playerInfo_ = std::make_shared<PlayerInfo>();
		playerPassiveInfo_ = std::make_shared<PlayerPassiveInfo>();
	}
	else
	{
		MsgBoxAssert("플레이어 생성자를 직접 호출하지 마세요.");
		return;
	}
}

Player::~Player()
{
	//if (nullptr != Player::playerSkillManager_)
	//{
	//	Player::playerSkillManager_ = nullptr;
	//}
}

void Player::Start()
{

	if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("PlayerRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("PlayerUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("PlayerDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("PlayerDash", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("Skill15On", 'B');
		GameEngineInput::GetInst()->CreateKey("Skill04On", 'N');
		GameEngineInput::GetInst()->CreateKey("Skill05On", 'M');
	}
	{
		collision_ = CreateComponent<GameEngineCollision>();
		collision_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Blue);
		collision_->GetTransform().SetLocalScale({ 70.f, 70.f, 1.0f });
		collision_->ChangeOrder(ObjectOrder::Player);
		collision_->SetCollisionMode(CollisionMode::Multiple);

		itemRangeCollision_ = CreateComponent<GameEngineCollision>();
		itemRangeCollision_->SetDebugSetting(CollisionType::CT_Sphere2D, float4::Blue);
		itemRangeCollision_->GetTransform().SetLocalScale({ 300.f, 300.f, 1.0f });
		itemRangeCollision_->ChangeOrder(ObjectOrder::Range);
		itemRangeCollision_->SetCollisionMode(CollisionMode::Multiple);
		itemRangeCollision_->GetTransform().SetLocalMove({ 0.f,-10.f ,0.f});
	}

	playerRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	playerRenderer_->Initialize("DeferredRendering");
	playerRenderer_->GetTransform().SetLocalScale(90, 90, 1);
	playerRenderer_->CreateFrameAnimation_CutTexture("PlayerIdle", FrameAnimation_Desc("PlayerIdle.png", 0, 10, 0.2f));
	playerRenderer_->CreateFrameAnimation_CutTexture("PlayerRun", FrameAnimation_Desc("PlayerRun.png", 0, 9, 0.2f));
	playerRenderer_->ChangeFrameAnimation("PlayerIdle");
	playerRenderer_->ChangeCamera(CameraOrder::MidCamera);
	std::shared_ptr<Texture2DShadowRenderer> shadowRenderer = CreateComponent<Texture2DShadowRenderer>();
	shadowRenderer->SetTextureRenderer(playerRenderer_);

	//serchCloseMonster_;
	//Monster::GetMonsterList();

	//playerSkillManager_->GetSkillList()[5][12]->currentlevel_++;

}


CollisionReturn Player::PlayerToGameItemObjectCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	std::shared_ptr<GameItemObject> A = std::dynamic_pointer_cast<GameItemObject>(_Other->GetActor());
	if (A->GetObjectOrder() == ItemObjectOrder::GreenExp)
	{
		playerInfo_->exp_ += 5;
	}
	else if (A->GetObjectOrder() == ItemObjectOrder::YellowExp)
	{
		playerInfo_->exp_ += 10;
	}
	else if (A->GetObjectOrder() == ItemObjectOrder::RedExp)
	{
		playerInfo_->exp_ += 15;
	}
	else if (A->GetObjectOrder() == ItemObjectOrder::Meet)
	{

			playerInfo_->hp_ += 30;
			if (playerInfo_->maxHp_ < playerInfo_->hp_)
			{
				playerInfo_->hp_ = playerInfo_->maxHp_;
			}
	}
	else if (A->GetObjectOrder() == ItemObjectOrder::Gold)
	{
		playerInfo_->gold_ += 10;
	}
	else if (A->GetObjectOrder() == ItemObjectOrder::Voidbead)
	{
		//for (size_t i = 0; i < 300; i++)
		//{
		//	//if (Monster::GetItemObjectManager()->GetallObjectContainer()[i] == A)
		//	{
		//		//순회돌면서 체이스 상태로 변경해줘야함
		//	}
		//
		//}
	}
	// 여기서 오브젝트 끄고 컨테이너에서 빼줘야함
	for (size_t i = 0; i < Monster::GetItemObjectManager()->GetallObjectContainer().size(); i++)
	{
		if (Monster::GetItemObjectManager()->GetallObjectContainer()[i] == A)
		{
			A->itemObjectRenderer_->Off();
			A->itemObjectCol_->Off();
			A->chasePlayer_ = false;
			A->Off();
			Monster::GetItemObjectManager()->DelteObject(i);
		}
	}
	return CollisionReturn::Stop;
}

CollisionReturn Player::ItemRangeToGameItemObjectCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	std::shared_ptr<GameItemObject> A = std::dynamic_pointer_cast<GameItemObject>(_Other->GetActor());
	A->chasePlayer_ = true;
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
		playerResultDirection_ = moveDirection_.Normalize3D() * ((playerInfo_->speed_ * playerPassiveInfo_->speed_Per / 100) - playerInfo_->pushSpeed_);
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
		if (playerInfo_->dashCount_ > 0)
		{
			playerInfo_->dashCount_ -= 1;
			dashState_ = true;
		}
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
		else if (dashTimer_ > 0.2f)
		{
			dashState_ = false;
			dashTimer_ = 0;
		}
	}
}

void Player::PlayerDeathEvent()
{
	if (playerInfo_->hp_ <= 0)
	{
		//Off();
	}
}

void Player::LevelUpEvent()
{
	if (playerInfo_->exp_ >= playerInfo_->maxExp_)
	{
		playerInfo_->exp_ -= playerInfo_->maxExp_;
		playerInfo_->maxExp_ *= 1.5;
		playerInfo_->level_ += 1;
		GetLevel()->CreateActor<SoulCardSelectBox>();
		GameEngineTime::GetInst()->SetGlobalTimeScale(0);
	}
}

void Player::ColCheak()
{
	itemRangeCollision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Item, CollisionType::CT_Sphere2D, std::bind(&Player::ItemRangeToGameItemObjectCollision, this, std::placeholders::_1, std::placeholders::_2));
	collision_->IsCollision(CollisionType::CT_Sphere2D, ObjectOrder::Item, CollisionType::CT_Sphere2D, std::bind(&Player::PlayerToGameItemObjectCollision, this, std::placeholders::_1, std::placeholders::_2));
}

void Player::Update(float _deltaTime)
{
	playerInfo_->stageTimer_ += _deltaTime;

	MoveDirectionUpdate(_deltaTime);
	PlayerDash(_deltaTime);

	PlayerDeathEvent();
	ColCheak();
	LevelUpEvent();
	FlashPlayer(_deltaTime);
	if (true == GameEngineInput::GetInst()->IsDown("Skill15On")) //나중에 카드 뽑으면 올려주는걸로 대체할 것임
	{
		if (playerSkillManager_->GetSkillList()[5][2]->currentlevel_ < 1)
		{
			playerSkillManager_->GetSkillList()[5][2]->currentlevel_ += 1;
		}
	}
	if (true == GameEngineInput::GetInst()->IsDown("Skill04On")) //나중에 카드 뽑으면 올려주는걸로 대체할 것임
	{
		if (playerSkillManager_->GetSkillList()[5][3]->currentlevel_ < 1)
		{
			playerSkillManager_->GetSkillList()[5][3]->currentlevel_ += 1;
		}
	}
	if (true == GameEngineInput::GetInst()->IsDown("Skill05On")) //나중에 카드 뽑으면 올려주는걸로 대체할 것임
	{
		if (playerSkillManager_->GetSkillList()[5][0]->currentlevel_ < 1)
		{
			playerSkillManager_->GetSkillList()[5][0]->currentlevel_ += 1;
		}
	}

	playerSkillManager_->SkillLevelCheak();
}

void Player::End()
{

}

void Player::CreatePlayer(GameEngineLevel* _thisLevel, const float4& _initPosition, const std::string_view& _playerName /*= "MainPlayer"*/)
{
	if (nullptr != mainPlayer_)
	{
		MsgBoxAssert("플레이어가 이미 존재합니다.");
		return;
	}

	isInitialized_ = true;

	mainPlayer_ = _thisLevel->CreateActor<Player>(ObjectOrder::Player);
	mainPlayer_->GetTransform().SetWorldPosition(_initPosition);
	_thisLevel->GetMainCameraActor()->GetTransform().SetWorldPosition(
		mainPlayer_->GetTransform().GetWorldPosition().x,
		mainPlayer_->GetTransform().GetWorldPosition().y,
		-220.f
	);

	playerSkillManager_->SetLevel(_thisLevel);
	playerSkillManager_->CreatePlayerAllSkill();
}

void Player::ResetScore()
{
	playerInfo_->targetScore_ = 0;
	playerInfo_->eliteTargetScore_ = 0;
	playerInfo_->stageTimer_ = 0.f;
}

void Player::FlashPlayer(float _deltaTime)
{
	if (flash_ == true)
	{
		if (flashTimer_ < 0.2f)
		{
			flashTimer_ += _deltaTime;
			playerRenderer_->GetPixelData().mulColor_ = float4{ 5.0f, 5.0f, 5.0f, 0.7f };
		}
		else
		{
			flashLoop_ = true;
		}

		if (flashLoop_ == true)
		{
			playerRenderer_->GetPixelData().mulColor_ = float4{ 1.f,1.f ,1.f ,1.f };
			flashTimer_ = 0;
			flashLoop_ = false;
			flash_ = false;
		}
	}
}