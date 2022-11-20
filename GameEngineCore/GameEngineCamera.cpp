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
	viewportDesc_.MaxDepth = 1.f;	//<-1.f�� ���ԵǾ� MinDepth�� ������ ���ܾ� �����׽�Ʈ�� ����� �� �� �ִ�.

	viewportMatrix_.Viewport(size_.x, size_.y, 0, 0, 0, 1);
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
		&pointerPosition	//��ȯ�� ȭ�� ��ü���� ���콺 ������ ��ǥ.
	))
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

	pos *= this->viewMatrix_;			//pos�� ����� ����, �佺���̽� ��ǥ�� ����.
	pos *= this->projectionMatrix_;		//pos�� ������� ����, 
	pos /= pos.w;						//pos.w�� ����� pos�� ���z����ŭ pos�� ���.
	//

	pos *= this->viewportMatrix_;		//pos�� ����Ʈ��� ����.

	return pos;
}

void GameEngineCamera::SetCameraOrder(CameraOrder _order)
{
	GetActor()->GetLevel()->PushCamera(std::dynamic_pointer_cast<GameEngineCamera>(shared_from_this()), _order);
}

GameEngineInstancing* GameEngineCamera::GetInstancing(const std::string& _name)
{
	std::shared_ptr<GameEngineMaterial> instancingPipeLine = GameEngineMaterial::Find(_name);
	return GetInstancing(instancingPipeLine);
}

GameEngineInstancing* GameEngineCamera::GetInstancing(std::shared_ptr<GameEngineMaterial> _pipeLine)
{
	if (nullptr == _pipeLine)
	{
		MsgBoxAssert("������ ������������ �������� �ʽ��ϴ�.");
		return nullptr;
	}

	std::unordered_map<GameEngineMaterial*, GameEngineInstancing>::iterator findIter
		= instancingMap_.find(_pipeLine.get());

	//if (instancingMap_.end() == findIter)	//�ν��Ͻ��� ���ٸ� ���� �� ��ȯ.
	//{
	//	GameEngineInstancing& instancing = instancingMap_[_pipeLine];
	//	GameEngineVertexBuffer* vertexBuffer = _pipeLine->GetVertexBuffer();

	//	instancing.instancingPipeLine_ = GameEngineRenderingPipeLine::Create();
	//	instancing.instancingPipeLine_->Copy(_pipeLine);
	//	instancing.instancingPipeLine_->SetVertexShader(_pipeLine->GetVertexShader()->GetInstancingShader());

	//	instancing.shaderResourceHelper_.ResourceCheck(instancing.instancingPipeLine_);
	//	instancing.shaderResourceHelper_.AllConstantBufferNew();

	//	instancing.size_ = vertexBuffer->GetInputLayoutInfo()->instancingSize_;
	//	instancing.instancingBuffer_
	//		= GameEngineInstancingBuffer::Create(
	//			GameEngineInstancing::startInstancingCount_,
	//			vertexBuffer->GetInputLayoutInfo()->instancingSize_
	//		);
	//	instancing.dataBuffer_.resize(
	//		static_cast<size_t>(GameEngineInstancing::startInstancingCount_ * instancing.size_));

	//	instancing.maxDataCount_ = GameEngineInstancing::startInstancingCount_;

	//	if (true == instancing.shaderResourceHelper_.IsStructuredBuffer("allInstancingTransfomrDatas"))
	//	{
	//		GameEngineStructuredBufferSetter* sBufferSetter 
	//			= instancing.shaderResourceHelper_.GetStructuredBufferSetter("allInstancingTransfomrDatas");

	//		if (nullptr != sBufferSetter->structuredBuffer_)
	//		{
	//			sBufferSetter->Resize(instancing.maxDataCount_);
	//		}
	//		else
	//		{
	//			MsgBoxAssert("�ν��Ͻ̿� ����ȭ���۰� �غ���� �ʾҽ��ϴ�.");
	//			return nullptr;
	//		}
	//	}
	//	findIter = instancingMap_.find(_pipeLine);
	//}

	return &findIter->second;
}

