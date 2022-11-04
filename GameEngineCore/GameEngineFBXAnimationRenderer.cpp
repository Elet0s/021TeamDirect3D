#include "PreCompile.h"
#include "GameEngineFBXAnimationRenderer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineFBXAnimation.h"	

GameEngineFBXAnimationRenderer::GameEngineFBXAnimationRenderer()
{
}

GameEngineFBXAnimationRenderer::~GameEngineFBXAnimationRenderer()
{
	Animations.clear();
}

void GameEngineFBXAnimationRenderer::SetFBXMesh(const std::string& _fbxMeshName, const std::string& _materialName)
{
	GameEngineMaterial* Material = GameEngineMaterial::Find(_materialName);

	if (nullptr == Material)
	{
		MsgBoxAssert("�������� �ʴ� ��Ƽ���� �Դϴ�.");
		return;
	}

	if (false == Material->GetVertexShader()->IsStructuredBuffer("ArrAnimationMatrix"))
	{
		MsgBoxAssert("FBX �ִϸ��̼� �������� �ִϸ��̼��� �Ұ����� ��Ƽ������ �����߽��ϴ�.");
		return;
	}

	GameEngineFBXRenderer::SetFBXMesh(_fbxMeshName, _materialName);
}

void GameEngineFBXAnimationRenderer::SetFBXMesh(
	const std::string& _fbxMeshName,
	const std::string& _materialName,
	size_t _meshIndex,
	size_t _subsetIndex
)
{
	GameEngineMaterial* Material = GameEngineMaterial::Find(_materialName);

	if (nullptr == Material)
	{
		MsgBoxAssert("�������� �ʴ� ��Ƽ���� �Դϴ�.");
		return;
	}

	if (false == Material->GetVertexShader()->IsStructuredBuffer("ArrAnimationMatrix"))
	{
		MsgBoxAssert("FBX �ִϸ��̼� �������� �ִϸ��̼��� �Ұ����� ��Ƽ������ �����߽��ϴ�.");
		return;
	}

	GameEngineFBXRenderer::SetFBXMesh(_fbxMeshName, _materialName, _meshIndex, _subsetIndex);
}

void GameEngineFBXAnimationRenderer::CreateFBXAnimation(
	const std::string& _AnimationName,
	const std::string& _AnimationFBX
)
{
	// ���� ���� fbx�� ���õǾ� �ִ��� �˻��Ѵ�.
	if (nullptr == GetFBXMesh())
	{
		MsgBoxAssert("��� FBX�� ���õǾ� ���� �ʽ��ϴ�.");
		return;
	}

	// �����ִ� �Լ��� �ܺο��� ȣ���ϸ� �˴ϴ�.

	if (Animations.end() != Animations.find(_AnimationName))
	{
		MsgBoxAssertString("�̹� �����ϴ� �̸��� �ִϸ��̼��Դϴ�." + _AnimationName);
		return;
	}

	GameEngineFBXAnimation* Animation = GameEngineFBXAnimation::Find(_AnimationFBX);

	if (nullptr == Animation)
	{
		MsgBoxAssertString("GameEngineFBXAnimation�� �������� �ʽ��ϴ�. " + _AnimationFBX);
		return;
	}

	std::shared_ptr<FBXRendererAnimation> NewAnimation = std::make_shared<FBXRendererAnimation>();

	NewAnimation->Mesh = GetFBXMesh();
	NewAnimation->Animation = Animation;

	renderOptionInst_.isAnimation_ = 1;

	Animations.insert(std::make_pair(_AnimationName, NewAnimation));

}
