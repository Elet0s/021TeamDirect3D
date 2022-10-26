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

	// 애니메이션과 연결되는 매쉬인가?
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
	//GameEngineFBXMesh 클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.


private:
	GameEngineFBXMesh();
	~GameEngineFBXMesh();
	//외부에서 제멋대로 리소스를 생성/삭제하는걸 막기 위해서 생성자/소멸자를 프라이빗으로 지정해서 외부 접근을 막는다.
	//이 프레임워크의 리소스는 반드시 소멸자가 아니라 ResourceDestroy()함수에서 제거해야 한다.
	//프로그램 끝날때까지 리소스삭제를 안하면 끝나는 문제지만 그래도 최대한 막아둔다.

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

