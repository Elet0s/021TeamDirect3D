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
#include "GameEngineInstancingRenderer.h"

GameEngineCamera::GameEngineCamera()
	: size_(GameEngineWindow::GetScale()),
	projectionMode_(CameraProjectionMode::Perspective),
	nearZ_(0.1f),
	farZ_(100000.f),
	fovAngleY_(60.f),
	conclusionRenderTarget_(nullptr),
	forwardRenderTarget_(nullptr),
	deferredRenderTarget_(nullptr),
	geometryBufferRenderTarget_(nullptr),
	shadowDepthRenderTarget_(nullptr),
	lightRatioBufferRenderTarget_(nullptr),
	lightDataBufferRenderTarget_(nullptr),
	lightRatioRenderUnit_(std::make_shared<GameEngineRenderUnit>()),
	lightDataRenderUnit_(std::make_shared<GameEngineRenderUnit>()),
	mergerRenderUnit_(std::make_shared<GameEngineRenderUnit>())
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
}

float4 GameEngineCamera::GetMouseScreenPosition()
{
	POINT pointerPosition;
	if (false == GetCursorPos(&pointerPosition))
		//ȭ�� ��ü ���� ���콺 �������� ��ǥ�� ������ ��ũ�� ��ǥ(�»�� 0, 0)�� ��ȯ�ϴ� �Լ�.
	{
		MsgBoxAssert("���콺 ������ ��ǥ�� �����µ� �����߽��ϴ�.");
		return float4::Zero;
	}

	if (false == ScreenToClient(	//ȭ�� ��ü ���� ���콺 ������ ��ǥ�� Ư�� ������ ���� ��ǥ�� ��ȯ�ϴ� �Լ�.
		GameEngineWindow::GetHWND(),	//���콺 ������ ��ǥ�� �˷��� �ϴ� �������� �ڵ�.
		&pointerPosition	//��ȯ�� ȭ�� ��ü���� ���콺 ������ ��ǥ.
	))
	{
		MsgBoxAssert("���콺 ������ ��ǥ�� ��ȯ�ϴµ� �����߽��ϴ�.");
		return float4::Zero;
	}

	return float4(static_cast<float>(pointerPosition.x), static_cast<float>(pointerPosition.y));
}

