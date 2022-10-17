#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineCamera.h"
#include "GameEngineInstancing.h"


#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"


//////////////////////////////////////////////////////// GameEngineRenderUnit 

GameEngineRenderUnit::GameEngineRenderUnit() 
	: ParentRenderer(nullptr)
	, PipeLine(nullptr)
{

}

void GameEngineRenderUnit::EngineShaderResourcesSetting(GameEngineRenderer* _Renderer)
{
	if (nullptr == _Renderer)
	{
		return;
	}

	ParentRenderer = _Renderer;

	//// ������ ������ ������ �Ѵ�.
	if (true == ShaderResources.IsConstantBuffer("TRANSFORMDATA"))
	{
		ShaderResources.SetConstantBufferLink("TRANSFORMDATA", &ParentRenderer->GetTransformData(), sizeof(TransformData));
	}

	if (true == ShaderResources.IsConstantBuffer("RENDEROPTION"))
	{
		ShaderResources.SetConstantBufferLink("RENDEROPTION", &ParentRenderer->renderOption, sizeof(RenderOption));
	}

}


void GameEngineRenderUnit::SetPipeLine(const std::string& _Name)
{
	PipeLine = GameEngineRenderingPipeLine::Find(_Name);

	if (nullptr == PipeLine)
	{
		MsgBoxAssert("�������� �ʴ� ������������ �����Ϸ��� �߽��ϴ�.");
		return;
	}

	ShaderResources.ResourcesCheck(PipeLine);
}

void GameEngineRenderUnit::SetRenderer(GameEngineRenderer* _Renderer)
{
	ParentRenderer = _Renderer;

	EngineShaderResourcesSetting(ParentRenderer);
}


GameEngineRenderingPipeLine* GameEngineRenderUnit::GetPipeLine()
{
	return PipeLine;
}

GameEngineRenderingPipeLine* GameEngineRenderUnit::GetClonePipeLine()
{
	if (false == PipeLine->IsOriginal())
	{
		return PipeLine;
	}

	PipeLine = ClonePipeLine(PipeLine);
	return PipeLine;
}


GameEngineRenderingPipeLine* GameEngineRenderUnit::ClonePipeLine(GameEngineRenderingPipeLine* _Rendering)
{
	// �̸����� �༮���� �����.
	GameEngineRenderingPipeLine* Clone = GameEngineRenderingPipeLine::Create();
	Clone->Copy(_Rendering);
	return Clone;
}




void GameEngineRenderUnit::Render(float _DeltaTime)
{
	if (nullptr == PipeLine)
	{
		MsgBoxAssert("������ ������������ ���õ��� ������ �������� �Ҽ� �����ϴ�.");
	}

	//if (false == IsInstancing(GetPipeLine()))
	//{
		// �غ�� ��� ���ҽ����� �� �������ش�.
		ShaderResources.AllResourcesSetting();
		PipeLine->Rendering();
		ShaderResources.AllResourcesReset();
	//}
	//else
	//{
	//	InstancingDataSetting(GetPipeLine());
	//	// �����е��� ���ο� �������� ����� �ν��Ͻ��� �ϸ�
	//	// �� �κ��� �޶����� �մϴ�.
	//	// ������ �����Ʈ¥�� �ν���
	//	// Camera->PushInstancingIndex(PipeLine);
	//}
}

//////////////////////////////////////////////////////// GameEngineRenderer

GameEngineRenderer::GameEngineRenderer()
	: CameraOrder(CAMERAORDER::MAINCAMERA)
	, RenderingOrder(0)
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
	int a = 0;
}

void GameEngineRenderer::Start() 
{
}

void GameEngineRenderer::PushRendererToMainCamera()
{
	GetActor()->GetLevel()->PushRendererToMainCamera(this);	
}

void GameEngineRenderer::SetRenderingOrder(int _Order)
{
	Camera->ChangeRenderingOrder(this, _Order);
}

void GameEngineRenderer::PushRendererToUICamera()
{
	GetActor()->GetLevel()->PushRendererToUICamera(this);
}


bool GameEngineRenderer::IsInstancing(GameEngineRenderingPipeLine* _Rendering)
{
	std::unordered_map<GameEngineRenderingPipeLine*, GameEngineInstancing>::iterator InstancingIter = Camera->InstancingMap.find(_Rendering);

	if (InstancingIter == Camera->InstancingMap.end())
	{
		return false;
	}

	return true == IsInstancing_ && GameEngineInstancing::MinInstancingCount <= InstancingIter->second.Count;
}

// �츮 �������� �ν��Ͻ��� �Ѵٸ� ������ �����ϳ��� �ν��Ͻ��� �����ϱ�. �̰� ok
void GameEngineRenderer::InstancingDataSetting(GameEngineRenderingPipeLine* _Line)
{
	// ���° �������� �˷��ְ� �־��
	// �̳༮�� ���ؼ� 
	int InstancingIndex = Camera->PushInstancingIndex(_Line);

	GameEngineInstancing* Instancing = Camera->GetInstancing(_Line);

	if (nullptr == Instancing)
	{
		MsgBoxAssert("�ν��Ͻ��� ���������� �ν��Ͻ� ������ �����ϴ�.");
	}

	if (true == Instancing->ShaderResources.IsStructuredBuffer("AllInstancingTransformData"))
	{
		GameEngineStructuredBufferSetter* Setter = Instancing->ShaderResources.GetStructuredBuffer("AllInstancingTransformData");

		Setter->Push(GetTransform().GetTransformData(), InstancingIndex);

		

		//Setter->Res

		// GetTransform().GetTransformData()
	}
}


//void GameEngineRenderer::Render(float _DeltaTime)
//{
//	//// ������
//	////GameEngineVertexBuffer* Vertex = GameEngineVertexBuffer::Find("Rect");
//	////GameEngineIndexBuffer* Index = GameEngineIndexBuffer::Find("Rect");
//
//	//GameEngineVertexBuffer* Vertex = GameEngineVertexBuffer::Find("Box");
//	//GameEngineIndexBuffer* Index = GameEngineIndexBuffer::Find("Box");
//	//
//	//std::vector<POINT> DrawVertex;
//	//DrawVertex.resize(Index->Indexs.size());
//
//	//std::vector<float4> CopyBuffer;
//	//CopyBuffer.resize(Index->Indexs.size());
//
//
//	//for (size_t i = 0; i < Index->Indexs.size(); i++)
//	//{
//	//	int TriIndex = Index->Indexs[i];
//
//	//	// 0 ��° ������ ���� �˴ϴ�.
//	//	// ���ʿ� ���� �Ž��� ���� �����մϴ�.
//	//	CopyBuffer[i] = Vertex->Vertexs[TriIndex];
//
//	//	auto& tran = GetTransform();
//
//	//	// ���ؽ����̴�
//	//	CopyBuffer[i] = CopyBuffer[i] * GetTransform().GetWorldViewProjection();
//
//
//	//	// �����Ͷ�����
//	//	//// ����س��� z������ �����°�
//	//	CopyBuffer[i] = CopyBuffer[i] / CopyBuffer[i].w;
//
//
//	//	DrawVertex[i] = CopyBuffer[i].GetConvertWindowPOINT();
//	//}
//	//
//	//for (size_t i = 0; i < DrawVertex.size(); i += 3)
//	//{
//	//	Polygon(GameEngineWindow::GetHDC(), &DrawVertex[i], 3);
//	//}
//}

void GameEngineRenderer::ChangeCamera(CAMERAORDER _Order)
{
	GetActor()->GetLevel()->PushRenderer(this, _Order);
}

