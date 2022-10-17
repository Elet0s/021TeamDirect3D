#include "PreCompile.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderer.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineInstancing.h"
#include "GameEngineStructuredBuffer.h"
#include <GameEngineBase/GameEngineWindow.h>



GameEngineCamera::GameEngineCamera() 
{
	// �����찡 �����е� �����ϱ� ���� ���� �����̶� ���⼭ �ϴ°Ű�.
	Size = GameEngineWindow::GetInst()->GetScale();
	Mode = CAMERAPROJECTIONMODE::PersPective;
	Near = 0.1f;
	Far = 1000.0f;
	Fov = 60.0f;

	ViewPortDesc.TopLeftX = 0;
	ViewPortDesc.TopLeftY = 0;
	ViewPortDesc.Width = Size.x;
	ViewPortDesc.Height = Size.y;
	ViewPortDesc.MinDepth = 0.0f;
	ViewPortDesc.MaxDepth = 1.0f;
}

GameEngineCamera::~GameEngineCamera() 
{
}

bool ZSort(GameEngineRenderer* _Left, GameEngineRenderer* _Right)
{
	return _Left->GetTransform().GetWorldPosition().z > _Right->GetTransform().GetWorldPosition().z;
}

GameEngineInstancing* GameEngineCamera::GetInstancing(const std::string& _Name)
{
	GameEngineRenderingPipeLine* Instancing = GameEngineRenderingPipeLine::Find(_Name);
	return GetInstancing(Instancing);
}

void GameEngineCamera::Render(float _DeltaTime)
{
	CameraRenderTarget->Clear();
	CameraRenderTarget->Setting();

	// ���������κ��� �����Ͷ����� �ܰ������� ������ ���� �����ű� ������.
	GameEngineDevice::GetContext()->RSSetViewports(1, &ViewPortDesc);

	// �����ϱ� ���� 
	View.LookAtLH(
		GetActor()->GetTransform().GetLocalPosition(), 
		GetActor()->GetTransform().GetForwardVector(), 
		GetActor()->GetTransform().GetUpVector());

	switch (Mode)
	{
	case CAMERAPROJECTIONMODE::PersPective:
		Projection.PerspectiveFovLH(Fov, Size.x, Size.y, Near, Far);
		break;
	case CAMERAPROJECTIONMODE::Orthographic:
		Projection.OrthographicLH(Size.x, Size.y, Near, Far);
		break;
	default:
		break;
	}

	float4 WindowSize = GameEngineWindow::GetInst()->GetScale();

	// �ν��Ͻ������� �ʱ�ȭ�ؿ�.
	{
		std::unordered_map<GameEngineRenderingPipeLine*, GameEngineInstancing>::iterator StartIter = InstancingMap.begin();
		std::unordered_map<GameEngineRenderingPipeLine*, GameEngineInstancing>::iterator EndIter = InstancingMap.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			StartIter->second.DataInsert = 0;
		}
	}

	{
		// ������ �ϸ鼭 �ν��Ͻ� �����͸� �����ϰ�
		// �����ϸ鼭 ++DataInsert
		// ������ �ϱ� ����
		for (std::pair<const int, std::list<GameEngineRenderer*>>& Group : AllRenderer_)
		{
			float ScaleTime = GameEngineTime::GetInst()->GetDeltaTime(Group.first);

			std::list<GameEngineRenderer*>& RenderList = Group.second;
			RenderList.sort(ZSort);

			for (GameEngineRenderer* const Renderer : Group.second)
			{
				if (false == Renderer->IsUpdate())
				{
					continue;
				}

				Renderer->renderOption.DeltaTime = _DeltaTime;
				Renderer->renderOption.SumDeltaTime = _DeltaTime;
				Renderer->GetTransform().SetView(View);
				Renderer->GetTransform().SetProjection(Projection);
				Renderer->GetTransform().CalculateWorldViewProjection();

				// �ν��Ͻ� ���� ����
				Renderer->Render(ScaleTime);
			}
		}
	}

	// �ٳ����� �ν��Ͻ��� ������
	{
		// ���̴� ���ҽ� ������ �ٸ��ֵ��� ������
		std::unordered_map<GameEngineRenderingPipeLine*, GameEngineInstancing>::iterator StartIter = InstancingMap.begin();
		std::unordered_map<GameEngineRenderingPipeLine*, GameEngineInstancing>::iterator EndIter = InstancingMap.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (GameEngineInstancing::MinInstancingCount > StartIter->second.Count)
			{
				continue;
			}

			GameEngineRenderingPipeLine* Pipe = StartIter->first;
			GameEngineInstancing& Instancing = StartIter->second;

			Instancing.InstancingBufferChangeData();
			Instancing.ShaderResources.AllResourcesSetting();
			Instancing.InstancingPipeLine->RenderingInstancing(Instancing.DataInsert, Instancing.Buffer);
		}
	}
}

void GameEngineCamera::SetCameraOrder(CAMERAORDER _Order)
{
	GetActor()->GetLevel()->PushCamera(this, _Order);
}

