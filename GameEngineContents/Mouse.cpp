#include "PreCompile.h"
#include "Mouse.h"
#include "GlobalContentsValue.h"

Mouse::Mouse()
	: defaultPointerRenderer_(nullptr),
	crossHairRenderer_(nullptr),
	aimLineRenderer_(nullptr),
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
	//메인카메라 월드좌표 == 레이 원점.

	float4 rayDirection = this->GetLevel()->GetMainCamera()->GetRayTowardMousePointer();
	//레이 방향벡터.

	DirectX::XMVECTOR rectVertexWorldPosition[4] =
	{
		((localVertexPosition_[0] + _pivot) * _worldWorldMatrix).directXVector_,
		((localVertexPosition_[1] + _pivot) * _worldWorldMatrix).directXVector_,
		((localVertexPosition_[2] + _pivot) * _worldWorldMatrix).directXVector_,
		((localVertexPosition_[3] + _pivot) * _worldWorldMatrix).directXVector_
	};
	//매개변수로 받은, 레이와의 교차 여부를 알고싶은 렌더러의 월드행렬을 "Rect"의 네 정점에 적용해서 저장한다.
	//"Rect"외에 다른 메쉬와의 교차 여부도 확인해야 하거나, 3~4개의 특정 렌더러와 레이의 교차여부만 확인하는 지금 방식에서 
	// 화면 내 임의의 클릭지점 좌표를 받아올 필요가 생긴다면 구조 변경할 것.

	float distance1 = 0.f;
	float distance2 = 0.f;
	//여기서는 별 필요 없을것 같지만 그래도 함수에서 요구하므로 레이 길이도 받을 준비도 해 둔다. 

	bool result1 = DirectX::TriangleTests::Intersects(
		cameraWorldPosition.directXVector_,
		rayDirection.directXVector_,
		rectVertexWorldPosition[0],
		rectVertexWorldPosition[1],
		rectVertexWorldPosition[2],
		distance1
	);

	bool result2 = DirectX::TriangleTests::Intersects(
		cameraWorldPosition.directXVector_,
		rayDirection.directXVector_,
		rectVertexWorldPosition[0],
		rectVertexWorldPosition[2],
		rectVertexWorldPosition[3],
		distance2
	);
	//DirectX::TriangleTests::Intersects()함수는 네임스페이스 이름처럼 삼각형 기준으로 교차 여부를 판정하는데 
	// 여기서는 사각형과 레이의 교차 여부가 필요하므로 삼각형 두개를 확인한다.

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

	defaultPointerRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	defaultPointerRenderer_->SetPivot(PivotMode::LeftTop);
	defaultPointerRenderer_->GetTransform().SetWorldScale(20, 28, 1);
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
		this->GetTransform().SetWorldPosition(this->GetLevel()->GetMainCamera()->GetMousePositionInWorldSpace());

		if (true == isAiming_)	//활성화된 플레이어 무기 중에 단창 등의 원하는 방향으로 투사체를 날리는 무기가 있는 경우.
		{
			aimLineRenderer_->GetTransform().SetWorldPosition(pivotWorldPosition_);
			//에임라인 렌더러의 중심축을 잡아준다. 중심축 위치는 외부에서 플레이어 월드좌표를 넣어줄 것.
			
			float4 aimingVector = this->GetTransform().GetWorldPosition() - pivotWorldPosition_;
			//에임라인이 향해야 할 방향 벡터.

			aimingVector.z = 0.f;
			//2D 기준으로만 생각할 것이므로 z값은 0으로 만들어서 오차를 줄인다.

			aimingVector /= aimingVector.Length();
			//정규화.

			float aimLineAngle = 0;
			//에임라인의 각도. 0이면 에임라인이 (0, 1, 0) 방향을 향한다.

			if (0 < aimingVector.x)
			{
				aimLineAngle = -acosf(aimingVector.y) * GameEngineMath::RadianToDegree;
				//이 부분이 없으면 에임라인이 오른쪽으로 넘어가지 않는다.
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
			this->GetLevel()->GetCamera(1)->GetMousePositionInWorldSpace()
		);

		//전투맵에서는 == 메인카메라가 원근투영일때는 마우스포인터 렌더러 위치 잡아주는것 외에 특별히 할 일이 없다.
	}
}

void Mouse::End()
{
	//DirectX::XMPlaneIntersectLine();
	//DirectX::TriangleTests::Intersects();
}
