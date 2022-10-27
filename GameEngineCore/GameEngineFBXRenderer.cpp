#include "PreCompile.h"
#include "GameEngineFBXRenderer.h"
#include "GameEngineFBXMesh.h"

GameEngineFBXRenderer::GameEngineFBXRenderer()
{
}

GameEngineFBXRenderer::~GameEngineFBXRenderer()
{
}

void GameEngineFBXRenderer::SetFBXMesh(const std::string& _fbxMeshName, const std::string& _materialName)
{
	// 너 몇개 가지고 있어.
	for (int i = 0; i < 2; i++)
	{
		SetFBXMesh(_fbxMeshName, _materialName, i);
	}
}

void GameEngineFBXRenderer::SetFBXMesh(const std::string& _fbxMeshName, const std::string& _materialName, int _meshIndex, int _subsetIndex)
{
	GameEngineFBXMesh* FindFBXMesh = GameEngineFBXMesh::Find(_fbxMeshName);

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("존재하지 않는 FBXMesh를 세팅했습니다.");
		return;
	}

	if (nullptr == FBXMesh && nullptr != FindFBXMesh)
	{
		FBXMesh = FindFBXMesh;
	}
	else if (nullptr != FBXMesh && FBXMesh != FindFBXMesh)
	{
		// 지금까지 만든거 다 날립니다.
	}

	GameEngineRenderUnit& RenderUnit = Unit.emplace_back();

	GameEngineMesh* FbxMesh = FBXMesh->GetGameEngineMesh(_meshIndex);

	// RenderUnit.SetMesh();
}

void GameEngineFBXRenderer::Render(float _DeltaTime)
{
	int a = 0;
}
