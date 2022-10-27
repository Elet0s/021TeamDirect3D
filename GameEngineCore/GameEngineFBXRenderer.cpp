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
	// �� � ������ �־�.
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
		MsgBoxAssert("�������� �ʴ� FBXMesh�� �����߽��ϴ�.");
		return;
	}

	if (nullptr == FBXMesh && nullptr != FindFBXMesh)
	{
		FBXMesh = FindFBXMesh;
	}
	else if (nullptr != FBXMesh && FBXMesh != FindFBXMesh)
	{
		// ���ݱ��� ����� �� �����ϴ�.
	}

	GameEngineRenderUnit& RenderUnit = Unit.emplace_back();

	GameEngineMesh* FbxMesh = FBXMesh->GetGameEngineMesh(_meshIndex);

	// RenderUnit.SetMesh();
}

void GameEngineFBXRenderer::Render(float _DeltaTime)
{
	int a = 0;
}
