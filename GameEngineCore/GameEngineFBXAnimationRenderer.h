#pragma once
#include "GameEngineFBXRenderer.h"

class FbxExAniData;
class GameEngineFBXMesh;
class GameEngineFBXAnimation;
class FBXRendererAnimation : public std::enable_shared_from_this<FBXRendererAnimation>
{
public:
	class GameEngineFBXAnimationRenderer* ParentRenderer;

	// SetFBX ���� ������ �ִ� �Ž�
	std::shared_ptr<GameEngineFBXMesh> Mesh;

	// �ִϸ��̼��� ������ �ִ� FBX
	std::shared_ptr<GameEngineFBXAnimation> Animation;

	FbxExAniData* FBXAnimationData;

	// �� �ִϸ��̼��� ������� �󸶳� ������.
	float CurFrameTime;
	float FrameTime; // 0.1
	UINT CurFrame;
	UINT Start;
	UINT End;


public:
	void Init(int _Index);
	void Reset();
	void Update(float _deltaTime);

public:
	FBXRendererAnimation()
		: CurFrameTime(0.0f)
		, FrameTime(0.0f) // 0.1
		, CurFrame(0)
		, Start(0)
		, End(0)
	{
	}

	~FBXRendererAnimation()
	{
	}
};

struct AnimationBoneData
{
public:
	int Index = -1;
	float4 Scale;
	float4 RotQuaternion;
	float4 Pos;
	float4 RotEuler;
};

class GameEngineFBXAnimationRenderer : public GameEngineFBXRenderer
{
	//�� Ŭ������ ���� ����:

	friend class FBXRendererAnimation;

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
	void SetFBXMesh(const std::string& _fbxMeshName, const std::string& _materialName) override;
	GameEngineRenderUnit* SetFBXMesh(
		const std::string& _fbxMeshName,
		const std::string& _materialName,
		size_t _meshIndex,
		size_t _subsetIndex = 0
	) override;

	void CreateFBXAnimation(const std::string& _AnimationName, const std::string& _AnimationFBX, int _Index = 0);

	void ChangeAnimation(const std::string& _AnimationName);

	void Update(float _deltaTime) override;

private:
	std::map<std::string, std::shared_ptr<FBXRendererAnimation>> Animations;
	std::shared_ptr<FBXRendererAnimation> CurAnimation;

	std::map<size_t, std::vector<float4x4>> AnimationBoneMatrixs;
	// std::map<size_t, std::vector<float4x4>> PrevAnimationBoneMatrixs;

	std::map<size_t, std::vector<AnimationBoneData>> AnimationBoneDatas;
};

