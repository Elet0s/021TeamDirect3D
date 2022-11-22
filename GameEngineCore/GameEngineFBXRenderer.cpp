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
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_fbxMeshName);
	// 너 몇개 가지고 있어.
	for (size_t UnitCount = 0; UnitCount < FindFBXMesh->GetRenderUnitCount(); UnitCount++)
	{
		for (size_t SubSetCount = 0; SubSetCount < FindFBXMesh->GetSubSetCount(UnitCount); SubSetCount++)
		{
			SetFBXMesh(_fbxMeshName, _materialName, UnitCount, SubSetCount);
		}
	}
}

void GameEngineFBXRenderer::SetFBXMesh(const std::string& _fbxMeshName, const std::string& _materialName, size_t _meshIndex)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_fbxMeshName);

	for (size_t SubSetCount = 0; SubSetCount < FindFBXMesh->GetSubSetCount(_meshIndex); SubSetCount++)
	{
		size_t SubSet = FindFBXMesh->GetSubSetCount(_meshIndex);

		SetFBXMesh(_fbxMeshName, _materialName, _meshIndex);
	}
}

GameEngineRenderUnit* GameEngineFBXRenderer::SetFBXMesh(
	const std::string& _fbxMeshName,
	const std::string& _materialName,
	size_t _meshIndex,
	size_t _subsetIndex
)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_fbxMeshName);

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("존재하지 않는 FBXMesh를 세팅했습니다.");
		return nullptr;
	}

	if (nullptr == FBXMesh && nullptr != FindFBXMesh)
	{
		FBXMesh = FindFBXMesh;
	}
	else if (nullptr != FBXMesh && FBXMesh != FindFBXMesh)
	{
		// 지금까지 만든거 다 날립니다.
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
	RenderUnit.SetMaterial(_materialName);

	std::shared_ptr<GameEngineMesh> FbxMesh = FBXMesh->GetGameEngineMesh(_meshIndex, _subsetIndex);
	RenderUnit.SetMesh(FbxMesh);

	if (RenderUnit.GetShaderResourceHelper().IsTexture("DiffuseTexture"))
	{
		const FBXExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(_meshIndex, _subsetIndex);

		if (nullptr != GameEngineTexture::Find(MatData.DifTextureName))
		{
			RenderUnit.GetShaderResourceHelper().SetTexture("DiffuseTexture", MatData.DifTextureName);
		}
	}

	RenderUnit.SetRenderer(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));

	return &RenderUnit;
}

void GameEngineFBXRenderer::Render(float _deltaTime)
{
	for (size_t UnitIndex = 0; UnitIndex < Unit.size(); UnitIndex++)
	{
		for (size_t SubSetIndex = 0; SubSetIndex < Unit[UnitIndex].size(); SubSetIndex++)
		{
			if (nullptr == Unit[UnitIndex][SubSetIndex].GetMaterial())
			{
				continue;
			}

			Unit[UnitIndex][SubSetIndex].Render(_deltaTime);
		}
	}
}