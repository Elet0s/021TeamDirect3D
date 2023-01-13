#include "PreCompile.h"
#include "Mouse.h"
#include "GlobalContentsValue.h"

Mouse::Mouse()
	: defaultPointerRenderer_(nullptr),
	crossHairRenderer_(nullptr),
	aimLineRenderer_(nullptr),
	mousePositionInWorldSpace_(float4::Zero),
	pivotWorldPosition_(float4::Zero),
	isAiming_(false),
	aimLineAngle_(0.f)
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

bool Mouse::IsPointing(const float4x4& _worldWorldMatrix, const float4& _renderPivot, bool _isUI /*= false*/)
{
	float4 cameraWorldPosition = this->GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition();
	//����ī�޶� ������ǥ == ���� ����.

	float4 rayDirection = this->GetLevel()->GetMainCamera()->GetRayTowardMousePointer();
	//���� ���⺤��.

	if (false == _isUI)
	{
		cameraWorldPosition = this->GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition();
		//����ī�޶� ������ǥ == ���� ����.

		rayDirection = this->GetLevel()->GetMainCamera()->GetRayTowardMousePointer();
		//���� ���⺤��.
	}
	else
	{
		cameraWorldPosition = this->GetLevel()->GetUICamera()->GetMousePositionInWorldSpace();
		//UI�� ���� ���������� UIī�޶� ��ϵǾ� �����Ƿ�,
		// UIī�޶� ���� ���콺 ������ǥ�� �޾Ƽ� �װ��� �����ϰ� ������� Z��� ������ ���̸� ���������� �����.

		rayDirection = float4::Blue;
		//���� ���⺤��. �׳� ������� Z��� �����ϰ� ó���Ѵ�.

		rayDirection.w = 0.f;
	}



	DirectX::XMVECTOR rectVertexWorldPosition[4] =
	{
		((localVertexPosition_[0] + _renderPivot) * _worldWorldMatrix).directXVector_,
		((localVertexPosition_[1] + _renderPivot) * _worldWorldMatrix).directXVector_,
		((localVertexPosition_[2] + _renderPivot) * _worldWorldMatrix).directXVector_,
		((localVertexPosition_[3] + _renderPivot) * _worldWorldMatrix).directXVector_
	};
	//�Ű������� ����, ���̿��� ���� ���θ� �˰���� �������� ��������� "Rect"�� �� ������ �����ؼ� �����Ѵ�.
	//"Rect"�ܿ� �ٸ� �޽����� ���� ���ε� Ȯ���ؾ� �ϰų�, 3~4���� Ư�� �������� ������ �������θ� Ȯ���ϴ� ���� ��Ŀ��� 
	// ȭ�� �� ������ Ŭ������ ��ǥ�� �޾ƿ� �ʿ䰡 ����ٸ� ���� ������ ��.

	float distance1 = 0.f;
	float distance2 = 0.f;
	//���⼭�� �� �ʿ� ������ ������ �׷��� �Լ����� �䱸�ϹǷ� ���� ���̵� ���� �غ� �� �д�. 

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
	//DirectX::TriangleTests::Intersects()�Լ��� ���ӽ����̽� �̸�ó�� �ﰢ�� �������� ���� ���θ� �����ϴµ� 
	// ���⼭�� �簢���� ������ ���� ���ΰ� �ʿ��ϹǷ� �ﰢ�� �ΰ��� Ȯ���Ѵ�.

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
	ShowCursor(false);

	this->GetTransform().SetLocalScale(float4::One);
	this->GetTransform().SetWorldScale(float4::One);

	defaultPointerRenderer_ = CreateComponent<GameEngineUIRenderer>();
	defaultPointerRenderer_->SetPivot(PivotMode::LeftTop);
	defaultPointerRenderer_->GetTransform().SetWorldScale(20, 28, 1);
	defaultPointerRenderer_->SetTexture("CursorSprite.png");

	crossHairRenderer_ = CreateComponent<GameEngineUIRenderer>();
	crossHairRenderer_->GetTransform().SetWorldScale(32, 32, 1);
	crossHairRenderer_->SetTexture("CrossHair.png");
	crossHairRenderer_->Off();

	aimLineRenderer_ = CreateComponent<GameEngineUIRenderer>();
	aimLineRenderer_->GetTransform().SetWorldScale(512, 512, 1);
	aimLineRenderer_->SetTexture("AimLine.png");
	aimLineRenderer_->Off();
}

void Mouse::Update(float _DeltaTime)
{
	//�����ʿ����� ����.
	if (ProjectionMode::Orthographic == this->GetLevel()->GetMainCamera()->GetProjectionMode())
	{
		this->GetTransform().SetWorldPosition(
			this->GetLevel()->GetMainCamera()->GetMousePositionInViewSpace()
		);

		//defaultPointerRenderer_->GetTransform().SetWorldPosition(
		//	this->GetLevel()->GetUICamera()->GetMousePositionInWorldSpace()
		//);

		if (true == isAiming_)	//Ȱ��ȭ�� �÷��̾� ���� �߿� ��â ���� ���ϴ� �������� ����ü�� ������ ���Ⱑ �ִ� ���.
		{
			aimLineRenderer_->GetTransform().SetWorldPosition(
				this->GetLevel()->GetMainCamera()->ConvertWorldPositionToViewPosition(pivotWorldPosition_)
			);
			//���Ӷ��� �������� �߽����� ����ش�. �߽��� ��ġ�� �ܺο��� �÷��̾� ������ǥ�� �־��� ��.
			
			float4 aimingVector = this->GetTransform().GetWorldPosition() - aimLineRenderer_->GetTransform().GetWorldPosition();
			//���Ӷ����� ���ؾ� �� ���� ����.

			aimingVector.z = 0.f;
			//2D �������θ� ������ ���̹Ƿ� z���� 0���� ���� ������ ���δ�.

			aimingVector /= aimingVector.Length();
			//����ȭ.

			aimLineAngle_ = 0;
			//���Ӷ����� ����. 0�̸� ���Ӷ����� (0, 1, 0) ������ ���Ѵ�.

			if (0 < aimingVector.x)
			{
				aimLineAngle_ = -acosf(aimingVector.y) * GameEngineMath::RadianToDegree;
				//�� �κ��� ������ ���Ӷ����� ���������� �Ѿ�� �ʴ´�.
			}
			else
			{
				aimLineAngle_ = acosf(aimingVector.y) * GameEngineMath::RadianToDegree;
			}

			aimLineRenderer_->GetTransform().SetWorldRotation(0.f, 0.f, aimLineAngle_);
		}
	}
	//�����, Ŭ����������� ����.
	else 
	{
		if (true == isAiming_)
		{
			MsgBoxAssert("���콺������ ������ ��ȯ�� �����ʿ����� �ǹ� �ִ� ����Դϴ�.");
			return;
		}

		this->GetTransform().SetWorldPosition(
			this->GetLevel()->GetUICamera()->GetMousePositionInWorldSpace()
		);

		defaultPointerRenderer_->GetTransform().SetWorldPosition(
			this->GetLevel()->GetUICamera()->GetMousePositionInWorldSpace()
		);

		//����ī�޶� ���������϶��� ���콺������ ���Ϳ� ������ ��ġ ����ִ°� �ܿ� Ư���� �� ���� ����.
	}
}

void Mouse::End()
{
	//DirectX::XMPlaneIntersectLine();
	//DirectX::TriangleTests::Intersects();
}
