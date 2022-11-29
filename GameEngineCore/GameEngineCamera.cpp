#include "PreCompile.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineRenderer.h"
#include "GameEngineActor.h"
#include "GameEngineDevice.h"
#include "GameEngineMaterial.h"
#include "GameEngineVertexShader.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexes.h"
#include "GameEngineInstancingBuffer.h"
#include "GameEngineInstancing.h"
#include "GameEngineStructuredBuffer.h"

GameEngineCamera::GameEngineCamera()
	: size_(GameEngineWindow::GetScale()),
	projectionMode_(CameraProjectionMode::Perspective),
	nearZ_(0.1f),
	farZ_(1000000.f),
	fovAngleY_(60.f),
	cameraRenderTarget_(nullptr)
{
	viewportDesc_.TopLeftX = 0;
	viewportDesc_.TopLeftY = 0;
	viewportDesc_.Width = size_.x;
	viewportDesc_.Height = size_.y;
	viewportDesc_.MinDepth = 0.0f;
	viewportDesc_.MaxDepth = 1.f;	//<-1.f이 대입되어 MinDepth와 격차가 생겨야 깊이테스트를 제대로 할 수 있다.

	viewportMatrix_.Viewport(size_.x, size_.y, 0, 0, 0, 1);
}

GameEngineCamera::~GameEngineCamera()
{
}

float4 GameEngineCamera::GetMouseScreenPosition()
{
	POINT pointerPosition;
	if (false == GetCursorPos(&pointerPosition))
		//화면 전체 기준 마우스 포인터의 좌표를 윈도우 스크린 좌표(좌상단 0, 0)로 반환하는 함수.
	{
		MsgBoxAssert("마우스 포인터 좌표를 얻어오는데 실패했습니다.");
		return float4::Zero;
	}

	if (false == ScreenToClient(	//화면 전체 기준 마우스 포인터 좌표를 특정 윈도우 기준 좌표로 변환하는 함수.
		GameEngineWindow::GetHWND(),	//마우스 포인터 좌표를 알려고 하는 윈도우의 핸들.
		&pointerPosition	//변환할 화면 전체기준 마우스 포인터 좌표.
	))
	{
		MsgBoxAssert("마우스 포인터 좌표를 변환하는데 실패했습니다.");
		return float4::Zero;
	}

	return float4(static_cast<float>(pointerPosition.x), static_cast<float>(pointerPosition.y));
}

float4 GameEngineCamera::GetMouseWorldPosition()
{
	POINT pointerPosition;
	if (false == GetCursorPos(&pointerPosition))
		//화면 전체 기준 마우스 포인터의 좌표를 윈도우 스크린 좌표(좌상단 0, 0)로 반환하는 함수.
	{
		MsgBoxAssert("마우스 포인터 좌표를 얻어오는데 실패했습니다.");
		return float4();
	}

	if (false == ScreenToClient(	//화면 전체 기준 마우스 포인터 좌표를 특정 윈도우 기준 좌표로 변환하는 함수.
		GameEngineWindow::GetHWND(),	//마우스 포인터 좌표를 알려고 하는 윈도우의 핸들.
		&pointerPosition	//변환할 화면 전체기준 마우스 포인터 좌표.
	))
	{
		MsgBoxAssert("마우스 포인터 좌표를 변환하는데 실패했습니다.");
		return float4();
	}

	float4 pointerPos = float4(static_cast<float>(pointerPosition.x), static_cast<float>(pointerPosition.y));

	//float4x4 invertedViewportMatrix;
	//invertedViewportMatrix.Viewport(size_.x, size_.y, 0.f, 0.f, 0.f, 1.f);
	//invertedViewportMatrix.Inverse();

	//pointerPos *= invertedViewportMatrix;

	pointerPos *= this->viewportMatrix_.InverseReturn();

	//float4x4 invertedProjectionMatrix = projectionMatrix_.InverseReturn();
	//pointerPos *= invertedProjectionMatrix;

	pointerPos *= this->projectionMatrix_.InverseReturn();

	return pointerPos;
}

float4 GameEngineCamera::GetMouseWorldPositionToActor()
{
	return this->GetTransform().GetWorldPosition() + GetMouseWorldPosition();
}

float4 GameEngineCamera::GetWorldPositionToScreenPosition(const float4& _worldPosition)
{
	float4 pos = _worldPosition;

	pos *= this->viewMatrix_;			//pos에 뷰행렬 적용, 뷰스페이스 좌표로 변경.
	pos *= this->projectionMatrix_;		//pos에 투영행렬 적용, 
	pos /= pos.w;						//pos.w에 저장된 pos의 상대z값만큼 pos값 축소.
	//

	pos *= this->viewportMatrix_;		//pos에 뷰포트행렬 적용.

	return pos;
}

