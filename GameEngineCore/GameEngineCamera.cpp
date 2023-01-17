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
#include "GameEngineStructuredBuffer.h"
#include "GameEngineInstancingRenderer.h"

GameEngineCamera::GameEngineCamera()
	: size_(GameEngineWindow::GetInst().GetScale()),
	projectionMode_(ProjectionMode::Perspective),
	nearZ_(1.f),
	farZ_(100000.f),
	fovAngleY_(60.f),
	conclusionRenderTarget_(nullptr),
	forwardRenderTarget_(nullptr),
	deferredRenderTarget_(nullptr),
	geometryBufferRenderTarget_(nullptr),
	shadowDepthRenderTarget_(nullptr),
	lightRatioBufferRenderTarget_(nullptr),
	lightDataBufferRenderTarget_(nullptr),
	lightRatioRenderUnit_(nullptr),
	lightDataRenderUnit_(nullptr),
	mergeRenderUnit_(nullptr)
{
	viewportDesc_.TopLeftX = 0;
	viewportDesc_.TopLeftY = 0;
	viewportDesc_.Width = size_.x;
	viewportDesc_.Height = size_.y;
	viewportDesc_.MinDepth = 0.f;
	viewportDesc_.MaxDepth = 1.f;	//<-1.f이 대입되어 MinDepth와 격차가 생겨야 깊이테스트를 제대로 할 수 있다.

	viewportMatrix_.Viewport(size_.x, size_.y, 0.f, 0.f, 0.f, 1.f);
}

GameEngineCamera::~GameEngineCamera()
{
	if (nullptr != lightRatioRenderUnit_)
	{
		delete lightRatioRenderUnit_;
		lightRatioRenderUnit_ = nullptr;
	}

	if (nullptr != lightDataRenderUnit_)
	{
		delete lightDataRenderUnit_;
		lightDataRenderUnit_ = nullptr;
	}
	
	if (nullptr != mergeRenderUnit_)
	{
		delete mergeRenderUnit_;
		mergeRenderUnit_ = nullptr;
	}
}

float4 GameEngineCamera::ConvertWorldPositionToScreenPosition(const float4& _worldPosition)
{
	float4 position = _worldPosition;

	position *= this->viewMatrix_;			//position에 뷰행렬 적용, 뷰공간 좌표로 변경.
	position *= this->projectionMatrix_;	//position에 투영행렬 적용, 투영공간 좌표로 변경.
	position /= position.w;					//position.w에 저장된 pos의 상대z값만큼 position값 축소.

	position *= this->viewportMatrix_;		//position에 뷰포트행렬 적용.

	return position;
}

float4 GameEngineCamera::ConvertWorldPositionToViewPosition(const float4& _worldPosition)
{
	float4 position = _worldPosition;
	position *= this->viewMatrix_;			//position에 뷰행렬 적용, 뷰공간 좌표로 변경.
	return position;
}

float4 GameEngineCamera::GetMousePositionInScreen()
{
	POINT pointerPosition;
	if (false == GetCursorPos(&pointerPosition))
		//화면 전체 기준 마우스 포인터의 좌표를 윈도우 스크린 좌표(좌상단 0, 0)로 반환하는 함수.
	{
		MsgBoxAssert("마우스 포인터 좌표를 얻어오는데 실패했습니다.");
		return float4::Zero;
	}

	if (false == ScreenToClient(	//화면 전체 기준 마우스 포인터 좌표를 특정 윈도우 기준 좌표로 변환하는 함수.
		GameEngineWindow::GetInst().GetHWND(),	//마우스 포인터 좌표를 알려고 하는 윈도우의 핸들.
		&pointerPosition	//변환할 화면 전체기준 마우스 포인터 좌표.
	))
	{
		MsgBoxAssert("마우스 포인터 좌표를 변환하는데 실패했습니다.");
		return float4::Zero;
	}

	return float4(static_cast<float>(pointerPosition.x), static_cast<float>(pointerPosition.y));
}