float4 GameEngineCamera::GetMouseWorldPosition()
{
	POINT pointerPosition;
	if (false == GetCursorPos(&pointerPosition))
		//ȭ�� ��ü ���� ���콺 �������� ��ǥ�� ������ ��ũ�� ��ǥ(�»�� 0, 0)�� ��ȯ�ϴ� �Լ�.
	{
		MsgBoxAssert("���콺 ������ ��ǥ�� �����µ� �����߽��ϴ�.");
		return float4();
	}

	if (false == ScreenToClient(	//ȭ�� ��ü ���� ���콺 ������ ��ǥ�� Ư�� ������ ���� ��ǥ�� ��ȯ�ϴ� �Լ�.
		GameEngineWindow::GetHWND(),	//���콺 ������ ��ǥ�� �˷��� �ϴ� �������� �ڵ�.
		&pointerPosition)	//��ȯ�� ȭ�� ��ü���� ���콺 ������ ��ǥ.
	)
	{
		MsgBoxAssert("���콺 ������ ��ǥ�� ��ȯ�ϴµ� �����߽��ϴ�.");
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

	//pointerPos *= pointerPos.w;
	pointerPos *= this->projectionMatrix_.InverseReturn();
	//pointerPos *= this->viewMatrix_.InverseReturn();

	return pointerPos;
}

float4 GameEngineCamera::GetMouseWorldPositionToActor()
{
	return this->GetTransform().GetWorldPosition() + GetMouseWorldPosition();
}

float4 GameEngineCamera::GetWorldPositionToScreenPosition(const float4& _worldPosition)
{
	float4 pos = _worldPosition;

	pos *= this->viewMatrix_;			//pos�� ����� ����, �佺���̽� ��ǥ�� ����.
	pos *= this->projectionMatrix_;		//pos�� ������� ����, 
	pos /= pos.w;						//pos.w�� ����� pos�� ���z����ŭ pos�� ���.

	pos *= this->viewportMatrix_;		//pos�� ����Ʈ��� ����.

	return pos;
}

float4 GameEngineCamera::GetMouseTrueWorldPosition()
{
	POINT pointerPosition;
	if (false == GetCursorPos(&pointerPosition))
		//ȭ�� ��ü ���� ���콺 �������� ��ǥ�� ������ ��ũ�� ��ǥ(�»�� 0, 0)�� ��ȯ�ϴ� �Լ�.
	{
		MsgBoxAssert("���콺 ������ ��ǥ�� �����µ� �����߽��ϴ�.");
		return float4();
	}

	if (false == ScreenToClient(	//ȭ�� ��ü ���� ���콺 ������ ��ǥ�� Ư�� ������ ���� ��ǥ�� ��ȯ�ϴ� �Լ�.
		GameEngineWindow::GetHWND(),	//���콺 ������ ��ǥ�� �˷��� �ϴ� �������� �ڵ�.
		&pointerPosition)	//��ȯ�� ȭ�� ��ü���� ���콺 ������ ��ǥ.
	)
	{
		MsgBoxAssert("���콺 ������ ��ǥ�� ��ȯ�ϴµ� �����߽��ϴ�.");
		return float4();
	}

	float4 pointerPos = float4(static_cast<float>(pointerPosition.x), static_cast<float>(pointerPosition.y));

	pointerPos *= this->viewportMatrix_.InverseReturn();
	//���콺 ��ǥ�� ����Ʈ����� ����� ����.

	pointerPos *= this->projectionMatrix_.InverseReturn();
	//���콺 ��ǥ�� ��������� ����� ����.

	pointerPos *= this->viewMatrix_.InverseReturn();
	//���콺 ��ǥ�� ������� ����� ����.

	pointerPos /= pointerPos.w;
	//�̷��� ������ ���콺 ��ǥ�� w������ ���������� ������ �͹��Ͼ��� ���� ���´�.

	return pointerPos;
}

void GameEngineCamera::SetCameraOrder(CameraOrder _order)
{
	GetActor()->GetLevel()->PushCamera(std::dynamic_pointer_cast<GameEngineCamera>(shared_from_this()), _order);
}

//GameEngineInstancing& GameEngineCamera::GetInstancing(const std::string& _name)
//{
//	return instancingMap_[_name];	//������ ���� ���� ��ȯ, ������ ã�Ƽ� ��ȯ.
//}

std::shared_ptr<GameEngineInstancingRenderer> GameEngineCamera::GetInstancingRenderer(const std::string& _name)
{
	if (false == allInstancingRenderers_.contains(_name))
	{
		std::pair<std::map<std::string, std::shared_ptr<GameEngineInstancingRenderer>>::iterator, bool> insertResult 
			= allInstancingRenderers_.insert(std::make_pair(_name, std::make_shared<GameEngineInstancingRenderer>()));
	}

	return allInstancingRenderers_[_name];
}

void GameEngineCamera::PushLighting(std::shared_ptr<GameEngineLighting> _newLighting)
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
		GameEngineWindow::GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero	//float4::Black
	);
	conclusionRenderTarget_->SetDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());
	//���� ����Ÿ�� ���� �� �ʱ�ȭ. ���̽��ٽǺ�� ����� ����Ÿ���� ���� �����´�.

	forwardRenderTarget_ = GameEngineRenderTarget::Create();
	forwardRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	forwardRenderTarget_->SetDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());
	//�����巻������ ����Ÿ�� ���� �� �ʱ�ȭ. ���̽��ٽǺ�� ����� ����Ÿ���� ���� �����´�.

	deferredRenderTarget_ = GameEngineRenderTarget::Create();
	deferredRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	deferredRenderTarget_->SetDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());
	//���۵巻������ ����Ÿ�� ���� �� �ʱ�ȭ. ���̽��ٽǺ�� ����� ����Ÿ���� ���� �����´�.


	geometryBufferRenderTarget_ = GameEngineRenderTarget::Create();
	//������Ʈ�� ���� ����Ÿ�� ����.

	geometryBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	//������Ʈ�� ���� ����Ÿ�ٿ� ������Ʈ ǥ���� �⺻ ���� ������ ������ �ؽ�ó ����.

	geometryBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	//������Ʈ�� ���� ����Ÿ�ٿ� ������ �� ������Ʈ ǥ���� ����� ��ǥ������ ������ �ؽ�ó ����.

	geometryBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	//������Ʈ�� ���� ����Ÿ�ٿ� ������ �� ������Ʈ���� ����� ǥ�� �������� ������ ������ �ؽ�ó ����.

	geometryBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT,	//4���� �� �ʿ��Ѱ� �ƴ϶� 0~1 ���� ������Ʈ ���̰��� ������ ����ϹǷ� �� �������� ����.
		float4::Red
	);
	//������Ʈ�� ���� ����Ÿ�ٿ� ������ �� ������Ʈ���� ���� ������ ������ �ؽ�ó ����.

	geometryBufferRenderTarget_->SetDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());
	//������Ʈ�� ���� ����Ÿ���� ���̽��ٽǺ�� ����� ����Ÿ���� ���� �����´�.


	shadowDepthRenderTarget_ = GameEngineRenderTarget::Create();
	shadowDepthRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetScale(),
		DXGI_FORMAT_R32_FLOAT,	//4���� �� �ʿ��Ѱ� �ƴ϶� 0~1 ���� �׸��� ���̰��� ������ ����ϹǷ� �� �������� ����.
		float4::Red
	);
	//�׸��� ���������� ���� ����Ÿ�ٺ�� ���̴����ҽ��� ����.


	lightRatioBufferRenderTarget_ = GameEngineRenderTarget::Create();
	lightRatioBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetScale(),
		DXGI_FORMAT_R32_FLOAT,	//4���� �� �ʿ��Ѱ� �ƴ϶� 0~1 ���� �� ���� �������� ������ ����ϹǷ� �� �������� ����.
		float4::Red
	);
	//�ȼ��� �� ���� ������ ������ ����Ÿ�ٺ�� ���̴����ҽ��� ����.


	lightDataBufferRenderTarget_ = GameEngineRenderTarget::Create();
	//������ ���� ���� ����Ÿ�� ����.

	lightDataBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	//������ ���� ���� ����Ÿ�ٿ� ���ݻ籤(Diffuse Light) ������ ������ �ؽ�ó ����. 

	lightDataBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	//������ ���� ���� ����Ÿ�ٿ� ���ݻ籤(Specular Light) ������ ������ �ؽ�ó ����. 

	lightDataBufferRenderTarget_->CreateRenderTargetTexture(
		GameEngineWindow::GetScale(),
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		float4::Zero
	);
	//������ ���� ���� ����Ÿ�ٿ� ȯ�汤(Ambient Light) ������ ������ �ؽ�ó ����. 
	//���� z�� ������� ����ǹǷ� ���̽��ٽǺ並 ������ �ʿ䰡 ����.


	lightRatioRenderUnit_->SetMesh("Fullrect");
	lightRatioRenderUnit_->SetMaterial("CalLightRatio");
	lightRatioRenderUnit_->GetShaderResourceHelper().SetSampler("POINTCLAMP", "POINTCLAMP");
	lightRatioRenderUnit_->GetShaderResourceHelper().SetTexture("ObjectDepthTexture", geometryBufferRenderTarget_->GetRenderTargetTexture(3));
	lightRatioRenderUnit_->GetShaderResourceHelper().SetTexture("ShadowDepthTexture", shadowDepthRenderTarget_->GetRenderTargetTexture(0));



	lightDataRenderUnit_->SetMesh("Fullrect");
	lightDataRenderUnit_->SetMaterial("CalDeferredLight");
	lightDataRenderUnit_->GetShaderResourceHelper().SetConstantBuffer_Link("AllLightingDatas", this->lightingDatasInst_);
	lightDataRenderUnit_->GetShaderResourceHelper().SetTexture("PositionTexture", geometryBufferRenderTarget_->GetRenderTargetTexture(1));
	lightDataRenderUnit_->GetShaderResourceHelper().SetTexture("NormalTexture", geometryBufferRenderTarget_->GetRenderTargetTexture(2));
	lightDataRenderUnit_->GetShaderResourceHelper().SetTexture("LightRatioTexture", lightRatioBufferRenderTarget_->GetRenderTargetTexture(0));



	mergerRenderUnit_->SetMesh("Fullrect");
	mergerRenderUnit_->SetMaterial("CalDeferredMerger");
	mergerRenderUnit_->GetShaderResourceHelper().SetTexture("ColorTexture", geometryBufferRenderTarget_->GetRenderTargetTexture(0));
	mergerRenderUnit_->GetShaderResourceHelper().SetTexture("DiffuseLightTexture", lightDataBufferRenderTarget_->GetRenderTargetTexture(0));
	mergerRenderUnit_->GetShaderResourceHelper().SetTexture("SpecularLightTexture", lightDataBufferRenderTarget_->GetRenderTargetTexture(1));
	mergerRenderUnit_->GetShaderResourceHelper().SetTexture("AmbientLightTexture", lightDataBufferRenderTarget_->GetRenderTargetTexture(2));

	GameEngineDevice::GetContext()->RSSetViewports(//���������ο� ����Ʈ���� �����ϴ� �Լ�.
		1,					//������ ����Ʈ ����.
		&viewportDesc_		//����Ʈ ����ü �迭�� �ּҰ�.
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
	return _rendererA->GetTransform().GetWorldPosition().y < _rendererB->GetTransform().GetWorldPosition().y;
}

