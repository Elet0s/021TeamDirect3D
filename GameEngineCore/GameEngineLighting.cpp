#include "PreCompile.h"
#include "GameEngineLighting.h"
#include "GameEngineCamera.h"

GameEngineLighting::GameEngineLighting()
{
}

GameEngineLighting::~GameEngineLighting()
{
}

void GameEngineLighting::Update(float _deltaTime)
{
	this->lightingData_.lightingPos_ = this->GetTransform().GetWorldPosition();
	this->lightingData_.lightingDirection_ = this->GetTransform().GetForwardVector();
	this->lightingData_.lightingInversedDirection_ = this->GetTransform().GetBackVector();

	this->lightingData_.lightingDirection_.w = 0.f;
	this->lightingData_.lightingInversedDirection_.w = 0.f;
	//조명 방향벡터와 역방향 벡터는 방향벡터이므로 w가 0이어야 한다.
}

void GameEngineLighting::UpdataLightingData(std::weak_ptr<GameEngineCamera> _camera)
{
	this->GetTransform().SetViewMatrix(_camera.lock()->GetViewMatrix());
	this->GetTransform().SetProjectionMatrix(_camera.lock()->GetProjectionMatrix());
	this->GetTransform().CalculateWorldViewProjection();
	//조명 액터의 트랜스폼에 뷰행렬, 투영행렬 적용.

	this->lightingData_.viewLightingPos_
		= this->lightingData_.lightingPos_ * _camera.lock()->GetViewMatrix();
	this->lightingData_.viewLightingDirection_
		= this->lightingData_.lightingDirection_ * _camera.lock()->GetViewMatrix();
	this->lightingData_.viewLightingInversedDirection_
		= this->lightingData_.lightingInversedDirection_ * _camera.lock()->GetViewMatrix();
	//조명데이터에도 뷰행렬'만' 적용.

	this->lightingData_.viewLightingDirection_.Normalize3D();
	this->lightingData_.viewLightingInversedDirection_.Normalize3D();
	//조명의 뷰공간 방향벡터와 역방향벡터 정규화.

	this->lightingData_.viewLightingDirection_.w = 0.f;
	this->lightingData_.viewLightingInversedDirection_.w = 0.f;
	//조명의 뷰공간 방향벡터와 역방향벡터도 방향벡터이므로 w를 0으로 만든다.
}
