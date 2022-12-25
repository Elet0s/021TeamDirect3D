#include "PreCompile.h"
#include "GameEngineLighting.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderTarget.h"

GameEngineLighting::GameEngineLighting(): lightViewport_()
{
	lightingData_.shadowRenderTargetWidth_ = GameEngineWindow::GetScale().x * 1.5f;
	lightingData_.shadowRenderTargetHeight_ = GameEngineWindow::GetScale().y * 1.5f;
	lightingData_.lightingViewFrustumNearZ_ = 0.1f;
	lightingData_.lightingViewFrustumFarZ_ = 1000.f;
	//�׸��� ����Ÿ�ٿ� �׸��ڸ� �׸��µ� �ʿ��� ���� �Է�.
}

GameEngineLighting::~GameEngineLighting()
{
}

void GameEngineLighting::Start()
{
	lightViewport_.TopLeftX = 0.f;
	lightViewport_.TopLeftY = 0.f;
	lightViewport_.Width = lightingData_.shadowRenderTargetWidth_;
	lightViewport_.Height = lightingData_.shadowRenderTargetHeight_;
	lightViewport_.MinDepth = 0.f;
	lightViewport_.MaxDepth = 1.f;
	//���� ����Ʈ �ʱ�ȭ.

	shadowRenderTarget_ = GameEngineRenderTarget::Create("ShadowRenderTarget");
	shadowRenderTarget_->CreateRenderTargetTexture(
		float4(lightingData_.shadowRenderTargetWidth_, lightingData_.shadowRenderTargetHeight_),
		DXGI_FORMAT_R32_FLOAT,	//4���� �� �ʿ��Ѱ� �ƴ϶� 0~1 ���� �׸��� �󵵸� ������ ����ϹǷ� �� �������� ����.
		float4::Zero
	);
	shadowRenderTarget_->CreateDepthTexture(0);
	//�׸��� ������ ���� ����Ÿ�ٺ�� ���̴����ҽ���, ���̽��ٽǺ� ����.
}

void GameEngineLighting::Update(float _deltaTime)
{
	this->lightingData_.lightingPosition_ = this->GetTransform().GetWorldPosition();
	this->lightingData_.lightingDirection_ = this->GetTransform().GetForwardVector();
	this->lightingData_.inverseLightingDirection_ = this->GetTransform().GetBackVector();

	this->lightingData_.lightingDirection_.w = 0.f;
	this->lightingData_.inverseLightingDirection_.w = 0.f;
	//���� ���⺤�Ϳ� ������ ���ʹ� ���⺤���̹Ƿ� w�� 0�̾�� �Ѵ�.

	lightingData_.lightingViewMatrix_.LookToLH(
		this->GetTransform().GetWorldPosition(),
		this->GetTransform().GetForwardVector(),
		this->GetTransform().GetUpVector()
	);
	lightingData_.inverseLightingViewMatrix_ = lightingData_.lightingViewMatrix_.InverseReturn();
	//���� ����İ� ����� ����.

	lightingData_.lightingProjectionMatrix_.ProjectOrthographicLH(
		lightingData_.shadowRenderTargetWidth_,
		lightingData_.shadowRenderTargetHeight_,
		lightingData_.lightingViewFrustumNearZ_,
		lightingData_.lightingViewFrustumFarZ_
	);
	lightingData_.inverseLightingProjectionMatrix_ = lightingData_.lightingProjectionMatrix_.InverseReturn();
	//���� ������İ� ����� ����.

	//lightingData_.lightingViewProjectionMatrix_ 
	//	= lightingData_.lightingViewMatrix_ * lightingData_.lightingProjectionMatrix_;
}

void GameEngineLighting::UpdataLightingData(std::weak_ptr<GameEngineCamera> _camera)
{
	this->lightingData_.cameraViewMatrix_ = _camera.lock()->GetViewMatrix();
	this->lightingData_.inverseCameraViewMatrix_ = this->lightingData_.cameraViewMatrix_.InverseReturn();

	this->GetTransform().SetViewMatrix(_camera.lock()->GetViewMatrix());
	this->GetTransform().SetProjectionMatrix(_camera.lock()->GetProjectionMatrix());
	this->GetTransform().CalculateWorldViewProjection();
	//���� ������ Ʈ�������� �����, ������� ����.

	this->lightingData_.viewLightingPosition_
		= this->lightingData_.lightingPosition_ * _camera.lock()->GetViewMatrix();
	this->lightingData_.viewLightingDirection_
		= this->lightingData_.lightingDirection_ * _camera.lock()->GetViewMatrix();
	this->lightingData_.inverseViewLightingDirection_
		= this->lightingData_.inverseLightingDirection_ * _camera.lock()->GetViewMatrix();
	//�������Ϳ��� ī�޶��� �����'��' ����.

	this->lightingData_.viewLightingDirection_.Normalize3D();
	this->lightingData_.inverseViewLightingDirection_.Normalize3D();
	//������ ����� ���⺤�Ϳ� �����⺤�� ����ȭ.

	this->lightingData_.viewLightingDirection_.w = 0.f;
	this->lightingData_.inverseViewLightingDirection_.w = 0.f;
	//������ ����� ���⺤�Ϳ� �����⺤�͵� ���⺤���̹Ƿ� w�� 0���� �����.

	//this->lightingData_.viewSpaceCameraPosition_
	//	= _camera.lock()->GetTransform().GetWorldPosition() * _camera.lock()->GetViewMatrix();
	//����� ī�޶���ġ�� (0, 0, 0) ���� �ƴѰ�?? ���� ����� �ʿ䰡 �ֳ�??
}

void GameEngineLighting::SetShadowRenderTarget()
{
	shadowRenderTarget_->Clear();
	shadowRenderTarget_->Setting();
}