void GameEngineCamera::PushInstancing(std::shared_ptr<GameEngineMaterial> _pipeLine, int _count)
{
	if (false == _pipeLine->GetVertexShader()->IsInstancing())
	{
		MsgBoxAssertString(_pipeLine->GetNameCopy() + ": �ν��Ͻ��� �Ұ����� �������Դϴ�.");
	}

	GameEngineInstancing& instancing = instancingMap_[_pipeLine.get()];

	instancing.count_ += _count;

	//if (GameEngineInstancing::minInstancingCount_ <= instancing.count_ && nullptr == instancing.instancingBuffer_)
	//{
	//	GameEngineVertexBuffer* vertexBuffer = _pipeLine->GetVertexBuffer();

	//	instancing.instancingPipeLine_ = GameEngineRenderingPipeLine::Create();
	//	instancing.instancingPipeLine_->Copy(_pipeLine);
	//	instancing.instancingPipeLine_->SetVertexShader(_pipeLine->GetVertexShader()->GetInstancingShader());

	//	// ��Ʈ��ó�� ���۰� �����������
	//	instancing.shaderResourceHelper_.ResourceCheck(instancing.instancingPipeLine_);
	//	instancing.shaderResourceHelper_.AllConstantBufferNew();


	//	// �� �ܰ� ������ � ������۸� �������ְ� �װ� �����ؾ��Ѵٴ� ������ ���������.
	//	// ������ �����.
	//	instancing.size_ = vertexBuffer->GetInputLayoutInfo()->instancingSize_;

	//	instancing.instancingBuffer_ = GameEngineInstancingBuffer::Create(
	//		GameEngineInstancing::startInstancingCount_, static_cast<UINT>(instancing.size_));

	//	instancing.dataBuffer_.resize(
	//		static_cast<size_t>(GameEngineInstancing::startInstancingCount_) * instancing.size_);
	//}
	//else if(instancing.instancingBuffer_->GetBufferCount() < instancing.count_ 
	//	&& nullptr != instancing.instancingBuffer_)
	//{
	//	GameEngineVertexBuffer* vertexBuffer = _pipeLine->GetVertexBuffer();

	//	size_t nextBufferCount = static_cast<size_t>(instancing.count_ * 1.5);

	//	instancing.instancingBuffer_->CreateInstancingBuffer(
	//		static_cast<UINT>(nextBufferCount), vertexBuffer->GetInputLayoutInfo()->instancingSize_);

	//	instancing.dataBuffer_.resize(nextBufferCount * instancing.size_);

	//	if (true == instancing.shaderResourceHelper_.IsStructuredBuffer("allInstancingTransformDataBuffer"))
	//	{
	//		GameEngineStructuredBufferSetter* sBufferSetter 
	//			= instancing.shaderResourceHelper_.GetStructuredBufferSetter("allInstancingTransformDataBuffer");

	//		if (nullptr != sBufferSetter->structuredBuffer_)
	//		{
	//			sBufferSetter->Resize(instancing.maxDataCount_);
	//		}
	//		else
	//		{
	//			MsgBoxAssert("�ν��Ͻ̿� ����ȭ���۰� �غ���� �ʾҽ��ϴ�.");
	//			return;
	//		}
	//	}
	//}
}

int GameEngineCamera::PushInstancingData(std::shared_ptr<GameEngineMaterial> _pipeLine, void* _data, int _dataSize)
{
	int dataOffset = instancingMap_[_pipeLine.get()].dataInsert_ * _dataSize;

	// PushInstancing���� �̹� ���۴� ����� �����ŭ �þ �־�� �Ѵ�.

	char* dataPtr = &instancingMap_[_pipeLine.get()].dataBuffer_[dataOffset];
	memcpy_s(dataPtr, instancingMap_[_pipeLine.get()].dataBuffer_.size() - dataOffset, _data, _dataSize);
	dataOffset += _dataSize;
	int insertResultIndex = instancingMap_[_pipeLine.get()].dataInsert_;
	++instancingMap_[_pipeLine.get()].dataInsert_;
	return insertResultIndex;
}

int GameEngineCamera::PushInstancingIndex(std::shared_ptr<GameEngineMaterial> _pipeLine)
{
	int insertCount = instancingMap_[_pipeLine.get()].dataInsert_;

	return PushInstancingData(_pipeLine, &insertCount, sizeof(int));
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
}

