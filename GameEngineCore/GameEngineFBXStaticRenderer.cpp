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
		MsgBoxAssert("�������� �ʴ� ��Ƽ���� �Դϴ�.");
		return;
	}

	if (true == Material->GetVertexShader()->IsStructuredBuffer("ArrAnimationMatrix"))
	{
		MsgBoxAssert("����ƽ �Ž� �������� �ִϸ��̼��� �Ҽ� �����ϴ�. ��Ƽ���� ���ο� ArrAnimationMatrix�� ����ϰ� �ֽ��ϴ�.");
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
		MsgBoxAssert("�������� �ʴ� ��Ƽ���� �Դϴ�.");
		return nullptr;
	}

	if (true == Material->GetVertexShader()->IsStructuredBuffer("ArrAnimationMatrix"))
	{
		MsgBoxAssert("����ƽ �Ž� �������� �ִϸ��̼��� �Ҽ� �����ϴ�. ��Ƽ���� ���ο� ArrAnimationMatrix�� ����ϰ� �ֽ��ϴ�.");
		return nullptr;
	}

	return GameEngineFBXRenderer::SetFBXMesh(_fbxMeshName, _materialName, _meshIndex, _subsetIndex);
}

void GameEngineFBXStaticRenderer::Render(float _deltaTime)
{
	GameEngineFBXRenderer::Render(_deltaTime);
}