void GameEngineCamera::SetCameraOrder(CameraOrder _order)
{
	GetActor()->GetLevel()->PushCamera(std::dynamic_pointer_cast<GameEngineCamera>(shared_from_this()), _order);
}

GameEngineInstancing& GameEngineCamera::GetInstancing(const std::string& _name)
{
	return instancingMap_[_name];	//없으면 생성 삽입 반환, 있으면 찾아서 반환.
}

void GameEngineCamera::Start()
{
	cameraRenderTarget_ = GameEngineRenderTarget::Create();
	cameraRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero	//float4::Black
	);

	cameraRenderTarget_->SetDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());

	GameEngineDevice::GetContext()->RSSetViewports(//파이프라인에 뷰포트들을 세팅하는 함수.
		1,					//설정할 뷰포트 개수.
		&viewportDesc_		//뷰포트 구조체 배열의 주소값.
	);
}

bool ZSort(std::shared_ptr<GameEngineRenderer> _rendererA, std::shared_ptr<GameEngineRenderer> _rendererB)
{
	//
	return _rendererA->GetTransform().GetWorldPosition().z > _rendererB->GetTransform().GetWorldPosition().z;
}

bool YSort(std::shared_ptr<GameEngineRenderer> _rendererA, std::shared_ptr<GameEngineRenderer> _rendererB)
{
	//
	return _rendererA->GetTransform().GetWorldPosition().y > _rendererB->GetTransform().GetWorldPosition().y;
}

void GameEngineCamera::Render(float _deltaTime)
{
	cameraRenderTarget_->Clear();
	//이 카메라의 렌더타겟뷰, 깊이스텐실뷰 초기화.

	cameraRenderTarget_->Setting();
	//초기화한 렌더타겟뷰를 렌더링 파이프라인에 연결.

	//GameEngineDevice::GetContext()->RSSetViewports(//파이프라인에 뷰포트들을 세팅하는 함수.
	//	1,					//설정할 뷰포트 개수.
	//	&viewportDesc_		//뷰포트 구조체 배열의 주소값.
	//);

	//오브젝트들을 재배치할 뷰행렬을 구한다.
	viewMatrix_.LookToLH(
		this->GetParent<GameEngineActor>()->GetTransform().GetLocalPosition(),
		this->GetParent<GameEngineActor>()->GetTransform().GetForwardVector(),
		this->GetParent<GameEngineActor>()->GetTransform().GetUpVector()
	);

	//투영모드에 맞게 오브젝트들을 축소할 투영행렬을 구한다.
	switch (projectionMode_)
	{
	case CameraProjectionMode::Perspective:
		//projection_.ProjectPerspectiveLH(
		//	planeSize_.x * 0.0001f,	 //근평면의 가로길이.
		//	planeSize_.y * 0.0001f,	 //근평면의 세로길이.  
		//	nearZ_,
		//	farZ_
		//);
		//근평면을 직접 계산해서 넣어줘야 하는 ProjectPerspectiveLH()보다 
		//화각과 종횡비, 적절한 윈도우크기만 넣어주면 알아서 계산하는 ProjectPerspectiveFovLH()가 더 편하다.


		projectionMatrix_.ProjectPerspectiveFovLH(
			fovAngleY_ * GameEngineMath::DegreeToRadian,
			size_.x / size_.y,
			nearZ_,
			farZ_
		);
		break;

	case CameraProjectionMode::Orthographic:
		projectionMatrix_.ProjectOrthographicLH(
			size_.x,
			size_.y,
			nearZ_,
			farZ_
		);
		break;


	default:
		break;
	}

	for (std::pair<const int, std::list<std::shared_ptr<GameEngineRenderer>>>& rendererGroup : allRenderers_)
	{
		float scaleTime = GameEngineTime::GetDeltaTime(rendererGroup.first);

		std::list<std::shared_ptr<GameEngineRenderer>>& sortingRendererList = rendererGroup.second;
		sortingRendererList.sort(ZSort);

		for (std::shared_ptr<GameEngineRenderer> const renderer : rendererGroup.second)
			//이 위치의 const는 renderer가 가리키는 메모리 위치를 변경할 수 없게 하겠다는 의미이다. 
			//하지만 renderer가 가리키는 메모리가 가진 값은 얼마든지 변경 가능하다.
		{
			if (false == renderer->IsUpdate())
			{
				continue;
			}

			renderer->renderOptionInst_.deltaTime_ = _deltaTime;
			renderer->renderOptionInst_.sumDeltaTime_ += _deltaTime;

			renderer->GetTransform().SetViewMatrix(viewMatrix_);
			renderer->GetTransform().SetProjectionMatrix(projectionMatrix_);
			//카메라에 저장된 뷰행렬과 투영행렬을 렌더러의 트랜스폼에 저장한다.

			renderer->GetTransform().CalculateWorldViewProjection();
			//크자이공부 변환을 거친 월드행렬에 뷰행렬과 투영행렬까지 계산한다.
			
			if (false == float4x4::IsInViewFrustum(
				renderer->GetTransformData().worldViewProjectionMatrix_, 
				float4(renderer->renderOptionInst_.pivotPosX_, renderer->renderOptionInst_.pivotPosY_))
			)
			{
				//뷰스페이스 안에 4개 정점들 중 한개라도 들어오는 것들만 그린다.
				continue;
			}

			renderer->Render(scaleTime);
			//뷰포트행렬을 포함한 모든 행렬 계산을 거친 결과대로 메쉬를 화면에 그린다.
		}
	}

	for (std::unordered_map<std::string, GameEngineInstancing>::iterator iter = instancingMap_.begin();
		iter != instancingMap_.end(); ++iter)
	{

	}
}