float4 GameEngineCamera::GetMousePositionInViewSpace()
{
	POINT pointerPosition;
	if (false == GetCursorPos(&pointerPosition))
		//화면 전체 기준 마우스 포인터의 좌표를 윈도우 스크린 좌표(좌상단 0, 0)로 반환하는 함수.
	{
		MsgBoxAssert("마우스 포인터 좌표를 얻어오는데 실패했습니다.");
		return float4();
	}

	if (false == ScreenToClient(	//화면 전체 기준 마우스 포인터 좌표를 특정 윈도우 기준 좌표로 변환하는 함수.
		GameEngineWindow::GetInst().GetHWND(),	//마우스 포인터 좌표를 알려고 하는 윈도우의 핸들.
		&pointerPosition)	//화면 전체기준 마우스 포인터 좌표.
		)
	{
		MsgBoxAssert("마우스 포인터 좌표를 변환하는데 실패했습니다.");
		return float4();
	}

	float4 pointerPos = float4(static_cast<float>(pointerPosition.x), static_cast<float>(pointerPosition.y));

	pointerPos *= this->viewportMatrix_.InverseReturn();
	//마우스의 윈도우 좌표에 뷰포트행렬의 역행렬 적용, 투영공간좌표로 변환.

	pointerPos *= this->projectionMatrix_.InverseReturn();
	//마우스의 투영공간 좌표에 투영행렬의 역행렬 적용, 뷰공간좌표로 변환.

	return pointerPos;
}

float4 GameEngineCamera::GetMousePositionInWorldSpace()
{
	POINT pointerPosition;
	if (false == GetCursorPos(&pointerPosition))
		//화면 전체 기준 마우스 포인터의 좌표를 윈도우 스크린 좌표(좌상단 0, 0)로 반환하는 함수.
	{
		MsgBoxAssert("마우스 포인터 좌표를 얻어오는데 실패했습니다.");
		return float4();
	}

	if (false == ScreenToClient(	//화면 전체 기준 마우스 포인터 좌표를 특정 윈도우 기준 좌표로 변환하는 함수.
		GameEngineWindow::GetInst().GetHWND(),	//마우스 포인터 좌표를 알려고 하는 윈도우의 핸들.
		&pointerPosition)	//화면 전체기준 마우스 포인터 좌표.
	)
	{
		MsgBoxAssert("마우스 포인터 좌표를 변환하는데 실패했습니다.");
		return float4();
	}

	float4 pointerPos = float4(static_cast<float>(pointerPosition.x), static_cast<float>(pointerPosition.y));

	pointerPos *= this->viewportMatrix_.InverseReturn();
	//마우스의 윈도우 좌표에 뷰포트행렬의 역행렬 적용, 투영공간좌표로 변환.

	pointerPos *= this->projectionMatrix_.InverseReturn();
	//마우스의 투영공간 좌표에 투영행렬의 역행렬 적용, 뷰공간좌표로 변환.

	pointerPos *= this->viewMatrix_.InverseReturn();
	//마우스의 뷰공간 좌표에 뷰행렬의 역행렬 적용.

	pointerPos /= pointerPos.w;
	//뷰변환 투영변환을 거치며 적용되었던 w값만큼 xyz값이 확장되어 나오므로,
	// w에 저장된 거리비례 축소비율만큼 마우스 좌표벡터를 나누어줘야 한다.

	//원래 원근 개념이 없던 마우스의 좌표가 이 과정까지 거치면, 
	// 이 카메라의 월드좌표에서 뷰공간 z++방향으로 nearZ_만큼, 종횡비를 유지하며 멀어진 지점에 있는 월드좌표가 된다.

	return pointerPos;
}

float4 GameEngineCamera::GetRayTowardMousePointer()
{
	return (GetMousePositionInWorldSpace() - GetTransform().GetWorldPosition()).Normalize3DReturn();
	//마우스포인터 월드좌표 - 카메라 월드좌표 -> 레이 방향벡터.
}

void GameEngineCamera::SetCameraOrder(CameraOrder _order)
{
	GetActor()->GetLevel()->PushCamera(this, _order);
}

GameEngineInstancingRenderer& GameEngineCamera::GetInstancingRenderer(const std::string& _name)
{
	return allInstancingRenderers_[_name];
}

void GameEngineCamera::PushLighting(GameEngineLighting* _newLighting)
{
	if (true == allLightings_.contains(_newLighting))
	{
		MsgBoxAssert("이미 있는 조명입니다.");
		return;
	}

	allLightings_.insert(_newLighting);
}

