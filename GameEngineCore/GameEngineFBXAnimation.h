#pragma once
#include "GameEngineRes.h"
#include "GameEngineFBX.h"

class FbxExBoneFrameData : public GameEngineSerializer
{
public:
	float4 S; // ũ
	float4 Q; // ��
	float4 T; // ��
	double Time;
	float4x4 FrameMat;

	fbxsdk::FbxAMatrix GlobalAnimation;
	fbxsdk::FbxAMatrix LocalAnimation;

	FbxExBoneFrameData() {

	}

	void Write(GameEngineFile& _File) override
	{
		_File.Write(S);
		_File.Write(Q);
		_File.Write(T);
		_File.Write(Time);
		_File.Write(FrameMat);
		_File.Write(GlobalAnimation);
		_File.Write(LocalAnimation);
	}

	void Read(GameEngineFile& _File) override
	{
		_File.Read(S);
		_File.Read(Q);
		_File.Read(T);
		_File.Read(Time);
		_File.Read(FrameMat);
		_File.Read(GlobalAnimation);
		_File.Read(LocalAnimation);
	}

};

class FbxExBoneFrame : public GameEngineSerializer
{
public:
	int BoneIndex;
	int BoneParentIndex;

	// 120�������̾�.
	std::vector<FbxExBoneFrameData> BoneMatData;

	FbxExBoneFrame() {

	}

	void Write(GameEngineFile& _File) override
	{
		_File.Write(BoneIndex);
		_File.Write(BoneParentIndex);
		_File.Write(BoneMatData);
	}

	void Read(GameEngineFile& _File) override
	{
		_File.Read(BoneIndex);
		_File.Read(BoneParentIndex);
		_File.Read(BoneMatData);
	}
};

// Take 001�̶�� �ִϸ��̼��� �ִµ�.
class FbxExAniData : public GameEngineSerializer
{
public:
	std::string				AniName;
	fbxsdk::FbxTime			StartTime; // ������ �ִϸ��̼� �ð�
	fbxsdk::FbxTime			EndTime; // 
	fbxsdk::FbxLongLong		TimeStartCount;
	fbxsdk::FbxLongLong		TimeEndCount;
	fbxsdk::FbxLongLong		FrameCount;
	fbxsdk::FbxTime::EMode	TimeMode;
	__int64					FbxModeCount;
	double					FbxModeRate;

	// 0~100
	// meshInfo 1�� ��ü 20
	// meshInfo 1�� ��ü
	// meshInfo 1�� ���� 20
	std::map<size_t, std::vector<FbxExBoneFrame>> AniFrameData;

	void Write(GameEngineFile& _File) override
	{
		_File.Write(AniName);
		_File.Write(StartTime);
		_File.Write(EndTime);
		_File.Write(TimeStartCount);
		_File.Write(TimeEndCount);
		_File.Write(FrameCount);
		_File.Write(TimeMode);
		_File.Write(FbxModeCount);
		_File.Write(FbxModeRate);
		_File.Write(AniFrameData);
	}

	void Read(GameEngineFile& _File) override
	{
		_File.Read(AniName);
		_File.Read(StartTime);
		_File.Read(EndTime);
		_File.Read(TimeStartCount);
		_File.Read(TimeEndCount);
		_File.Read(FrameCount);
		_File.Read(TimeMode);
		_File.Read(FbxModeCount);
		_File.Read(FbxModeRate);
		_File.Read(AniFrameData);
	}

public:
	float FrameTime(int _Frame)
	{
		fbxsdk::FbxTime tTime = {};
		tTime.SetFrame(_Frame, TimeMode);

		return (float)tTime.GetSecondDouble();
	}

public:
	__int64 FrameModeRateInt()
	{
		return static_cast<__int64>(fbxsdk::FbxGetFrameRate(TimeMode));
	}
	double FrameModeRateDouble()
	{
		return fbxsdk::FbxGetFrameRate(TimeMode);
	}

	float FrameModeRateFloat()
	{
		return static_cast<float>(fbxsdk::FbxGetFrameRate(TimeMode));
	}


public:
	FbxExAniData() : AniName(""), StartTime(0), EndTime(0), TimeStartCount(0), TimeEndCount(0), FrameCount(0), FbxModeCount(0), FbxModeRate(0.0), TimeMode()
	{}
	~FbxExAniData() {}
};

class GameEngineFBXAnimationRenderer;
class GameEngineFBXMesh;
class GameEngineFBXAnimation : public GameEngineRes<GameEngineFBXAnimation>, public GameEngineFBX
{

public:
	GameEngineFBXAnimation();
	~GameEngineFBXAnimation();

private:

	GameEngineFBXAnimation(const GameEngineFBXAnimation& _other) = delete;
	GameEngineFBXAnimation(GameEngineFBXAnimation&& _other) noexcept = delete;
	GameEngineFBXAnimation& operator=(const GameEngineFBXAnimation& _other) = delete;
	GameEngineFBXAnimation& operator=(const GameEngineFBXAnimation&& _other) = delete;


public:
	static std::shared_ptr<GameEngineFBXAnimation> Load(const std::string& _Path)
	{
		return Load(_Path, GameEnginePath::GetFileName(_Path));
	}

	static std::shared_ptr<GameEngineFBXAnimation> Load(const std::string& _Path, const std::string& _Name);


	// �ִϸ��̼� ������ ��İ��.
	// ���⼭ �������� �ǹ̴� Animation TimeEndCount - TimeStartCount
	void AnimationMatrixLoad(std::shared_ptr <GameEngineFBXMesh> _Mesh, std::shared_ptr<GameEngineFBXAnimationRenderer> _Renderer, int _AnimationIndex);

	FbxExAniData* GetAnimationData(int _Index)
	{
		if (AnimationDatas.size() <= _Index)
		{
			MsgBoxAssert("�ִϸ��̼� ������ ������ �Ѿ���ϴ�");
		}

		return &AnimationDatas[_Index];
	}

	void UserLoad(const std::string_view& _Path);
	void UserSave(const std::string_view& _Path);

protected:
	void LoadMesh(const std::string& _Path, const std::string& _Name);

	// �ִϸ��̼��� ����� ��Ʈ����Ʈ�� �� eMesh�� �༮���� ��������Ƿ� �׳༮���Լ� �ִϸ��̼� �ε� �Լ��� �����Ű�� ������ �Ѵ�.
	void ProcessAnimationLoad(std::shared_ptr<GameEngineFBXMesh> _Mesh, fbxsdk::FbxNode* pNode, int _index);
	bool AnimationLoad(std::shared_ptr<GameEngineFBXMesh> _Mesh, fbxsdk::FbxNode* _Node, int AnimationIndex);
	void ProcessAnimationCheckState(std::shared_ptr<GameEngineFBXMesh> _Fbx, int userAniDataIndex);
	fbxsdk::FbxAMatrix GetGeometryTransformation(fbxsdk::FbxNode* pNode);

	// ��
	// ���̵�
	// ����
	std::vector<FbxExAniData> AnimationDatas;

private:
	bool CheckAnimation();
};

