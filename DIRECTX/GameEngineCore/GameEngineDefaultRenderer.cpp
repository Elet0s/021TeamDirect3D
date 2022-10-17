#include "PreCompile.h"
#include "GameEngineDefaultRenderer.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexShader.h"

GameEngineDefaultRenderer::GameEngineDefaultRenderer() 
{
}

GameEngineDefaultRenderer::~GameEngineDefaultRenderer() 
{
}

void GameEngineDefaultRenderer::Start()
{
	GameEngineRenderer::Start();

	// ���� �� ������ �ִٸ� ���⼭ �ض�.
}

void GameEngineDefaultRenderer::SetPipeLine(const std::string& _Name)
{
	Unit.SetPipeLine(_Name);
	Unit.SetRenderer(this);
	PushRendererToMainCamera();
}

void GameEngineDefaultRenderer::Render(float _DeltaTime) 
{
	Unit.Render(_DeltaTime);

	//if (nullptr == PipeLine)
	//{
	//	MsgBoxAssert("������ ������������ ���õ��� ������ �������� �Ҽ� �����ϴ�.");
	//}

	//if (false == IsInstancing(GetPipeLine()))
	//{
	//	// �غ�� ��� ���ҽ����� �� �������ش�.
	//	ShaderResources.AllResourcesSetting();
	//	PipeLine->Rendering();
	//	ShaderResources.AllResourcesReset();
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

void GameEngineDefaultRenderer::InstancingOn()
{
	GameEngineRenderer::InstancingOn();

	// Camera->PushInstancing(PipeLine, 1);
}