bool ZSort(std::shared_ptr<GameEngineRenderer> _rendererA, std::shared_ptr<GameEngineRenderer> _rendererB)
{
	//
	return _rendererA->GetTransform().GetWorldPosition().z > _rendererB->GetTransform().GetWorldPosition().z;
}

void GameEngineCamera::Render(float _deltaTime)
{
	cameraRenderTarget_->Clear();
	//�� ī�޶��� ����Ÿ�ٺ�, ���̽��ٽǺ� �ʱ�ȭ.

	cameraRenderTarget_->Setting();
	//�ʱ�ȭ�� ����Ÿ�ٺ並 ������ ���������ο� ����.

	GameEngineDevice::GetContext()->RSSetViewports(//���������ο� ����Ʈ���� �����ϴ� �Լ�.
		1,					//������ ����Ʈ ����.
		&viewportDesc_		//����Ʈ ����ü �迭�� �ּҰ�.
	);

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

	for (std::unordered_map<GameEngineMaterial*, GameEngineInstancing>::iterator iter = instancingMap_.begin();
		iter != instancingMap_.end(); iter++)
	{
		iter->second.dataInsert_ = 0;
		//�ν��Ͻ� ���� �ʱ�ȭ.
	}

	for (std::pair<const int, std::list<std::shared_ptr<GameEngineRenderer>>>& rendererGroup : allRenderers_)
	{
		float scaleTime = GameEngineTime::GetDeltaTime(rendererGroup.first);

		std::list<std::shared_ptr<GameEngineRenderer>>& sortingRendererList = rendererGroup.second;
		sortingRendererList.sort(ZSort);

		for (std::shared_ptr<GameEngineRenderer> const renderer : rendererGroup.second)
			//�� ��ġ�� const�� renderer�� ����Ű�� �޸� ��ġ�� ������ �� ���� �ϰڴٴ� �ǹ��̴�. 
			//������ renderer�� ����Ű�� �޸𸮰� ���� ���� �󸶵��� ���� �����ϴ�.
		{
			if (true == renderer->IsUpdate())
			{
				renderer->renderOptionInst_.deltaTime_ = _deltaTime;
				renderer->renderOptionInst_.sumDeltaTime_ += _deltaTime;

				renderer->GetTransform().SetViewMatrix(viewMatrix_);
				renderer->GetTransform().SetProjectionMatrix(projectionMatrix_);
				//ī�޶� ����� ����İ� ��������� �������� Ʈ�������� �����Ѵ�.

				renderer->GetTransform().CalculateWorldViewProjection();
				//ũ���̰��� ��ȯ�� ��ģ ������Ŀ� ����İ� ������ı��� ����Ѵ�.

				
				if (true == float4x4::IsInViewSpace(
					renderer->GetTransformData().worldViewProjectionMatrix_, 
					float4(renderer->renderOptionInst_.pivotPosX_, renderer->renderOptionInst_.pivotPosY_))
				)
					//�佺���̽� �ȿ� �����̶� ������ �͵鸸 �׸���.
				{
					renderer->Render(scaleTime);
					//����Ʈ����� ������ ��� ��� ����� ��ģ ������ �޽��� ȭ�鿡 �׸���.
				}
			}
		}
	}

	//for (std::unordered_map<GameEngineRenderingPipeLine*, GameEngineInstancing>::iterator iter = instancingMap_.begin();
	//	iter != instancingMap_.end(); iter++)
	//{
	//	if (GameEngineInstancing::minInstancingCount_ > iter->second.count_)
	//	{
	//		continue;
	//	}
	//
	//	GameEngineRenderingPipeLine* pipeLine = iter->first;
	//	GameEngineInstancing& instancing = iter->second;
	//
	//	instancing.InstancingBufferChangeData();
	//	instancing.shaderResourceHelper_.AllResourcesSetting();
	//	instancing.instancingPipeLine_->RenderInstancing(instancing.dataInsert_, instancing.instancingBuffer_);
	//	instancing.shaderResourceHelper_.AllResourcesReset();
	//}
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
