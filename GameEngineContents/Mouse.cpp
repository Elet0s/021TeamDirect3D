#include "PreCompile.h"
#include "Mouse.h"
#include "GlobalContentsValue.h"

Mouse::Mouse()
	: defaultPointerRenderer_(nullptr),
	crossHairRenderer_(nullptr),
	aimLineRenderer_(nullptr),
	mouseCollision_(nullptr),
	mousePositionInWindow_(float4::Zero),
	mousePositionInWorldSpace_(float4::Zero),
	pivotWorldPosition_(float4::Zero),
	isAiming_(false)
{
	localVertexPosition_[0] = float4(-0.5f, 0.5f);
	localVertexPosition_[1] = float4(0.5f, 0.5f);
	localVertexPosition_[2] = float4(0.5f, -0.5f);
	localVertexPosition_[3] = float4(-0.5f, -0.5f);
}

Mouse::~Mouse()
{

}

void Mouse::ChangeMousePointerRenderer(bool _isAiming)
{
	isAiming_ = _isAiming;
	if (true == isAiming_)
	{
		defaultPointerRenderer_->Off();
		crossHairRenderer_->On();
		aimLineRenderer_->On();
	}
	else
	{
		defaultPointerRenderer_->On();
		crossHairRenderer_->Off();
		aimLineRenderer_->Off();
	}
}

void Mouse::UpdatePivotPosition(const float4& _pivot)
{
	pivotWorldPosition_ = _pivot;
}

bool Mouse::IsPointing(const float4x4& _worldWorldMatrix, const float4& _pivot)
{
	float4 cameraWorldPosition = this->GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition();
	//float4 direction = this->GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor() - origin;
	float4 mousePointerWorldPosition = this->GetLevel()->GetMainCamera()->GetMousePositionInWorldSpace();
	float4 direction = mousePointerWorldPosition - cameraWorldPosition;
	direction.Normalize3D();

	DirectX::XMVECTOR worldVertexPositionVector0 
		= ((localVertexPosition_[0] + _pivot) * _worldWorldMatrix).directXVector_;
	DirectX::XMVECTOR worldVertexPositionVector1 
		= ((localVertexPosition_[1] + _pivot) * _worldWorldMatrix).directXVector_;
	DirectX::XMVECTOR worldVertexPositionVector2 
		= ((localVertexPosition_[2] + _pivot) * _worldWorldMatrix).directXVector_;
	DirectX::XMVECTOR worldVertexPositionVector3
		= ((localVertexPosition_[3] + _pivot) * _worldWorldMatrix).directXVector_;

	float distance1 = 0.f;
	float distance2 = 0.f;

	bool result1 = DirectX::TriangleTests::Intersects(
		cameraWorldPosition.directXVector_,
		direction.directXVector_,
		worldVertexPositionVector0,
		worldVertexPositionVector1,
		worldVertexPositionVector2,
		distance1
	);

	bool result2 = DirectX::TriangleTests::Intersects(
		cameraWorldPosition.directXVector_,
		direction.directXVector_,
		worldVertexPositionVector0,
		worldVertexPositionVector2,
		worldVertexPositionVector3,
		distance2
	);

	if (true == result1 || true == result2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Mouse::Start()
{
	this->GetTransform().SetLocalScale(float4::One);
	this->GetTransform().SetWorldScale(float4::One);

	mouseCollision_ = CreateComponent<GameEngineCollision>();
	mouseCollision_->SetDebugSetting(CollisionType::CT_OBB2D, float4::Black);
	mouseCollision_->GetTransform().SetWorldScale( 10, 10, 10 );
	mouseCollision_->GetTransform().SetLocalPosition( 20, -28, 0 );
	mouseCollision_->ChangeOrder(ObjectOrder::Mouse);

	defaultPointerRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	defaultPointerRenderer_->GetTransform().SetWorldScale(20, 28, 1);
	defaultPointerRenderer_->GetTransform().SetLocalPosition( 10, -14, 0 );
	defaultPointerRenderer_->SetTexture("CursorSprite.png");
	defaultPointerRenderer_->ChangeCamera(CameraOrder::MousePointerCamera);

	crossHairRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	crossHairRenderer_->GetTransform().SetWorldScale(32, 32, 1);
	crossHairRenderer_->SetTexture("CrossHair.png");
	crossHairRenderer_->ChangeCamera(CameraOrder::MousePointerCamera);
	crossHairRenderer_->Off();

	aimLineRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	aimLineRenderer_->GetTransform().SetWorldScale(512, 512, 1);
	aimLineRenderer_->SetTexture("AimLine.png");
	aimLineRenderer_->ChangeCamera(CameraOrder::MousePointerCamera);
	aimLineRenderer_->Off();
}

void Mouse::Update(float _DeltaTime)
{

	//전투맵에서의 동작.
	if (CameraProjectionMode::Orthographic == this->GetLevel()->GetMainCamera()->GetProjectionMode())
	{
		//this->GetTransform().SetWorldPosition(
		//	this->GetLevel()->GetCamera(static_cast<UINT>(CameraOrder::MousePointerCamera))->GetMouseWorldPositionToActor()
		//);

		this->GetTransform().SetWorldPosition(this->GetLevel()->GetMainCamera()->GetMousePositionInWorldSpace());

		if (true == isAiming_)
		{
			aimLineRenderer_->GetTransform().SetWorldPosition(pivotWorldPosition_);
			
			float4 aimingVector = this->GetTransform().GetWorldPosition() - pivotWorldPosition_;
			aimingVector.z = 0.f;
			aimingVector /= aimingVector.Length();

			float aimLineAngle = 0;
			if (0 < aimingVector.x)
			{
				aimLineAngle = -acosf(aimingVector.y) * GameEngineMath::RadianToDegree;
			}
			else
			{
				aimLineAngle = acosf(aimingVector.y) * GameEngineMath::RadianToDegree;
			}

			aimLineRenderer_->GetTransform().SetWorldRotation(0.f, 0.f, aimLineAngle);
		}
	}
	//월드맵에서의 동작.
	else /*if (CameraProjectionMode::Perspective == this->GetLevel()->GetMainCamera()->GetProjectionMode())*/
	{
		if (true == isAiming_)
		{
			MsgBoxAssert("마우스포인터 렌더러 전환은 전투맵에서만 의미 있는 기능입니다.");
			return;
		}

		this->GetTransform().SetWorldPosition(
			this->GetLevel()->GetMainCamera()->GetMousePositionInWorldSpace()
		);

		defaultPointerRenderer_->GetTransform().SetWorldPosition(
			this->GetLevel()->GetCamera(1)->GetMousePositionInWorldSpace().x + 10.f,
			this->GetLevel()->GetCamera(1)->GetMousePositionInWorldSpace().y - 14.f,
			this->GetLevel()->GetCamera(1)->GetMousePositionInWorldSpace().z
		);

	}
}

void Mouse::End()
{
	//DirectX::XMPlaneIntersectLine();
	//DirectX::TriangleTests::Intersects();
}