void GameEngineCamera::Start()
{
	conclusionRenderTarget_ = GameEngineRenderTarget::Create();
	conclusionRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero	//float4::Black
	);
	conclusionRenderTarget_->SetDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());
	//최종 렌더타겟 생성 및 초기화. 깊이스텐실뷰는 백버퍼 렌더타겟의 것을 가져온다.

	forwardRenderTarget_ = GameEngineRenderTarget::Create();
	forwardRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	forwardRenderTarget_->SetDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());
	//포워드렌더링용 렌더타겟 생성 및 초기화. 깊이스텐실뷰는 백버퍼 렌더타겟의 것을 가져온다.

	deferredRenderTarget_ = GameEngineRenderTarget::Create();
	deferredRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	deferredRenderTarget_->SetDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());
	//디퍼드렌더링용 렌더타겟 생성 및 초기화. 깊이스텐실뷰는 백버퍼 렌더타겟의 것을 가져온다.


	geometryBufferRenderTarget_ = GameEngineRenderTarget::Create();
	//지오메트리 버퍼 렌더타겟 생성.

	geometryBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	//지오메트리 버퍼 렌더타겟에 오브젝트 표면의 기본 색상값 정보를 저장할 텍스처 생성.

	geometryBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	//지오메트리 버퍼 렌더타겟에 윈도우 내 오브젝트 표면의 뷰공간 좌표정보를 저장할 텍스처 생성.

	geometryBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	//지오메트리 버퍼 렌더타겟에 윈도우 내 오브젝트들의 뷰공간 표면 법선벡터 정보를 저장할 텍스처 생성.

	geometryBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT,	//4색이 다 필요한게 아니라 0~1 사이 오브젝트 깊이값만 있으면 충분하므로 이 포맷으로 설정.
		float4::Red
	);
	//지오메트리 버퍼 렌더타겟에 윈도우 내 오브젝트들의 깊이 정보를 저장할 텍스처 생성.

	geometryBufferRenderTarget_->SetDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());
	//지오메트리 버퍼 렌더타겟의 깊이스텐실뷰는 백버퍼 렌더타겟의 것을 가져온다.


	shadowDepthRenderTarget_ = GameEngineRenderTarget::Create();
	shadowDepthRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT_R32_FLOAT,	//4색이 다 필요한게 아니라 0~1 사이 그림자 깊이값만 있으면 충분하므로 이 포맷으로 설정.
		float4::Red
	);
	//그림자 깊이정보를 받을 렌더타겟뷰겸 셰이더리소스뷰 생성.


	lightRatioBufferRenderTarget_ = GameEngineRenderTarget::Create();
	lightRatioBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT_R32_FLOAT,	//4색이 다 필요한게 아니라 0~1 사이 빛 적용 배율값만 있으면 충분하므로 이 포맷으로 설정.
		float4::Red
	);
	//픽셀별 빛 적용 배율을 저장할 렌더타겟뷰겸 셰이더리소스뷰 생성.


	lightDataBufferRenderTarget_ = GameEngineRenderTarget::Create();
	//빛정보 저장 버퍼 렌더타겟 생성.

	lightDataBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	//빛정보 저장 버퍼 렌더타겟에 난반사광(Diffuse Light) 정보를 저장할 텍스처 생성. 

	lightDataBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	//빛정보 저장 버퍼 렌더타겟에 정반사광(Specular Light) 정보를 저장할 텍스처 생성. 

	lightDataBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	//빛정보 저장 버퍼 렌더타겟에 환경광(Ambient Light) 정보를 저장할 텍스처 생성. 
	//빛은 z값 관계없이 적용되므로 깊이스텐실뷰를 가져올 필요가 없다.

	lightRatioRenderUnit_ = new GameEngineRenderUnit();
	lightRatioRenderUnit_->SetMesh("Fullrect");
	lightRatioRenderUnit_->SetMaterial("CalLightRatio");
	lightRatioRenderUnit_->GetShaderResourceHelper().SetSampler("POINTCLAMP", "POINTCLAMP");
	lightRatioRenderUnit_->GetShaderResourceHelper().SetTexture("ObjectDepthTexture", geometryBufferRenderTarget_->GetRenderTargetTexture(3));
	lightRatioRenderUnit_->GetShaderResourceHelper().SetTexture("ShadowDepthTexture", shadowDepthRenderTarget_->GetRenderTargetTexture(0));


	lightDataRenderUnit_ = new GameEngineRenderUnit();
	lightDataRenderUnit_->SetMesh("Fullrect");
	lightDataRenderUnit_->SetMaterial("CalDeferredLight");
	lightDataRenderUnit_->GetShaderResourceHelper().SetConstantBuffer_Link("AllLightingDatas", this->lightingDatasInst_);
	lightDataRenderUnit_->GetShaderResourceHelper().SetTexture("PositionTexture", geometryBufferRenderTarget_->GetRenderTargetTexture(1));
	lightDataRenderUnit_->GetShaderResourceHelper().SetTexture("NormalTexture", geometryBufferRenderTarget_->GetRenderTargetTexture(2));
	lightDataRenderUnit_->GetShaderResourceHelper().SetTexture("LightRatioTexture", lightRatioBufferRenderTarget_->GetRenderTargetTexture(0));


	mergeRenderUnit_ = new GameEngineRenderUnit();
	mergeRenderUnit_->SetMesh("Fullrect");
	mergeRenderUnit_->SetMaterial("CalDeferredMerger");
	mergeRenderUnit_->GetShaderResourceHelper().SetTexture("ColorTexture", geometryBufferRenderTarget_->GetRenderTargetTexture(0));
	mergeRenderUnit_->GetShaderResourceHelper().SetTexture("DiffuseLightTexture", lightDataBufferRenderTarget_->GetRenderTargetTexture(0));
	mergeRenderUnit_->GetShaderResourceHelper().SetTexture("SpecularLightTexture", lightDataBufferRenderTarget_->GetRenderTargetTexture(1));
	mergeRenderUnit_->GetShaderResourceHelper().SetTexture("AmbientLightTexture", lightDataBufferRenderTarget_->GetRenderTargetTexture(2));

	GameEngineDevice::GetDC()->RSSetViewports(//파이프라인에 뷰포트들을 세팅하는 함수.
		1,					//설정할 뷰포트 개수.
		&viewportDesc_		//뷰포트 구조체 배열의 주소값.
	);
}