void GameEngineCamera::Start()
{
	CameraRenderTarget = GameEngineRenderTarget::Create();

	CameraRenderTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	CameraRenderTarget->SettingDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());
	// CameraRenderTarget->CreateDepthTexture()
}

void GameEngineCamera::PushRenderer(GameEngineRenderer* _Renderer)
{
	AllRenderer_[_Renderer->RenderingOrder].push_back(_Renderer);
}


GameEngineInstancing* GameEngineCamera::GetInstancing(GameEngineRenderingPipeLine* _Pipe)
{
	if (nullptr == _Pipe)
	{
		MsgBoxAssert("�������� �ʴ� ������������ �ν��Ͻ� �����͸� �����ü� �����ϴ�.");
	}

	std::unordered_map<GameEngineRenderingPipeLine*, GameEngineInstancing>::iterator FindIter
		= InstancingMap.find(_Pipe);

	// ���±��� �ν��Ͻ��� �Ѱų� �õ����� �ʾҴ� �༮�ε�
	// �������� �ν��Ͻ��� �ҰŴϱ� �޶�� �Ҽ��� ����?
	if (FindIter == InstancingMap.end())
	{
		GameEngineInstancing& Instancing = InstancingMap[_Pipe];
		GameEngineVertexBuffer* Buffer = _Pipe->GetVertexBuffer();
		// InstancingMap[_Pipe].
		Instancing.InstancingPipeLine = GameEngineRenderingPipeLine::Create();
		Instancing.InstancingPipeLine->Copy(_Pipe);
		Instancing.InstancingPipeLine->SetVertexShader(_Pipe->GetVertexShader()->GetInstancingShader());

		Instancing.ShaderResources.ResourcesCheck(Instancing.InstancingPipeLine);
		Instancing.ShaderResources.AllConstantBufferNew();

		Instancing.Size = Buffer->GetLayOutDesc()->InstancingSize;
		Instancing.Buffer = GameEngineInstancingBuffer::Create(GameEngineInstancing::StartInstancingCount, Buffer->GetLayOutDesc()->InstancingSize);
		Instancing.DataBuffer.resize(GameEngineInstancing::StartInstancingCount * Instancing.Size);
		Instancing.MaxDataCount = GameEngineInstancing::StartInstancingCount;

		// �������� å������.
		if (Instancing.ShaderResources.IsStructuredBuffer("AllInstancingTransformData"))
		{
			GameEngineStructuredBufferSetter* Setter = Instancing.ShaderResources.GetStructuredBuffer("AllInstancingTransformData");

			if (nullptr != Setter->Res)
			{
				Setter->Resize(Instancing.MaxDataCount);
			}
			else
			{
				MsgBoxAssert("�ν��Ͻ̿� ����ȭ ���۰� ��������� �ʾҽ��ϴ�.");
			}
		}



		FindIter = InstancingMap.find(_Pipe);
	}

	return &FindIter->second;
}


void GameEngineCamera::PushInstancing(GameEngineRenderingPipeLine* _Pipe, int Count)
{
	if (false == _Pipe->GetVertexShader()->IsInstancing())
	{
		MsgBoxAssert("�ν��Ͻ��� �Ұ����� ������ �Դϴ�.")
	}

	// Camera->gameenginepipeline

	GameEngineInstancing& Instancing = InstancingMap[_Pipe];

	Instancing.Count += Count;

	if (GameEngineInstancing::MinInstancingCount <= Instancing.Count
		&& nullptr == Instancing.Buffer)
	{

		GameEngineVertexBuffer* Buffer = _Pipe->GetVertexBuffer();
		// InstancingMap[_Pipe].
		Instancing.InstancingPipeLine = GameEngineRenderingPipeLine::Create();
		Instancing.InstancingPipeLine->Copy(_Pipe);
		Instancing.InstancingPipeLine->SetVertexShader(_Pipe->GetVertexShader()->GetInstancingShader());

		// ��Ʈ��ó�� ���۰� �����������
		Instancing.ShaderResources.ResourcesCheck(Instancing.InstancingPipeLine);
		Instancing.ShaderResources.AllConstantBufferNew();


		// �� �ܰ� ������ � ������۸� �������ְ� �װ� �����ؾ��Ѵٴ� ������ ���������.
		// ������ �����.

		Instancing.Size = Buffer->GetLayOutDesc()->InstancingSize;
		Instancing.Buffer = GameEngineInstancingBuffer::Create(GameEngineInstancing::StartInstancingCount, Buffer->GetLayOutDesc()->InstancingSize);
		Instancing.DataBuffer.resize(GameEngineInstancing::StartInstancingCount * Instancing.Size);
	}
	else if(nullptr != Instancing.Buffer
		&& Instancing.Count > Instancing.Buffer->GetBufferCount())
	{
		//           105                           100
		GameEngineVertexBuffer* Buffer = _Pipe->GetVertexBuffer();
		int NextBufferSize = static_cast<int>(Instancing.Count * 1.5);
		Instancing.Buffer->BufferCreate(NextBufferSize, Buffer->GetLayOutDesc()->InstancingSize);
		Instancing.DataBuffer.resize(NextBufferSize * Instancing.Size);

		if (Instancing.ShaderResources.IsStructuredBuffer("AllInstancingTransformData"))
		{
			GameEngineStructuredBufferSetter* Setter = Instancing.ShaderResources.GetStructuredBuffer("AllInstancingTransformData");

			if (nullptr != Setter->Res)
			{
				Setter->Resize(Instancing.MaxDataCount);
			}
			else
			{
				MsgBoxAssert("�ν��Ͻ̿� ����ȭ ���۰� ��������� �ʾҽ��ϴ�.");
			}
		}

	}
}