void GameEngineCamera::Render(float _deltaTime)
{
	//GameEngineDevice::GetContext()->RSSetViewports(//���������ο� ����Ʈ���� �����ϴ� �Լ�.
	//	1,					//������ ����Ʈ ����.
	//	&viewportDesc_		//����Ʈ ����ü �迭�� �ּҰ�.
	//);

	//������Ʈ���� ���ġ�� ������� ���Ѵ�.
	viewMatrix_.LookToLH(
		this->GetParent<GameEngineActor>()->GetTransform().GetLocalPosition(),
		this->GetParent<GameEngineActor>()->GetTransform().GetForwardVector(),
		this->GetParent<GameEngineActor>()->GetTransform().GetUpVector()
	);

	//������忡 �°� ������Ʈ���� ����� ��������� ���Ѵ�.
	switch (projectionMode_)
	{
	case CameraProjectionMode::Perspective:
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

	lightingDatasInst_.lightingCount_ = static_cast<int>(allLightings_.size());
	int lightingIndex = 0;
	for (std::shared_ptr<GameEngineLighting> singleLighting : allLightings_)
	{
		singleLighting->UpdataLightingData(std::dynamic_pointer_cast<GameEngineCamera>(shared_from_this()));
		lightingDatasInst_.lightings_[lightingIndex++] = singleLighting->GetLightingData();
	}


	{	
		//������ ������.

		forwardRenderTarget_->Clear();
		forwardRenderTarget_->Setting();
		//������ ����Ÿ�� ���� �� �ʱ�ȭ.

		for (std::pair<const int, std::list<std::shared_ptr<GameEngineRenderer>>>& rendererGroup : allRenderers_)
		{
			float scaleTime = GameEngineTime::GetDeltaTime(rendererGroup.first);

			std::list<std::shared_ptr<GameEngineRenderer>>& sortingRendererList = rendererGroup.second;
			sortingRendererList.sort(ZSort);

			for (std::shared_ptr<GameEngineRenderer> const renderer : rendererGroup.second)
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

		//for (std::unordered_map<std::string, GameEngineInstancing>::iterator iter = instancingMap_.begin();
		//	iter != instancingMap_.end(); ++iter)
		//{
		//	iter->second.RenderInstancing(_deltaTime);
		//}

		for (std::map<std::string, std::shared_ptr<GameEngineInstancingRenderer>>::iterator iter = allInstancingRenderers_.begin();
			iter != allInstancingRenderers_.end(); ++iter)
		{
			iter->second->Render(_deltaTime, this->viewMatrix_, this->projectionMatrix_);
			//���ο��� ��ü������ Ʈ������ ��İ���� �ؾ� �ϹǷ� �����, ��������� �־��ش�.
		}
	}


	{
		//���۵� ������.

		geometryBufferRenderTarget_->Clear(false);
		//gBuffer ����Ÿ���� �ؽ�ó�鸸 �ʱ�ȭ�Ѵ�. ���̽��ٽ� ���۴� �ʱ�ȭ���� �ʴ´�.
		//���̽��ٽǹ��۱��� �ʱ�ȭ�ϸ� ������Ʈ���� z�� ������ ���� ���ư���.

		geometryBufferRenderTarget_->Setting();
		//gBuffer ����Ÿ���� DC�� ����.

		for (std::pair<const int, std::list<std::shared_ptr<GameEngineRenderer>>>& rendererGroup : allRenderers_)
		{
			float scaleTime = GameEngineTime::GetDeltaTime(rendererGroup.first);

			//std::list<std::shared_ptr<GameEngineRenderer>>& sortingRendererList = rendererGroup.second;
			//sortingRendererList.sort(ZSort);

			for (std::shared_ptr<GameEngineRenderer> const renderer : rendererGroup.second)
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

		//for (std::unordered_map<std::string, GameEngineInstancing>::iterator iter = instancingMap_.begin();
		//	iter != instancingMap_.end(); ++iter)
		//{
		//	iter->second.RenderInstancing(_deltaTime);
		//}

		for (std::map<std::string, std::shared_ptr<GameEngineInstancingRenderer>>::iterator iter = allInstancingRenderers_.begin();
			iter != allInstancingRenderers_.end(); ++iter)
		{
			iter->second->DeferredRender(_deltaTime, this->viewMatrix_, this->projectionMatrix_);
		}
	}
	


	{
		//���۵� �׸��� ������.

		shadowDepthRenderTarget_->Clear();
		shadowDepthRenderTarget_->Setting();

		for (std::map<std::string, std::shared_ptr<GameEngineInstancingRenderer>>::iterator iter = allInstancingRenderers_.begin();
			iter != allInstancingRenderers_.end(); ++iter)
		{
			iter->second->RenderShadow(_deltaTime, this->viewMatrix_, this->projectionMatrix_);
		}
		//�÷��̾� �׸��� �������°Ϳ� ���� �ӽ� ��ġ.

		for (std::pair<const int, std::list<std::shared_ptr<GameEngineRenderer>>>& rendererGroup : allRenderers_)
		{
			float scaleTime = GameEngineTime::GetDeltaTime(rendererGroup.first);

			std::list<std::shared_ptr<GameEngineRenderer>>& sortingRendererList = rendererGroup.second;
			sortingRendererList.sort(ZSort);

			for (std::shared_ptr<GameEngineRenderer> const renderer : rendererGroup.second)
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
	lightRatioBufferRenderTarget_->Effect(lightRatioRenderUnit_);
	//�׸����� ���̰��� ������Ʈ�� ���̰��� ���ؼ� �׸��ڰ� ������Ʈ���� �� �տ� ���´ٸ� 
	// �׸��ڰ� �׷����� �ȼ����� ���ݻ籤�� ���ݸ� ����ǰ� �Ѵ�.


	//������ ��� ����.

	lightDataBufferRenderTarget_->Clear();
	lightDataBufferRenderTarget_->Effect(lightDataRenderUnit_);

	deferredRenderTarget_->Clear();
	deferredRenderTarget_->Effect(mergerRenderUnit_);



	conclusionRenderTarget_->Clear();
	//���� ����Ÿ���� ����Ÿ�ٺ�, ���̽��ٽǺ� �ʱ�ȭ.

	conclusionRenderTarget_->Merge(forwardRenderTarget_);
	//������ ����Ÿ�ٿ� ����� ���󰪵��� ���� ����Ÿ�ٺ�� �����Ѵ�.

	conclusionRenderTarget_->Merge(deferredRenderTarget_);
	//���۵� ����Ÿ�ٿ� ����� ���󰪵��� ���� ����Ÿ�ٺ�� �����Ѵ�.


	//�̷��� ������ ���� �������� ���ӿ��������� Render()�Լ����� ����� ����Ÿ�ٿ� �ٽ��ѹ� ��������. 
}

void GameEngineCamera::PushRenderer(std::shared_ptr<GameEngineRenderer> _renderer)
{
	allRenderers_[_renderer->GetOrder()].push_back(_renderer);
	//���ӿ���ī�޶��� �Ҹ��ڰ� ȣ����� ������, allRenderers Ǫ�ù� �������� ���� �����Ҵ�� ������ �������� 
	// �ʰ� �״�� ���� ���� �޸� ���� �ȴ�.
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
	float4 currentMousePosition = GetMouseWorldPosition();
	//���� ���콺�������� ��ġ�� �˾Ƴ���.

	currentMousePosition.w = 0.f;
	//w�� �� ���� 0??

	mouseDirection_ = currentMousePosition - prevMousePosition_;
	//���� ���콺������ ��ġ - ���� ���콺������ ��ġ = ���콺�������� �̵�����.

	prevMousePosition_ = currentMousePosition;
	//���� ���콺������ ��ġ ����.
}

void GameEngineCamera::OverRenderer(std::shared_ptr<GameEngineCamera> _nextCamera)
{
	if (nullptr == _nextCamera)
	{
		MsgBoxAssert("nextCamera�� �����ϴ�.");
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
