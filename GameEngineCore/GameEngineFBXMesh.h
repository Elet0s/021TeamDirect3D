#pragma once
#include "GameEngineRes.h"
#include "GameEngineFBX.h"

struct FBXExMeshInfo
{
	std::string meshName_;
	fbxsdk::FbxMesh* mesh_;
	bool isTriangulated_;

	unsigned __int64 UniqueId;
	int FaceNum;
	int VertexNum;
	int MaterialNum;

	// �ִϸ��̼ǰ� ����Ǵ� �Ž��ΰ�?
	bool bIsSkelMesh;
	std::string SkeletonRoot;
	int SkeletonElemNum;

	bool bIsLodGroup;
	std::string LODGroup;
	int LODLevel;
	int MorphNum;

	FBXExMeshInfo()
	{
		meshName_ = "";
		UniqueId = 0;
		FaceNum = 0;
		VertexNum = 0;
		isTriangulated_ = false;
		MaterialNum = 0;
		bIsSkelMesh = false;
		SkeletonRoot = "";
		SkeletonElemNum = 0;
		bIsLodGroup = false;
		LODGroup = "";
		LODLevel = -1;
		MorphNum = 0;
	}
};

class GameEngineFBXMesh : public GameEngineRes<GameEngineFBXMesh>, public GameEngineFBX
{
	friend GameEngineRes<GameEngineFBXMesh>;
	//GameEngineFBXMesh Ŭ������ �����̺� �Ҹ��ڸ� GameEngineResŬ�������� ȣ���ϱ� ���� ���.


private:
	GameEngineFBXMesh();
	~GameEngineFBXMesh();
	//�ܺο��� ���ڴ�� ���ҽ��� ����/�����ϴ°� ���� ���ؼ� ������/�Ҹ��ڸ� �����̺����� �����ؼ� �ܺ� ������ ���´�.
	//�� �����ӿ�ũ�� ���ҽ��� �ݵ�� �Ҹ��ڰ� �ƴ϶� ResourceDestroy()�Լ����� �����ؾ� �Ѵ�.
	//���α׷� ���������� ���ҽ������� ���ϸ� ������ �������� �׷��� �ִ��� ���Ƶд�.

	GameEngineFBXMesh(const GameEngineFBXMesh& _other) = delete;
	GameEngineFBXMesh(GameEngineFBXMesh&& _other) noexcept = delete;
	GameEngineFBXMesh& operator=(const GameEngineFBXMesh& _other) = delete;
	GameEngineFBXMesh& operator=(const GameEngineFBXMesh&& _other) = delete;


public:
	static GameEngineFBXMesh* Load(const std::string& _path);
	static GameEngineFBXMesh* Load(const std::string& _path, const std::string& _name);


protected:
	std::vector<FBXExMeshInfo> meshInfos_;


private:
	void LoadMesh(const std::string& _path, const std::string& _name);
	void MeshLoad();

};