int GameEngineCamera::PushInstancingIndex(GameEngineRenderingPipeLine* _Pipe)
{
	int InsertCount = InstancingMap[_Pipe].DataInsert;
	return PushInstancingData(_Pipe, &InsertCount, sizeof(int));
}


int GameEngineCamera::PushInstancingData(GameEngineRenderingPipeLine* _Pipe, void* _DataPtr, int _Size)
{
	int DataOffset = InstancingMap[_Pipe].DataInsert * _Size;

	// �־��ִٰ� ����� �����Ǹ� �����?
	// �ƴϴ�.
	// PushInstancing���� �̹� ���۴� ����� �����ŭ �þ �־�� �Ѵ�.

	char* DataPtr = &InstancingMap[_Pipe].DataBuffer[DataOffset];
	memcpy_s(DataPtr, InstancingMap[_Pipe].DataBuffer.size() - DataOffset, _DataPtr, _Size);
	DataOffset += _Size;

	int ResultIndex = InstancingMap[_Pipe].DataInsert;

	++InstancingMap[_Pipe].DataInsert;

	return ResultIndex;
}


void GameEngineCamera::Release(float _DelataTime)
{
	std::map<int, std::list<GameEngineRenderer*>>::iterator StartGroupIter = AllRenderer_.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator EndGroupIter = AllRenderer_.end();

	for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
	{
		std::list<GameEngineRenderer*>& Group = StartGroupIter->second;
		std::list<GameEngineRenderer*>::iterator GroupStart = Group.begin();
		std::list<GameEngineRenderer*>::iterator GroupEnd = Group.end();

		for (; GroupStart != GroupEnd; )
		{
			(*GroupStart)->ReleaseUpdate(_DelataTime);
			if (true == (*GroupStart)->IsDeath())
			{
				GroupStart = Group.erase(GroupStart);
			}
			else
			{
				++GroupStart;
			}

		}
	}
}

float4 GameEngineCamera::GetMouseScreenPosition() 
{
	POINT P;

	GetCursorPos(&P);

	ScreenToClient(GameEngineWindow::GetHWND(), &P);

	return { static_cast<float>(P.x), static_cast<float>(P.y) };
}

void GameEngineCamera::Update(float _DeltaTime) 
{
	float4 MousePos = GetMouseWorldPosition();
	MousePos.w = 0.0f;
	MouseDir = MousePos - PrevMouse;
	PrevMouse = MousePos;
}

// ����Ʈ�� �ִ°���?
float4 GameEngineCamera::GetMouseWorldPosition()
{
	float4 Pos = GetMouseScreenPosition();

	float4x4 ViewPort;
	ViewPort.ViewPort(Size.x, Size.y, 0, 0, 0, 1);
	ViewPort.Inverse();

	float4x4 ProjectionInvers = Projection.InverseReturn();

	Pos = Pos * ViewPort;
	Pos = Pos * ProjectionInvers;
	// ���콺�� ����Ʈ�� ��ǥ��?

	return Pos;
}


float4 GameEngineCamera::GetMouseWorldPositionToActor()
{
	return GetTransform().GetWorldPosition() + GetMouseWorldPosition();
}

void GameEngineCamera::ChangeRenderingOrder(GameEngineRenderer* _Renderer, int _ChangeOrder)
{
	// 0��°���� �����ǰ�
	AllRenderer_[_Renderer->GetRenderingOrder()].remove(_Renderer);

	_Renderer->RenderingOrder = _ChangeOrder;

	// 10000��°�� �̵��Ѵ�.
	AllRenderer_[_Renderer->GetRenderingOrder()].push_back(_Renderer);
}

void GameEngineCamera::OverRenderer(GameEngineCamera* _NextCamera) 
{
	if (nullptr == _NextCamera)
	{
		MsgBoxAssert("next camera is nullptr! fuck you");
		return;
	}

	std::map<int, std::list<GameEngineRenderer*>>::iterator StartGroupIter = AllRenderer_.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator EndGroupIter = AllRenderer_.end();

	for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
	{
		std::list<GameEngineRenderer*>& Group = StartGroupIter->second;
		std::list<GameEngineRenderer*>::iterator GroupStart = Group.begin();
		std::list<GameEngineRenderer*>::iterator GroupEnd = Group.end();

		for (; GroupStart != GroupEnd; )
		{
			GameEngineActor* Root = (*GroupStart)->GetRoot<GameEngineActor>();

			if (true == Root->IsLevelOver)
			{
				_NextCamera->AllRenderer_[StartGroupIter->first].push_back(*GroupStart);
				GroupStart = Group.erase(GroupStart);
			}
			else
			{
				++GroupStart;
			}

		}
	}
}