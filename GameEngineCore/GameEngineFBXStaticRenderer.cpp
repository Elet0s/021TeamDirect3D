#include "PreCompile.h"
#include "GameEngineFBXStaticRenderer.h"
#include "GameEngineVertexShader.h"

GameEngineFBXStaticRenderer::GameEngineFBXStaticRenderer()
{
}

GameEngineFBXStaticRenderer::~GameEngineFBXStaticRenderer()
{
}

void GameEngineFBXStaticRenderer::SetFBXMesh(const std::string& _fbxMeshName, const std::string& _materialName)
{
	std::shared_ptr<GameEngineMaterial> Material = GameEngineMaterial::Find(_materialName);

	if (nullptr == Material)
	{
		MsgBoxAssert("존재하지 않는 머티리얼 입니다.");
		return;
	}

	if (true == Material->GetVertexShader()->IsStructuredBuffer("ArrAnimationMatrix"))
	{
		MsgBoxAssert("스태틱 매쉬 랜더러는 애니메이션을 할수 없습니다. 머티리얼 내부에 ArrAnimationMatrix를 사용하고 있습니다.");
		return;
	}

	GameEngineFBXRenderer::SetFBXMesh(_fbxMeshName, _materialName);
}

GameEngineRenderUnit* GameEngineFBXStaticRenderer::SetFBXMesh(
	const std::string& _fbxMeshName,
	const std::string& _materialName,
	size_t _meshIndex,
	size_t _subsetIndex
)
{
	std::shared_ptr<GameEngineMaterial> Material = GameEngineMaterial::Find(_materialName);

	if (nullptr == Material)
	{
		MsgBoxAssert("존재하지 않는 머티리얼 입니다.");
		return nullptr;
	}

	if (true == Material->GetVertexShader()->IsStructuredBuffer("ArrAnimationMatrix"))
	{
		MsgBoxAssert("스태틱 매쉬 랜더러는 애니메이션을 할수 없습니다. 머티리얼 내부에 ArrAnimationMatrix를 사용하고 있습니다.");
		return nullptr;
	}

	return GameEngineFBXRenderer::SetFBXMesh(_fbxMeshName, _materialName, _meshIndex, _subsetIndex);
}

void GameEngineFBXStaticRenderer::Render(float _deltaTime)
{
	GameEngineFBXRenderer::Render(_deltaTime);
}
