#pragma once
#include "GameEngineFBXRenderer.h"

class FbxExAniData;
class GameEngineFBXMesh;
class GameEngineFBXAnimation;
class FBXRendererAnimation : public std::enable_shared_from_this<FBXRendererAnimation>
{
public:
	// SetFBX 본을 가지고 있는 매쉬
	GameEngineFBXMesh* Mesh;

	// 애니메이션을 가지고 있는 FBX
	GameEngineFBXAnimation* Animation;

	FbxExAniData* FBXAnimationData;

	// 이 애니메이션이 현재까지 얼마나 지났나.
	float CurFrameTime;
	float FrameTime; // 0.1
	UINT CurFrame;
	UINT Start;
	UINT End;

public:
	FBXRendererAnimation()
	{
	}

	~FBXRendererAnimation()
	{
	}
};

class GameEngineFBXAnimationRenderer : public GameEngineFBXRenderer
{
	//이 클래스의 존재 이유:
public:
	GameEngineFBXAnimationRenderer();
	~GameEngineFBXAnimationRenderer();

protected:
	GameEngineFBXAnimationRenderer(const GameEngineFBXAnimationRenderer& _other) = delete;
	GameEngineFBXAnimationRenderer(GameEngineFBXAnimationRenderer&& _other) noexcept = delete;

private:
	GameEngineFBXAnimationRenderer& operator=(const GameEngineFBXAnimationRenderer& _other) = delete;
	GameEngineFBXAnimationRenderer& operator=(const GameEngineFBXAnimationRenderer&& _other) = delete;


public:
	virtual void SetFBXMesh(const std::string& _fbxMeshName, const std::string& _materialName) override;
	virtual void SetFBXMesh(
		const std::string& _fbxMeshName,
		const std::string& _materialName,
		size_t _meshIndex,
		size_t _subsetIndex = 0
	) override;

	void CreateFBXAnimation(const std::string& _AnimationName, const std::string& _AnimationFBX);


private:
	std::map<std::string, std::shared_ptr<FBXRendererAnimation>> Animations;
	std::shared_ptr<FBXRendererAnimation> CurAnimation;
};

