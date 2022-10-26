#include "PreCompile.h"
#include "Player.h"
#include "GlobalContentsValue.h"

Player* Player::mainPlayer_ = nullptr;

Player::Player()
	: playerRenderer_(nullptr)
{
	mainPlayer_ = this;
	//SetLevelOverOn();
}

Player::~Player()
{
}

void Player::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("PlayerRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("PlayerUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("PlayerDown", VK_DOWN);
	}

	this->GetTransform().SetLocalScale(1, 1, 1);
	this->GetTransform().SetWorldScale(1, 1, 1);


	playerRenderer_ = CreateComponent<GameEngineTextureRenderer>("PlayerRenderer");
	playerRenderer_->GetTransform().SetLocalScale(100, 100, 100);
	playerRenderer_->SetMesh("Rect");
	playerRenderer_->SetPipeLine("TextureAtlas");
	playerRenderer_->SetFolderTextureToIndex("Player_Idle.png", 0);

	stateManager_.CreateState("Idle"
		, std::bind(&Player::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::IdleStart, this, std::placeholders::_1)
	);

	stateManager_.CreateState("Move"
		, std::bind(&Player::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, [/*&*/=](const StateInfo& _Info)
		{
		});
}

void Player::Update(float _deltaTime)
{
	if (true == this->GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	this->GetLevel()->GetMainCameraActorTransform().SetLocalPosition(
		this->GetTransform().GetLocalPosition() + float4::Back * 100.f);

	stateManager_.Update(_deltaTime);
}

void Player::End()
{
}

void Player::IdleStart(const StateInfo& _info)
{
	//playerRenderer_->ChangeFrameAnimation("Idle");
}

void Player::IdleUpdate(float _deltaTime, const StateInfo& _info)
{
	if (true == GameEngineInput::GetInst()->IsPressed("PlayerLeft")
		|| true == GameEngineInput::GetInst()->IsPressed("PlayerRight")
		|| true == GameEngineInput::GetInst()->IsPressed("PlayerUp")
		|| true == GameEngineInput::GetInst()->IsPressed("PlayerDown"))
	{
		stateManager_.ChangeState("Move");
	}
}

void Player::MoveUpdate(float _deltaTime, const StateInfo& _info)
{
	if (false == GameEngineInput::GetInst()->IsPressed("PlayerLeft")
		&& false == GameEngineInput::GetInst()->IsPressed("PlayerRight")
		&& false == GameEngineInput::GetInst()->IsPressed("PlayerUp")
		&& false == GameEngineInput::GetInst()->IsPressed("PlayerDown"))
	{
		stateManager_.ChangeState("Idle");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPressed("PlayerLeft"))
	{
		this->GetTransform().SetWorldMove(GetTransform().GetLeftVector() * 200.0f * _deltaTime);
		playerRenderer_->GetTransform().PixLocalNegativeX();
	}
	if (true == GameEngineInput::GetInst()->IsPressed("PlayerRight"))
	{
		this->GetTransform().SetWorldMove(GetTransform().GetRightVector() * 200.0f * _deltaTime);
		playerRenderer_->GetTransform().PixLocalPositiveX();
	}
	if (true == GameEngineInput::GetInst()->IsPressed("PlayerUp"))
	{
		this->GetTransform().SetWorldMove(GetTransform().GetUpVector() * 200.0f * _deltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressed("PlayerDown"))
	{
		this->GetTransform().SetWorldMove(GetTransform().GetDownVector() * 200.0f * _deltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressed("PlayerForward"))
	{
		this->GetTransform().SetWorldMove(GetTransform().GetForwardVector() * 200.0f * _deltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressed("PlayerBack"))
	{
		this->GetTransform().SetWorldMove(GetTransform().GetBackVector() * 200.0f * _deltaTime);
	}

	this->GetLevel()->GetMainCameraActorTransform().SetLocalPosition(this->GetTransform().GetLocalPosition() + float4::Back * 100.f);
	//플레이어에 카메라효과 부여.
}