bool ZSort(GameEngineRenderer* _rendererA, GameEngineRenderer* _rendererB)
{
	//
	return _rendererA->GetTransform().GetWorldPosition().z > _rendererB->GetTransform().GetWorldPosition().z;
}

void GameEngineCamera::Render(float _deltaTime)
{
	//GameEngineDevice::GetContext()->RSSetViewports(//파이프라인에 뷰포트들을 세팅하는 함수.
	//	1,					//설정할 뷰포트 개수.
	//	&viewportDesc_		//뷰포트 구조체 배열의 주소값.
	//);

	//월드공간의 오브젝트들을 재배치할 뷰행렬을 구한다.
	viewMatrix_.LookToLH(
		this->GetParent<GameEngineActor>()->GetTransform().GetLocalPosition(),
		this->GetParent<GameEngineActor>()->GetTransform().GetForwardVector(),
		this->GetParent<GameEngineActor>()->GetTransform().GetUpVector()
	);

	//투영모드에 맞게 오브젝트들을 축소할 투영행렬을 구한다.
	switch (projectionMode_)
	{
	case ProjectionMode::Perspective:
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

	case ProjectionMode::Orthographic:
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

	lightingDatasInst_.lightingCount_ = static_cast<int>(allLightings_.size());
	int lightingIndex = 0;
	for (GameEngineLighting* singleLighting : allLightings_)
	{
		singleLighting->UpdataLightingData(this);
		lightingDatasInst_.lightings_[lightingIndex++] = singleLighting->GetLightingData();
	}


	{	
		//포워드 렌더링.

		forwardRenderTarget_->Clear();
		forwardRenderTarget_->SetRenderTarget();
		//포워드 렌더타겟 세팅 및 초기화.

		for (std::pair<const int, std::list<GameEngineRenderer*>>& rendererGroup : allRenderers_)
		{
			float scaleTime = GameEngineTime::GetInst().GetDeltaTime(rendererGroup.first);

			std::list<GameEngineRenderer*>& sortingRendererList = rendererGroup.second;
			sortingRendererList.sort(ZSort);

			for (GameEngineRenderer* const renderer : rendererGroup.second)
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

				renderer->Render(scaleTime);
				//뷰포트행렬을 포함한 모든 행렬 계산을 거친 결과대로 메쉬를 화면에 그린다.
			}
		}

		for (std::map<std::string, GameEngineInstancingRenderer>::iterator iter = allInstancingRenderers_.begin();
			iter != allInstancingRenderers_.end(); ++iter)
		{
			iter->second.Render(_deltaTime, this->viewMatrix_, this->projectionMatrix_);
			//내부에서 자체적으로 트랜스폼 행렬계산을 해야 하므로 뷰행렬, 투영행렬을 넣어준다.
		}
	}


	{
		//디퍼드 렌더링.

		geometryBufferRenderTarget_->Clear(false);
		//gBuffer 렌더타겟의 텍스처들만 초기화한다. 깊이스텐실 버퍼는 초기화하지 않는다.
		//깊이스텐실버퍼까지 초기화하면 오브젝트들의 z값 정보가 전부 날아간다.

		geometryBufferRenderTarget_->SetRenderTarget();
		//gBuffer 렌더타겟을 DC에 연결.

		for (std::pair<const int, std::list<GameEngineRenderer*>>& rendererGroup : allRenderers_)
		{
			float scaleTime = GameEngineTime::GetInst().GetDeltaTime(rendererGroup.first);

			for (GameEngineRenderer* const renderer : rendererGroup.second)
				//이 위치의 const는 renderer가 가리키는 메모리 위치를 변경할 수 없게 하겠다는 의미이다. 
				//하지만 renderer가 가리키는 메모리가 가진 값은 얼마든지 변경 가능하다.
			{
				if (false == renderer->IsUpdate())
				{
					continue;
				}

				renderer->renderOptionInst_.deltaTime_ = _deltaTime;
				renderer->renderOptionInst_.sumDeltaTime_ += _deltaTime;
				
				//renderer->GetTransform().SetViewMatrix(viewMatrix_);
				//renderer->GetTransform().SetProjectionMatrix(projectionMatrix_);
				////카메라에 저장된 뷰행렬과 투영행렬을 렌더러의 트랜스폼에 저장한다.
				//
				//renderer->GetTransform().CalculateWorldViewProjection();
				//크자이공부 변환을 거친 월드행렬에 뷰행렬과 투영행렬까지 계산한다.
				////행렬 변환은 이미 위에서 했으므로 또다시 하지 않는다.

				renderer->DeferredRender(scaleTime);
				//geometryBufferRenderTarget_의 네 렌더타겟뷰들에 오브젝트의 원래 색상, 오브젝트 표면 모든 점들의 뷰공간 위치, 
				// 오브젝트 표면 모든 점들의 뷰공간 법선벡터, 오브젝트의 깊이값을 렌더링 형식으로 저장한다. 
			}
		}

		for (std::map<std::string, GameEngineInstancingRenderer>::iterator iter = allInstancingRenderers_.begin();
			iter != allInstancingRenderers_.end(); ++iter)
		{
			iter->second.DeferredRender(_deltaTime, this->viewMatrix_, this->projectionMatrix_);
		}
	}
	


	{
		//디퍼드 그림자 렌더링.

		shadowDepthRenderTarget_->Clear();
		shadowDepthRenderTarget_->SetRenderTarget();

		for (std::map<std::string, GameEngineInstancingRenderer>::iterator iter = allInstancingRenderers_.begin();
			iter != allInstancingRenderers_.end(); ++iter)
		{
			iter->second.RenderShadow(_deltaTime, this->viewMatrix_, this->projectionMatrix_);
		}
		//플레이어가 자기 그림자에 가려지는것에 대한 임시 조치.

		for (std::pair<const int, std::list<GameEngineRenderer*>>& rendererGroup : allRenderers_)
		{
			float scaleTime = GameEngineTime::GetInst().GetDeltaTime(rendererGroup.first);

			std::list<GameEngineRenderer*>& sortingRendererList = rendererGroup.second;
			sortingRendererList.sort(ZSort);

			for (GameEngineRenderer* const renderer : rendererGroup.second)
				//이 위치의 const는 renderer가 가리키는 메모리 위치를 변경할 수 없게 하겠다는 의미이다. 
				//하지만 renderer가 가리키는 메모리가 가진 값은 얼마든지 변경 가능하다.
			{
				if (false == renderer->IsUpdate())
				{
					continue;
				}

				renderer->renderOptionInst_.deltaTime_ = _deltaTime;
				renderer->renderOptionInst_.sumDeltaTime_ += _deltaTime;

				//renderer->GetTransform().SetViewMatrix(this->viewMatrix_);
				//renderer->GetTransform().SetProjectionMatrix(this->projectionMatrix_);
				////카메라에 저장된 뷰행렬과 투영행렬을 렌더러의 트랜스폼에 저장한다.

				//renderer->GetTransform().CalculateWorldViewProjection();
				//크자이공부 변환을 거친 월드행렬에 뷰행렬과 투영행렬까지 계산한다.
				////행렬 변환은 이미 위에서 했으므로 또다시 하지 않는다.

				renderer->RenderShadow(scaleTime);
				//shadowDepthRenderTarget_의 렌더타겟뷰에 그림자의 깊이값을 저장하게 한다.
			}
		}
	}


	lightRatioBufferRenderTarget_->Clear();
	lightRatioBufferRenderTarget_->Effect(*lightRatioRenderUnit_);
	//그림자의 깊이값과 오브젝트의 깊이값을 비교해서 그림자가 오브젝트보다 더 앞에 나온다면 
	// 그림자가 그려지는 픽셀에는 난반사광을 절반만 적용되게 한다.


	//렌더링 결과 통합.

	lightDataBufferRenderTarget_->Clear();
	lightDataBufferRenderTarget_->Effect(*lightDataRenderUnit_);

	deferredRenderTarget_->Clear();
	deferredRenderTarget_->Effect(*mergeRenderUnit_);



	conclusionRenderTarget_->Clear();
	//최종 렌더타겟의 렌더타겟뷰, 깊이스텐실뷰 초기화.

	conclusionRenderTarget_->Merge(forwardRenderTarget_);
	//포워드 렌더타겟에 저장된 색상값들을 최종 렌더타겟뷰로 복사한다.

	conclusionRenderTarget_->Merge(deferredRenderTarget_);
	//디퍼드 렌더타겟에 저장된 색상값들을 최종 렌더타겟뷰로 복사한다.


	//이렇게 합쳐진 색상값 정보들은 게임엔진레벨의 Render()함수에서 백버퍼 렌더타겟에 다시한번 합쳐진다. 
}

