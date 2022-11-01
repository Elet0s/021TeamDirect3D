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
	GameEngineFBXMesh* FindFBXMesh = GameEngineFBXMesh::Find(_fbxMeshName);
	// �� � ������ �־�.
	for (size_t UnitCount = 0; UnitCount < FindFBXMesh->GetRenderUnitCount(); UnitCount++)
	{
		for (size_t SubSetCount = 0; SubSetCount < FindFBXMesh->GetSubSetCount(UnitCount); SubSetCount++)
		{
			SetFBXMesh(_fbxMeshName, _materialName, UnitCount, SubSetCount);
		}
	}
}

void GameEngineFBXRenderer::SetFBXMesh(
	const std::string& _fbxMeshName,
	const std::string& _materialName,
	size_t _meshIndex,
	size_t _subsetIndex /*= 0*/
)
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

	if (Unit.empty())
	{
		Unit.resize(FBXMesh->GetRenderUnitCount());
		for (size_t i = 0; i < Unit.size(); i++)
		{
			Unit[i].resize(FBXMesh->GetSubSetCount(i));
		}
	}

	GameEngineRenderUnit& RenderUnit = Unit[_meshIndex][_subsetIndex];
	RenderUnit.SetPipeLine(_materialName);

	GameEngineMesh* FbxMesh = FBXMesh->GetGameEngineMesh(_meshIndex, _subsetIndex);
	RenderUnit.SetMesh(FbxMesh);

	if (RenderUnit.GetShaderResourceHelper().IsTexture("DiffuseTexture"))
	{
		const FBXExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(_meshIndex, _subsetIndex);

		RenderUnit.GetShaderResourceHelper().SetTexture("DiffuseTexture", MatData.DifTextureName);
	}

	RenderUnit.SetRenderer(this);
}

void GameEngineFBXRenderer::Render(float _deltaTime)
{
	for (size_t UnitIndex = 0; UnitIndex < Unit.size(); UnitIndex++)
	{
		for (size_t SubSetIndex = 0; SubSetIndex < Unit[UnitIndex].size(); SubSetIndex++)
		{
			if (nullptr == Unit[UnitIndex][SubSetIndex].GetPipeLine())
			{
				continue;
			}

			Unit[UnitIndex][SubSetIndex].Render(_deltaTime);
		}
	}
}

void GameEngineFBXRenderer::CreateAnimation(
	const std::string& _AnimationName,
	const std::string& _MeshFBX,
	const std::string& _AnimationFBX
)
{
}
