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
	viewportDesc_.MaxDepth = 1.f;	//<-1.f�� ���ԵǾ� MinDepth�� ������ ���ܾ� �����׽�Ʈ�� ����� �� �� �ִ�.

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

	position *= this->viewMatrix_;			//position�� ����� ����, ����� ��ǥ�� ����.
	position *= this->projectionMatrix_;	//position�� ������� ����, �������� ��ǥ�� ����.
	position /= position.w;					//position.w�� ����� pos�� ���z����ŭ position�� ���.

	position *= this->viewportMatrix_;		//position�� ����Ʈ��� ����.

	return position;
}

float4 GameEngineCamera::ConvertWorldPositionToViewPosition(const float4& _worldPosition)
{
	float4 position = _worldPosition;
	position *= this->viewMatrix_;			//position�� ����� ����, ����� ��ǥ�� ����.
	return position;
}

float4 GameEngineCamera::GetMousePositionInScreen()
{
	POINT pointerPosition;
	if (false == GetCursorPos(&pointerPosition))
		//ȭ�� ��ü ���� ���콺 �������� ��ǥ�� ������ ��ũ�� ��ǥ(�»�� 0, 0)�� ��ȯ�ϴ� �Լ�.
	{
		MsgBoxAssert("���콺 ������ ��ǥ�� �����µ� �����߽��ϴ�.");
		return float4::Zero;
	}

	if (false == ScreenToClient(	//ȭ�� ��ü ���� ���콺 ������ ��ǥ�� Ư�� ������ ���� ��ǥ�� ��ȯ�ϴ� �Լ�.
		GameEngineWindow::GetInst().GetHWND(),	//���콺 ������ ��ǥ�� �˷��� �ϴ� �������� �ڵ�.
		&pointerPosition	//��ȯ�� ȭ�� ��ü���� ���콺 ������ ��ǥ.
	))
	{
		MsgBoxAssert("���콺 ������ ��ǥ�� ��ȯ�ϴµ� �����߽��ϴ�.");
		return float4::Zero;
	}

	return float4(static_cast<float>(pointerPosition.x), static_cast<float>(pointerPosition.y));
}

float4 GameEngineCamera::GetMousePositionInViewSpace()
{
	POINT pointerPosition;
	if (false == GetCursorPos(&pointerPosition))
		//ȭ�� ��ü ���� ���콺 �������� ��ǥ�� ������ ��ũ�� ��ǥ(�»�� 0, 0)�� ��ȯ�ϴ� �Լ�.
	{
		MsgBoxAssert("���콺 ������ ��ǥ�� �����µ� �����߽��ϴ�.");
		return float4();
	}

	if (false == ScreenToClient(	//ȭ�� ��ü ���� ���콺 ������ ��ǥ�� Ư�� ������ ���� ��ǥ�� ��ȯ�ϴ� �Լ�.
		GameEngineWindow::GetInst().GetHWND(),	//���콺 ������ ��ǥ�� �˷��� �ϴ� �������� �ڵ�.
		&pointerPosition)	//ȭ�� ��ü���� ���콺 ������ ��ǥ.
		)
	{
		MsgBoxAssert("���콺 ������ ��ǥ�� ��ȯ�ϴµ� �����߽��ϴ�.");
		return float4();
	}

	float4 pointerPos = float4(static_cast<float>(pointerPosition.x), static_cast<float>(pointerPosition.y));

	pointerPos *= this->viewportMatrix_.InverseReturn();
	//���콺�� ������ ��ǥ�� ����Ʈ����� ����� ����, ����������ǥ�� ��ȯ.

	pointerPos *= this->projectionMatrix_.InverseReturn();
	//���콺�� �������� ��ǥ�� ��������� ����� ����, �������ǥ�� ��ȯ.

	return pointerPos;
}