void GameEngineCamera::PushRenderer(std::shared_ptr<GameEngineRenderer> _renderer)
{
	allRenderers_[_renderer->GetOrder()].push_back(_renderer);
	//게임엔진카메라의 소멸자가 호출되지 않으면, allRenderers 푸시백 과정에서 새로 동적할당된 노드들이 해제되지 
	// 않고 그대로 남아 전부 메모리 릭이 된다.
}

void GameEngineCamera::Release(float _deltaTime)
{
	for (std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>>::iterator mapIter = allRenderers_.begin();
		mapIter != allRenderers_.end(); mapIter++)
	{
		for (std::list<std::shared_ptr<GameEngineRenderer>>::iterator listIter = mapIter->second.begin();
			listIter != mapIter->second.end(); /*listIter++*/)
		{
			(*listIter)->ReleaseUpdate(_deltaTime);
			//deadTime_이 0이 된 렌더러들에게 사망 판정을 내린다.

			if (true == (*listIter)->IsDead())
			{
				//delete (*listIter);	//더이상 카메라에서 렌더러 삭제를 직접 하지 않는다.
				listIter = mapIter->second.erase(listIter);
				//대신 카메라의 allRenderers_ 리스트에서만 제거한다.
			}
			else
			{
				++listIter;
			}
		}
	}
}

void GameEngineCamera::Update(float _dletaTime)
{
	float4 currentMousePosition = GetMouseWorldPosition();
	//현재 마우스포인터의 위치를 알아낸다.

	currentMousePosition.w = 0.f;
	//w는 왜 굳이 0??

	mouseDirection_ = currentMousePosition - prevMousePosition_;
	//현재 마우스포인터 위치 - 이전 마우스포인터 위치 = 마우스포인터의 이동방향.

	prevMousePosition_ = currentMousePosition;
	//이전 마우스포인터 위치 갱신.
}

void GameEngineCamera::OverRenderer(std::shared_ptr<GameEngineCamera> _nextCamera)
{
	if (nullptr == _nextCamera)
	{
		MsgBoxAssert("nextCamera가 없습니다.");
		return;
	}

	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>>::iterator startGroupIter = allRenderers_.begin();
	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>>::iterator endGroupIter = allRenderers_.end();

	for (; startGroupIter != endGroupIter; ++startGroupIter)
	{
		std::list<std::shared_ptr<GameEngineRenderer>>& group = startGroupIter->second;

		std::list<std::shared_ptr<GameEngineRenderer>>::iterator groupStart = group.begin();
		std::list<std::shared_ptr<GameEngineRenderer>>::iterator groupEnd = group.end();

		for (; groupStart != groupEnd; )
		{
			std::shared_ptr<GameEngineActor> root = (*groupStart)->GetRoot<GameEngineActor>();

			if (true == root->isLevelOver_)
			{
				_nextCamera->allRenderers_[startGroupIter->first].push_back(*groupStart);
				groupStart = group.erase(groupStart);
			}
			else
			{
				++groupStart;
			}
		}
	}
}

void GameEngineCamera::ChangeRenderingOrder(std::shared_ptr<GameEngineRenderer> _renderer, int _newRenderingOrder)
{
	this->allRenderers_[_renderer->GetRenderingOrder()].remove(_renderer);

	_renderer->renderingOrder_ = _newRenderingOrder;

	this->allRenderers_[_renderer->GetRenderingOrder()].push_back(_renderer);
}
