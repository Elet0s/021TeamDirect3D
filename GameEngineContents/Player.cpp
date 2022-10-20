#include "PreCompile.h"
#include "Player.h"
#include "GlobalContentsValue.h"

Player* Player::mainPlayer_ = nullptr;

Player::Player()
	: playerRenderer_(nullptr), 
	speed_(50.f),
	color_(float4::Black)
{
	mainPlayer_ = this;
	//SetLevelOverOn();
}

Player::~Player()
{
}

bool Player::MonsterCollision(GameEngineCollision* _this, GameEngineCollision* _other)
{
	_other->GetActor()->Death();
	return true;
}

void Player::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", 'J');
		GameEngineInput::GetInst()->CreateKey("PlayerRight", 'L');
		GameEngineInput::GetInst()->CreateKey("PlayerUp", 'I');
		GameEngineInput::GetInst()->CreateKey("PlayerDown", 'K');
		GameEngineInput::GetInst()->CreateKey("PlayerForward", 'Y');
		GameEngineInput::GetInst()->CreateKey("PlayerBack", 'U');
	}

	this->GetTransform().SetLocalScale(1, 1, 1);
	this->GetTransform().SetWorldScale(1, 1, 1);


	playerRenderer_ = CreateComponent<GameEngineDefaultRenderer>("PlayerRenderer");
	playerRenderer_->GetTransform().SetLocalScale(100, 100, 100);
	playerRenderer_->SetMesh("Box");
	playerRenderer_->SetPipeLine("Color");
	playerRenderer_->GetShaderResourceHelper().SetConstantBuffer_Link("ResultColor", this->color_);

	//GameEngineFontRenderer* fontRenderer = CreateComponent<GameEngineFontRenderer>();
	//fontRenderer->SetText("안녕하세요", "궁서");
	//fontRenderer->SetColor({ 1.0f, 0.0f, 0.0f });
	//fontRenderer->SetTextPosition({0, 0});
	//fontRenderer->SetRenderingOrder(10000);
	//fontRenderer->SetSize(80);


	stateManager_.CreateState("Idle",
		std::bind(&Player::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Player::IdleStart, this, std::placeholders::_1)
	);
	stateManager_.CreateState("Move",
		std::bind(&Player::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2),
		[this](const StateInfo& _info)->void{ /*playerRenderer_->ChangeFrameAnimation("Move");*/ }
	);
	stateManager_.ChangeState("Idle");







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
		this->GetTransform().SetWorldMove(GetTransform().GetLeftVector() * speed_ * _deltaTime);
		playerRenderer_->GetTransform().PixLocalNegativeX();
	}
	if (true == GameEngineInput::GetInst()->IsPressed("PlayerRight"))
	{
		this->GetTransform().SetWorldMove(GetTransform().GetRightVector() * speed_ * _deltaTime);
		playerRenderer_->GetTransform().PixLocalPositiveX();
	}
	if (true == GameEngineInput::GetInst()->IsPressed("PlayerUp"))
	{
		this->GetTransform().SetWorldMove(GetTransform().GetUpVector() *speed_ * _deltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressed("PlayerDown"))
	{
		this->GetTransform().SetWorldMove(GetTransform().GetDownVector() * speed_ * _deltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressed("PlayerForward"))
	{
		this->GetTransform().SetWorldMove(GetTransform().GetForwardVector() * speed_ * _deltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressed("PlayerBack"))
	{
		this->GetTransform().SetWorldMove(GetTransform().GetBackVector() * speed_ * _deltaTime);
	}

	this->GetLevel()->GetMainCameraActorTransform().SetLocalPosition(this->GetTransform().GetLocalPosition() + float4::Back * 100.f);
	//플레이어에 카메라효과 부여.
}