float4 GameEngineCamera::GetMousePositionInWorldSpace()
{
	POINT pointerPosition;
	if (false == GetCursorPos(&pointerPosition))
		//ȭ�� ��ü ���� ���콺 �������� ��ǥ�� ������ ��ũ�� ��ǥ(�»�� 0, 0)�� ��ȯ�ϴ� �Լ�.
	{
		MsgBoxAssert("���콺 ������ ��ǥ�� �����µ� �����߽��ϴ�.");
		return float4();
	}

	if (false == ScreenToClient(	//ȭ�� ��ü ���� ���콺 ������ ��ǥ�� Ư�� ������ ���� ��ǥ�� ��ȯ�ϴ� �Լ�.
		GameEngineWindow::GetInst().GetHWND(),	//���콺 ������ ��ǥ�� �˷��� �ϴ� �������� �ڵ�.
		&pointerPosition)	//ȭ�� ��ü���� ���콺 ������ ��ǥ.
	)
	{
		MsgBoxAssert("���콺 ������ ��ǥ�� ��ȯ�ϴµ� �����߽��ϴ�.");
		return float4();
	}

	float4 pointerPos = float4(static_cast<float>(pointerPosition.x), static_cast<float>(pointerPosition.y));

	pointerPos *= this->viewportMatrix_.InverseReturn();
	//���콺�� ������ ��ǥ�� ����Ʈ����� ����� ����, ����������ǥ�� ��ȯ.

	pointerPos *= this->projectionMatrix_.InverseReturn();
	//���콺�� �������� ��ǥ�� ��������� ����� ����, �������ǥ�� ��ȯ.

	pointerPos *= this->viewMatrix_.InverseReturn();
	//���콺�� ����� ��ǥ�� ������� ����� ����.

	pointerPos /= pointerPos.w;
	//�亯ȯ ������ȯ�� ��ġ�� ����Ǿ��� w����ŭ xyz���� Ȯ��Ǿ� �����Ƿ�,
	// w�� ����� �Ÿ���� ��Һ�����ŭ ���콺 ��ǥ���͸� ��������� �Ѵ�.

	//���� ���� ������ ���� ���콺�� ��ǥ�� �� �������� ��ġ��, 
	// �� ī�޶��� ������ǥ���� ����� z++�������� nearZ_��ŭ, ��Ⱦ�� �����ϸ� �־��� ������ �ִ� ������ǥ�� �ȴ�.

	return pointerPos;
}

float4 GameEngineCamera::GetRayTowardMousePointer()
{
	return (GetMousePositionInWorldSpace() - GetTransform().GetWorldPosition()).Normalize3DReturn();
	//���콺������ ������ǥ - ī�޶� ������ǥ -> ���� ���⺤��.
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
		MsgBoxAssert("�̹� �ִ� �����Դϴ�.");
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
	//���� ����Ÿ�� ���� �� �ʱ�ȭ. ���̽��ٽǺ�� ����� ����Ÿ���� ���� �����´�.

	forwardRenderTarget_ = GameEngineRenderTarget::Create();
	forwardRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	forwardRenderTarget_->SetDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());
	//�����巻������ ����Ÿ�� ���� �� �ʱ�ȭ. ���̽��ٽǺ�� ����� ����Ÿ���� ���� �����´�.

	deferredRenderTarget_ = GameEngineRenderTarget::Create();
	deferredRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	deferredRenderTarget_->SetDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());
	//���۵巻������ ����Ÿ�� ���� �� �ʱ�ȭ. ���̽��ٽǺ�� ����� ����Ÿ���� ���� �����´�.


	geometryBufferRenderTarget_ = GameEngineRenderTarget::Create();
	//������Ʈ�� ���� ����Ÿ�� ����.

	geometryBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	//������Ʈ�� ���� ����Ÿ�ٿ� ������Ʈ ǥ���� �⺻ ���� ������ ������ �ؽ�ó ����.

	geometryBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	//������Ʈ�� ���� ����Ÿ�ٿ� ������ �� ������Ʈ ǥ���� ����� ��ǥ������ ������ �ؽ�ó ����.

	geometryBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	//������Ʈ�� ���� ����Ÿ�ٿ� ������ �� ������Ʈ���� ����� ǥ�� �������� ������ ������ �ؽ�ó ����.

	geometryBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT,	//4���� �� �ʿ��Ѱ� �ƴ϶� 0~1 ���� ������Ʈ ���̰��� ������ ����ϹǷ� �� �������� ����.
		float4::Red
	);
	//������Ʈ�� ���� ����Ÿ�ٿ� ������ �� ������Ʈ���� ���� ������ ������ �ؽ�ó ����.

	geometryBufferRenderTarget_->SetDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());
	//������Ʈ�� ���� ����Ÿ���� ���̽��ٽǺ�� ����� ����Ÿ���� ���� �����´�.


	shadowDepthRenderTarget_ = GameEngineRenderTarget::Create();
	shadowDepthRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT_R32_FLOAT,	//4���� �� �ʿ��Ѱ� �ƴ϶� 0~1 ���� �׸��� ���̰��� ������ ����ϹǷ� �� �������� ����.
		float4::Red
	);
	//�׸��� ���������� ���� ����Ÿ�ٺ�� ���̴����ҽ��� ����.


	lightRatioBufferRenderTarget_ = GameEngineRenderTarget::Create();
	lightRatioBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT_R32_FLOAT,	//4���� �� �ʿ��Ѱ� �ƴ϶� 0~1 ���� �� ���� �������� ������ ����ϹǷ� �� �������� ����.
		float4::Red
	);
	//�ȼ��� �� ���� ������ ������ ����Ÿ�ٺ�� ���̴����ҽ��� ����.


	lightDataBufferRenderTarget_ = GameEngineRenderTarget::Create();
	//������ ���� ���� ����Ÿ�� ����.

	lightDataBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	//������ ���� ���� ����Ÿ�ٿ� ���ݻ籤(Diffuse Light) ������ ������ �ؽ�ó ����. 

	lightDataBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	//������ ���� ���� ����Ÿ�ٿ� ���ݻ籤(Specular Light) ������ ������ �ؽ�ó ����. 

	lightDataBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetInst().GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	//������ ���� ���� ����Ÿ�ٿ� ȯ�汤(Ambient Light) ������ ������ �ؽ�ó ����. 
	//���� z�� ������� ����ǹǷ� ���̽��ٽǺ並 ������ �ʿ䰡 ����.

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

	GameEngineDevice::GetDC()->RSSetViewports(//���������ο� ����Ʈ���� �����ϴ� �Լ�.
		1,					//������ ����Ʈ ����.
		&viewportDesc_		//����Ʈ ����ü �迭�� �ּҰ�.
	);
}

