#pragma once
#include "GameEngineFBXRenderer.h"
#include "GameEngineRenderingEvent.h"

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
	std::shared_ptr<GameEngineFBXAnimation> Aniamtion;
	FbxExAniData* FBXAnimationData;

	UINT Start;
	UINT End;

	GameEngineRenderingEvent Info;

	bool Pause;
	bool bOnceStart;
	bool bOnceEnd;
	std::function<void(const GameEngineRenderingEvent&)> FrameEvent;
	std::function<void(const GameEngineRenderingEvent&)> EndEvent;
	std::function<void(const GameEngineRenderingEvent&)> StartEvent;
	std::function<void(const GameEngineRenderingEvent&, float)> TimeEvent;

	// Event

	void PauseSwtich();
	void Init(const std::string_view& _Name, int _Index);
	void Reset();
	void Update(float _DeltaTime);

public:
	FBXRendererAnimation()
		: Start(0)
		, End(0)
		, Pause(false)
		, bOnceStart(false)
		, bOnceEnd(false)
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

	void CreateFBXAnimation(const std::string& _AnimationName, const GameEngineRenderingEvent& _Desc, int _Index = 0);

	void ChangeAnimation(const std::string& _AnimationName);

	void Update(float _deltaTime) override;

	// �ִϸ��̼� ���ε�
	// ���� �����ӿ� ���´�.
	void AnimationBindStart(const std::string& _AnimationName, std::function<void(const GameEngineRenderingEvent&)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (Animations.end() == Animations.find(Name))
		{
			MsgBoxAssert("�������� �ʴ� �ִϸ��̼����� ü���� �Ϸ��� �߽��ϴ�.");
			return;
		}

		Animations[Name]->StartEvent = _Function;
	}
	// ������ �����ӿ� ���´�
	void AnimationBindEnd(const std::string& _AnimationName, std::function<void(const GameEngineRenderingEvent&)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (Animations.end() == Animations.find(Name))
		{
			MsgBoxAssert("�������� �ʴ� �ִϸ��̼����� ü���� �Ϸ��� �߽��ϴ�.");
			return;
		}

		Animations[Name]->EndEvent = _Function;
	}
	// �������� �ٲ𶧸��� ���´�
	void AnimationBindFrame(const std::string& _AnimationName, std::function<void(const GameEngineRenderingEvent&)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (Animations.end() == Animations.find(Name))
		{
			MsgBoxAssert("�������� �ʴ� �ִϸ��̼����� ü���� �Ϸ��� �߽��ϴ�.");
			return;
		}

		Animations[Name]->FrameEvent = _Function;
	}
	// Update
	void AnimationBindTime(const std::string& _AnimationName, std::function<void(const GameEngineRenderingEvent&, float)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (Animations.end() == Animations.find(Name))
		{
			MsgBoxAssert("�������� �ʴ� �ִϸ��̼����� ü���� �Ϸ��� �߽��ϴ�.");
			return;
		}

		Animations[Name]->TimeEvent = _Function;
	}

private:
	std::map<std::string, std::shared_ptr<FBXRendererAnimation>> Animations;
	std::shared_ptr<FBXRendererAnimation> CurAnimation;

	std::map<size_t, std::vector<float4x4>> AnimationBoneMatrixs;
	// std::map<size_t, std::vector<float4x4>> PrevAnimationBoneMatrixs;

	std::map<size_t, std::vector<AnimationBoneData>> AnimationBoneDatas;
};

