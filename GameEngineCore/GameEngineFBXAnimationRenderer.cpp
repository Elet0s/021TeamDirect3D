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
		MsgBoxAssert("존재하지 않는 머티리얼 입니다.");
		return;
	}

	if (false == Material->GetVertexShader()->IsStructuredBuffer("ArrAnimationMatrix"))
	{
		MsgBoxAssert("FBX 애니메이션 랜더러에 애니메이션이 불가능한 머티리얼을 세팅했습니다.");
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
		MsgBoxAssert("존재하지 않는 머티리얼 입니다.");
		return;
	}

	if (false == Material->GetVertexShader()->IsStructuredBuffer("ArrAnimationMatrix"))
	{
		MsgBoxAssert("FBX 애니메이션 랜더러에 애니메이션이 불가능한 머티리얼을 세팅했습니다.");
		return;
	}

	GameEngineFBXRenderer::SetFBXMesh(_fbxMeshName, _materialName, _meshIndex, _subsetIndex);
}

void GameEngineFBXAnimationRenderer::CreateFBXAnimation(
	const std::string& _AnimationName,
	const std::string& _AnimationFBX
)
{
	// 본을 가진 fbx가 세팅되어 있는지 검사한다.
	if (nullptr == GetFBXMesh())
	{
		MsgBoxAssert("골격 FBX가 세팅되어 있지 않습니다.");
		return;
	}

	// 여기있는 함수를 외부에서 호출하면 됩니다.

	if (Animations.end() != Animations.find(_AnimationName))
	{
		MsgBoxAssertString("이미 존재하는 이름의 애니메이션입니다." + _AnimationName);
		return;
	}

	GameEngineFBXAnimation* Animation = GameEngineFBXAnimation::Find(_AnimationFBX);

	if (nullptr == Animation)
	{
		MsgBoxAssertString("GameEngineFBXAnimation이 존재하지 않습니다. " + _AnimationFBX);
		return;
	}

	std::shared_ptr<FBXRendererAnimation> NewAnimation = std::make_shared<FBXRendererAnimation>();

	NewAnimation->Mesh = GetFBXMesh();
	NewAnimation->Animation = Animation;

	renderOptionInst_.isAnimation_ = 1;

	Animations.insert(std::make_pair(_AnimationName, NewAnimation));

}
