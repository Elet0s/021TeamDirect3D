#pragma once
#include "GameEngineRes.h"
#include "GameEngineFBX.h"
#include "GameEngineVertexes.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineMesh.h"

// 지금설명하기 힘듬.
class FBXExIW
{
public:
	int Index;
	double Weight;
};


class FBXExMaterialSettingData
{
public:
	std::string Name;
	// 픽셀쉐이더에서 그냥 최종색상에 곱해주면 되는 색상.
	float4			 DifColor;
	float4			 AmbColor; // 빛
	float4			 SpcColor; // 빛
	float4			 EmvColor; // 빛
	float			 SpecularPower;		// 빛의 강도
	float			 TransparencyFactor;	// 빛의 강도
	float			 Shininess;			// 빛의 강도
	std::string DifTexturePath;	// 텍스처경로 
	std::string NorTexturePath; // 텍스처경로
	std::string SpcTexturePath; // 텍스처경로

	std::string DifTextureName;	// 텍스처경로 
	std::string NorTextureName; // 텍스처경로
	std::string SpcTextureName; // 텍스처경로

public:
	void Write(GameEngineFile* _File) const
	{
		_File->Write(Name);
		_File->Write(AmbColor); // 빛
		_File->Write(SpcColor); // 빛
		_File->Write(EmvColor); // 빛
		_File->Write(SpecularPower);
		_File->Write(TransparencyFactor);
		_File->Write(Shininess);
		_File->Write(DifTexturePath);	// 텍스처
		_File->Write(NorTexturePath); // 텍스처
		_File->Write(SpcTexturePath); // 텍스처
		_File->Write(DifTextureName);	// 텍스처
		_File->Write(NorTextureName); // 텍스처
		_File->Write(SpcTextureName); // 텍스처

	}

	void Read(GameEngineFile* _File)
	{
		_File->Read(Name);
		_File->Read(AmbColor); // 빛
		_File->Read(SpcColor); // 빛
		_File->Read(EmvColor); // 빛
		_File->Read(SpecularPower);
		_File->Read(TransparencyFactor);
		_File->Read(Shininess);
		_File->Read(DifTexturePath);	// 텍스처
		_File->Read(NorTexturePath); // 텍스처
		_File->Read(SpcTexturePath); // 텍스처
		_File->Read(DifTextureName);	// 텍스처
		_File->Read(NorTextureName); // 텍스처
		_File->Read(SpcTextureName); // 텍스처
	}


public:
	FBXExMaterialSettingData()
	{
	}
	~FBXExMaterialSettingData()
	{
	}
};

struct FBXExMeshInfo
{
	std::string Name;
	fbxsdk::FbxMesh* Mesh;
	bool bTriangulated;

	unsigned __int64 UniqueId;
	int FaceNum;
	int VertexNum;
	int MaterialNum;

	// 애니메이션과 연결되는 매쉬인가?
	bool bIsSkeletalMesh;
	std::string SkeletonRoot;
	int SkeletonElemNum;

	bool bIsLodGroup;
	std::string LODGroupName;
	int LodLevel;
	int MorphNum;

	FBXExMeshInfo()
	{
		Name;
		Mesh = nullptr;
		UniqueId = 0;
		FaceNum = 0;
		VertexNum = 0;
		bTriangulated = false;
		MaterialNum = 0;
		bIsSkeletalMesh = false;
		SkeletonRoot;
		SkeletonElemNum = 0;
		bIsLodGroup = false;
		LODGroupName;
		LodLevel = -1;
		MorphNum = 0;
	}
};


struct FBXRenderUnit
{
public:
	int VectorIndex;
	int IsLodLv;
	bool IsLod;

	float4 MinBoundBox;
	float4 MaxBoundBox;
	float4 BoundScaleBox;

	//       자신의 정보를 
//       들고 있던 node
//       의 mesh
//       이매쉬에서  이점들을 빼냈다라고 보면 됩니다.
//       얻어온 점들에 대한 모든 정보이고.
//       만약 필요하다면 더 얻어야 할수도 있다.
	std::map<FbxMesh*, std::vector<GameEngineVertex>*> FbxVertexMap;

	//       애니메이션이 있다면 채워져 있을겁니다.
	std::map<FbxMesh*, std::map<int, std::vector<FBXExIW>>> MapWI;

	std::vector<GameEngineVertex> Vertexs;

	// 머리
	// 다리 
	// 몸통
	std::vector<std::vector<unsigned int>> Indexs;

	std::vector<FBXExMaterialSettingData> MaterialData;


	GameEngineVertexBuffer* VertexBuffer;
	std::vector<GameEngineIndexBuffer*> IndexBuffers;

	std::vector<GameEngineMesh*> Meshs;

	FBXRenderUnit()
		:VectorIndex(0),
		IsLod(false),
		IsLodLv(-1),
		VertexBuffer(nullptr)
	{
	}

	~FBXRenderUnit()
	{
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
	static GameEngineFBXMesh* Load(const std::string& _Path);

	static GameEngineFBXMesh* Load(const std::string& _Path, const std::string& _Name);

	GameEngineMesh* GetGameEngineMesh(size_t _MeshIndex, size_t _SubIndex);

	const FBXExMaterialSettingData& GetMaterialSettingData(size_t _MeshIndex, size_t _SubIndex);

public:
	size_t GetRenderUnitCount()
	{
		return RenderUnitInfos.size();
	}

	size_t GetSubSetCount(size_t _RenderUnitIndex)
	{
		return RenderUnitInfos[_RenderUnitIndex].Indexs.size();
	}


protected:
	std::vector<FBXExMeshInfo> MeshInfos;
	std::vector<FBXRenderUnit> RenderUnitInfos;

private:
	void LoadMesh(const std::string& _Path, const std::string& _Name);

	void MeshLoad();

	void MeshNodeCheck();
	fbxsdk::FbxNode* RecursiveFindParentLodGroup(fbxsdk::FbxNode* parentNode);
	fbxsdk::FbxNode* FindLODGroupNode(fbxsdk::FbxNode* NodeLodGroup, int LodIndex, fbxsdk::FbxNode* NodeToFind);
	fbxsdk::FbxNode* RecursiveGetFirstMeshNode(fbxsdk::FbxNode* Node, fbxsdk::FbxNode* NodeToFind);

	void VertexBufferCheck();
	fbxsdk::FbxAMatrix ComputeTotalMatrix(fbxsdk::FbxNode* Node);
	bool IsOddNegativeScale(const fbxsdk::FbxAMatrix& TotalMatrix);
	void FBXRenderUnitMaterialSetting(fbxsdk::FbxNode* _Node, FBXRenderUnit* _RenderData);
	float4 MaterialColor(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _ColorName, const char* _FactorName);
	float MaterialFactor(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _FactorName);
	std::string MaterialTex(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _FactorName);

	void LoadBinormal(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int _Index);
	void LoadTangent(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int _Index);
	void LoadNormal(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int _Index);
	void DrawSetWeightAndIndexSetting(FBXRenderUnit* _DrawSet, fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxCluster* _Cluster, int _BoneIndex);
	void LoadUV(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int VertexCount, int _Index);
};