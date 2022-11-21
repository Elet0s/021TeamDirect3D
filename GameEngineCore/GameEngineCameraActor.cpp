#include "PreCompile.h"
#include "GameEngineCameraActor.h"
#include "GameEngineCollision.h"

GameEngineCameraActor::GameEngineCameraActor()
	: cameraComponent_(nullptr),
	freeCameraMode_(false),
	cameraMovingSpeed_(500.f),
	rotationSpeed_(180.f),
	prevProjectionMode_(CameraProjectionMode::Orthographic)
{
}

GameEngineCameraActor::~GameEngineCameraActor()
{
}

void GameEngineCameraActor::Start()
{
	cameraComponent_ = CreateComponent<GameEngineCamera>();
	
	if (false == GameEngineInput::GetInst()->IsKey("CamLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("CamLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("CamRight", 'D');
		GameEngineInput::GetInst()->CreateKey("CamUp", 'Q');
		GameEngineInput::GetInst()->CreateKey("CamDown", 'E');
		GameEngineInput::GetInst()->CreateKey("CamForward", 'W');
		GameEngineInput::GetInst()->CreateKey("CamBack", 'S');

		GameEngineInput::GetInst()->CreateKey("CamRot", VK_RBUTTON);
		GameEngineInput::GetInst()->CreateKey("CamBoost", VK_LSHIFT);
	}
}

void GameEngineCameraActor::Update(float _deltaTime)
{

	if (false == freeCameraMode_)
	{
		return;
	}

	float cameraSpeed = cameraMovingSpeed_;


	if (true == GameEngineInput::GetInst()->IsPressed("CamBoost"))
	{
		cameraSpeed *= 3.f;
	}

	if (true == GameEngineInput::GetInst()->IsPressed("CamLeft"))
	{
		this->GetTransform().SetLocalMove(
			this->GetTransform().GetLeftVector() * cameraSpeed * _deltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressed("CamRight"))
	{
		this->GetTransform().SetLocalMove(
			this->GetTransform().GetRightVector() * cameraSpeed * _deltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressed("CamUp"))
	{
		this->GetTransform().SetLocalMove(
			this->GetTransform().GetUpVector() * cameraSpeed * _deltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressed("CamDown"))
	{
		this->GetTransform().SetLocalMove(
			this->GetTransform().GetDownVector() * cameraSpeed * _deltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPressed("CamForward"))
	{
		this->GetTransform().SetLocalMove(
			this->GetTransform().GetForwardVector() * cameraSpeed * _deltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressed("CamBack"))
	{
		this->GetTransform().SetLocalMove(
			this->GetTransform().GetBackVector() * cameraSpeed * _deltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPressed("CamRot"))
	{
		float4 mouseDir = this->cameraComponent_->GetMouseWorldDirection();
		float4 rotMouseDir;
		rotMouseDir.x = -mouseDir.y;		//마우스 좌표값 입력을 왜 반대로?? 직접 계산해볼 것.
		rotMouseDir.y = mouseDir.x;	//마우스 좌표값 입력을 왜 반대로?? 직접 계산해볼 것.
		GetTransform().SetAddWorldRotation(rotMouseDir * rotationSpeed_);
	}
}

void GameEngineCameraActor::End()
{
}

void GameEngineCameraActor::FreeCameraModeOnOff()
{
	freeCameraMode_ = !freeCameraMode_;

	if (true == freeCameraMode_)
	{
		prevProjectionMode_ = cameraComponent_->GetProjectionMode();
		cameraComponent_->SetProjectionMode(CameraProjectionMode::Perspective);
		originalTransform_.Copy(this->GetTransform());
	}
	else
	{
		cameraComponent_->SetProjectionMode(prevProjectionMode_);
		this->GetTransform().Copy(originalTransform_);
	}
}