void GameEngineCamera::PushRenderer(GameEngineRenderer* _renderer)
{
	allRenderers_[_renderer->GetOrder()].push_back(_renderer);
	//게임엔진카메라의 소멸자가 호출되지 않으면, allRenderers 푸시백 과정에서 새로 동적할당된 노드들이 해제되지 
	// 않고 그대로 남아 전부 메모리 릭이 된다.
}

void GameEngineCamera::Release(float _deltaTime)
{
	for (std::map<int, std::list<GameEngineRenderer*>>::iterator mapIter = allRenderers_.begin();
		mapIter != allRenderers_.end(); mapIter++)
	{
		for (std::list<GameEngineRenderer*>::iterator listIter = mapIter->second.begin();
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
	UpdateMouseDirection();
}

void GameEngineCamera::OverRenderer(GameEngineCamera* _nextCamera)
{
	if (nullptr == _nextCamera)
	{
		MsgBoxAssert("nextCamera가 없습니다.");
		return;
	}

	std::map<int, std::list<GameEngineRenderer*>>::iterator startGroupIter = allRenderers_.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator endGroupIter = allRenderers_.end();

	for (; startGroupIter != endGroupIter; ++startGroupIter)
	{
		std::list<GameEngineRenderer*>& group = startGroupIter->second;

		std::list<GameEngineRenderer*>::iterator groupStart = group.begin();
		std::list<GameEngineRenderer*>::iterator groupEnd = group.end();

		for (; groupStart != groupEnd; )
		{
			GameEngineActor* root = (*groupStart)->GetRoot<GameEngineActor>();

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

void GameEngineCamera::ChangeRenderingOrder(GameEngineRenderer* _renderer, int _newRenderingOrder)
{
	this->allRenderers_[_renderer->GetRenderingOrder()].remove(_renderer);

	_renderer->renderingOrder_ = _newRenderingOrder;

	this->allRenderers_[_renderer->GetRenderingOrder()].push_back(_renderer);
}

void GameEngineCamera::UpdateMouseDirection()
{
	float4 currentMousePosition = GetMousePositionInViewSpace();
	//현재 마우스포인터의 위치를 알아낸다.

	mouseDirection_ = currentMousePosition - prevMousePosition_;
	//현재 마우스포인터 위치 - 이전 마우스포인터 위치 = 마우스포인터의 이동방향.

	prevMousePosition_ = currentMousePosition;
	//이전 마우스포인터 위치 갱신.
}