bool ZSort(GameEngineRenderer* _rendererA, GameEngineRenderer* _rendererB)
{
	//
	return _rendererA->GetTransform().GetWorldPosition().z > _rendererB->GetTransform().GetWorldPosition().z;
}

void GameEngineCamera::Render(float _deltaTime)
{
	//GameEngineDevice::GetContext()->RSSetViewports(//���������ο� ����Ʈ���� �����ϴ� �Լ�.
	//	1,					//������ ����Ʈ ����.
	//	&viewportDesc_		//����Ʈ ����ü �迭�� �ּҰ�.
	//);

	//��������� ������Ʈ���� ���ġ�� ������� ���Ѵ�.
	viewMatrix_.LookToLH(
		this->GetParent<GameEngineActor>()->GetTransform().GetLocalPosition(),
		this->GetParent<GameEngineActor>()->GetTransform().GetForwardVector(),
		this->GetParent<GameEngineActor>()->GetTransform().GetUpVector()
	);

	//������忡 �°� ������Ʈ���� ����� ��������� ���Ѵ�.
	switch (projectionMode_)
	{
	case ProjectionMode::Perspective:
		//projection_.ProjectPerspectiveLH(
		//	planeSize_.x * 0.0001f,	 //������� ���α���.
		//	planeSize_.y * 0.0001f,	 //������� ���α���.  
		//	nearZ_,
		//	farZ_
		//);
		//������� ���� ����ؼ� �־���� �ϴ� ProjectPerspectiveLH()���� 
		//ȭ���� ��Ⱦ��, ������ ������ũ�⸸ �־��ָ� �˾Ƽ� ����ϴ� ProjectPerspectiveFovLH()�� �� ���ϴ�.


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
		//������ ������.

		forwardRenderTarget_->Clear();
		forwardRenderTarget_->SetRenderTarget();
		//������ ����Ÿ�� ���� �� �ʱ�ȭ.

		for (std::pair<const int, std::list<GameEngineRenderer*>>& rendererGroup : allRenderers_)
		{
			float scaleTime = GameEngineTime::GetInst().GetDeltaTime(rendererGroup.first);

			std::list<GameEngineRenderer*>& sortingRendererList = rendererGroup.second;
			sortingRendererList.sort(ZSort);

			for (GameEngineRenderer* const renderer : rendererGroup.second)
				//�� ��ġ�� const�� renderer�� ����Ű�� �޸� ��ġ�� ������ �� ���� �ϰڴٴ� �ǹ��̴�. 
				//������ renderer�� ����Ű�� �޸𸮰� ���� ���� �󸶵��� ���� �����ϴ�.
			{
				if (false == renderer->IsUpdate())
				{
					continue;
				}

				renderer->renderOptionInst_.deltaTime_ = _deltaTime;
				renderer->renderOptionInst_.sumDeltaTime_ += _deltaTime;

				renderer->GetTransform().SetViewMatrix(viewMatrix_);
				renderer->GetTransform().SetProjectionMatrix(projectionMatrix_);
				//ī�޶� ����� ����İ� ��������� �������� Ʈ�������� �����Ѵ�.

				renderer->GetTransform().CalculateWorldViewProjection();
				//ũ���̰��� ��ȯ�� ��ģ ������Ŀ� ����İ� ������ı��� ����Ѵ�.

				renderer->Render(scaleTime);
				//����Ʈ����� ������ ��� ��� ����� ��ģ ������ �޽��� ȭ�鿡 �׸���.
			}
		}

		for (std::map<std::string, GameEngineInstancingRenderer>::iterator iter = allInstancingRenderers_.begin();
			iter != allInstancingRenderers_.end(); ++iter)
		{
			iter->second.Render(_deltaTime, this->viewMatrix_, this->projectionMatrix_);
			//���ο��� ��ü������ Ʈ������ ��İ���� �ؾ� �ϹǷ� �����, ��������� �־��ش�.
		}
	}


	{
		//���۵� ������.

		geometryBufferRenderTarget_->Clear(false);
		//gBuffer ����Ÿ���� �ؽ�ó�鸸 �ʱ�ȭ�Ѵ�. ���̽��ٽ� ���۴� �ʱ�ȭ���� �ʴ´�.
		//���̽��ٽǹ��۱��� �ʱ�ȭ�ϸ� ������Ʈ���� z�� ������ ���� ���ư���.

		geometryBufferRenderTarget_->SetRenderTarget();
		//gBuffer ����Ÿ���� DC�� ����.

		for (std::pair<const int, std::list<GameEngineRenderer*>>& rendererGroup : allRenderers_)
		{
			float scaleTime = GameEngineTime::GetInst().GetDeltaTime(rendererGroup.first);

			for (GameEngineRenderer* const renderer : rendererGroup.second)
				//�� ��ġ�� const�� renderer�� ����Ű�� �޸� ��ġ�� ������ �� ���� �ϰڴٴ� �ǹ��̴�. 
				//������ renderer�� ����Ű�� �޸𸮰� ���� ���� �󸶵��� ���� �����ϴ�.
			{
				if (false == renderer->IsUpdate())
				{
					continue;
				}

				renderer->renderOptionInst_.deltaTime_ = _deltaTime;
				renderer->renderOptionInst_.sumDeltaTime_ += _deltaTime;
				
				//renderer->GetTransform().SetViewMatrix(viewMatrix_);
				//renderer->GetTransform().SetProjectionMatrix(projectionMatrix_);
				////ī�޶� ����� ����İ� ��������� �������� Ʈ�������� �����Ѵ�.
				//
				//renderer->GetTransform().CalculateWorldViewProjection();
				//ũ���̰��� ��ȯ�� ��ģ ������Ŀ� ����İ� ������ı��� ����Ѵ�.
				////��� ��ȯ�� �̹� ������ �����Ƿ� �Ǵٽ� ���� �ʴ´�.

				renderer->DeferredRender(scaleTime);
				//geometryBufferRenderTarget_�� �� ����Ÿ�ٺ�鿡 ������Ʈ�� ���� ����, ������Ʈ ǥ�� ��� ������ ����� ��ġ, 
				// ������Ʈ ǥ�� ��� ������ ����� ��������, ������Ʈ�� ���̰��� ������ �������� �����Ѵ�. 
			}
		}

		for (std::map<std::string, GameEngineInstancingRenderer>::iterator iter = allInstancingRenderers_.begin();
			iter != allInstancingRenderers_.end(); ++iter)
		{
			iter->second.DeferredRender(_deltaTime, this->viewMatrix_, this->projectionMatrix_);
		}
	}
	


	{
		//���۵� �׸��� ������.

		shadowDepthRenderTarget_->Clear();
		shadowDepthRenderTarget_->SetRenderTarget();

		for (std::map<std::string, GameEngineInstancingRenderer>::iterator iter = allInstancingRenderers_.begin();
			iter != allInstancingRenderers_.end(); ++iter)
		{
			iter->second.RenderShadow(_deltaTime, this->viewMatrix_, this->projectionMatrix_);
		}
		//�÷��̾ �ڱ� �׸��ڿ� �������°Ϳ� ���� �ӽ� ��ġ.

		for (std::pair<const int, std::list<GameEngineRenderer*>>& rendererGroup : allRenderers_)
		{
			float scaleTime = GameEngineTime::GetInst().GetDeltaTime(rendererGroup.first);

			std::list<GameEngineRenderer*>& sortingRendererList = rendererGroup.second;
			sortingRendererList.sort(ZSort);

			for (GameEngineRenderer* const renderer : rendererGroup.second)
				//�� ��ġ�� const�� renderer�� ����Ű�� �޸� ��ġ�� ������ �� ���� �ϰڴٴ� �ǹ��̴�. 
				//������ renderer�� ����Ű�� �޸𸮰� ���� ���� �󸶵��� ���� �����ϴ�.
			{
				if (false == renderer->IsUpdate())
				{
					continue;
				}

				renderer->renderOptionInst_.deltaTime_ = _deltaTime;
				renderer->renderOptionInst_.sumDeltaTime_ += _deltaTime;

				//renderer->GetTransform().SetViewMatrix(this->viewMatrix_);
				//renderer->GetTransform().SetProjectionMatrix(this->projectionMatrix_);
				////ī�޶� ����� ����İ� ��������� �������� Ʈ�������� �����Ѵ�.

				//renderer->GetTransform().CalculateWorldViewProjection();
				//ũ���̰��� ��ȯ�� ��ģ ������Ŀ� ����İ� ������ı��� ����Ѵ�.
				////��� ��ȯ�� �̹� ������ �����Ƿ� �Ǵٽ� ���� �ʴ´�.

				renderer->RenderShadow(scaleTime);
				//shadowDepthRenderTarget_�� ����Ÿ�ٺ信 �׸����� ���̰��� �����ϰ� �Ѵ�.
			}
		}
	}


	lightRatioBufferRenderTarget_->Clear();
	lightRatioBufferRenderTarget_->Effect(*lightRatioRenderUnit_);
	//�׸����� ���̰��� ������Ʈ�� ���̰��� ���ؼ� �׸��ڰ� ������Ʈ���� �� �տ� ���´ٸ� 
	// �׸��ڰ� �׷����� �ȼ����� ���ݻ籤�� ���ݸ� ����ǰ� �Ѵ�.


	//������ ��� ����.

	lightDataBufferRenderTarget_->Clear();
	lightDataBufferRenderTarget_->Effect(*lightDataRenderUnit_);

	deferredRenderTarget_->Clear();
	deferredRenderTarget_->Effect(*mergeRenderUnit_);



	conclusionRenderTarget_->Clear();
	//���� ����Ÿ���� ����Ÿ�ٺ�, ���̽��ٽǺ� �ʱ�ȭ.

	conclusionRenderTarget_->Merge(forwardRenderTarget_);
	//������ ����Ÿ�ٿ� ����� ���󰪵��� ���� ����Ÿ�ٺ�� �����Ѵ�.

	conclusionRenderTarget_->Merge(deferredRenderTarget_);
	//���۵� ����Ÿ�ٿ� ����� ���󰪵��� ���� ����Ÿ�ٺ�� �����Ѵ�.


	//�̷��� ������ ���� �������� ���ӿ��������� Render()�Լ����� ����� ����Ÿ�ٿ� �ٽ��ѹ� ��������. 
}

void GameEngineCamera::PushRenderer(GameEngineRenderer* _renderer)
{
	allRenderers_[_renderer->GetOrder()].push_back(_renderer);
	//���ӿ���ī�޶��� �Ҹ��ڰ� ȣ����� ������, allRenderers Ǫ�ù� �������� ���� �����Ҵ�� ������ �������� 
	// �ʰ� �״�� ���� ���� �޸� ���� �ȴ�.
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
			//deadTime_�� 0�� �� �������鿡�� ��� ������ ������.

			if (true == (*listIter)->IsDead())
			{
				//delete (*listIter);	//���̻� ī�޶󿡼� ������ ������ ���� ���� �ʴ´�.
				listIter = mapIter->second.erase(listIter);
				//��� ī�޶��� allRenderers_ ����Ʈ������ �����Ѵ�.
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
		MsgBoxAssert("nextCamera�� �����ϴ�.");
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
	//���� ���콺�������� ��ġ�� �˾Ƴ���.

	mouseDirection_ = currentMousePosition - prevMousePosition_;
	//���� ���콺������ ��ġ - ���� ���콺������ ��ġ = ���콺�������� �̵�����.

	prevMousePosition_ = currentMousePosition;
	//���� ���콺������ ��ġ ����.
}
