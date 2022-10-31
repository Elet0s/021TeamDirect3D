#pragma once
#include "GameEngineRes.h"
#include "GameEngineFBX.h"
#include "GameEngineVertexes.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineMesh.h"

// ���ݼ����ϱ� ����.
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
	// �ȼ����̴����� �׳� �������� �����ָ� �Ǵ� ����.
	float4			 DifColor;
	float4			 AmbColor; // ��
	float4			 SpcColor; // ��
	float4			 EmvColor; // ��
	float			 SpecularPower;		// ���� ����
	float			 TransparencyFactor;	// ���� ����
	float			 Shininess;			// ���� ����
	std::string DifTexturePath;	// �ؽ�ó��� 
	std::string NorTexturePath; // �ؽ�ó���
	std::string SpcTexturePath; // �ؽ�ó���

	std::string DifTextureName;	// �ؽ�ó��� 
	std::string NorTextureName; // �ؽ�ó���
	std::string SpcTextureName; // �ؽ�ó���

public:
	void Write(GameEngineFile* _File) const
	{
		_File->Write(Name);
		_File->Write(AmbColor); // ��
		_File->Write(SpcColor); // ��
		_File->Write(EmvColor); // ��
		_File->Write(SpecularPower);
		_File->Write(TransparencyFactor);
		_File->Write(Shininess);
		_File->Write(DifTexturePath);	// �ؽ�ó
		_File->Write(NorTexturePath); // �ؽ�ó
		_File->Write(SpcTexturePath); // �ؽ�ó
		_File->Write(DifTextureName);	// �ؽ�ó
		_File->Write(NorTextureName); // �ؽ�ó
		_File->Write(SpcTextureName); // �ؽ�ó

	}

	void Read(GameEngineFile* _File)
	{
		_File->Read(Name);
		_File->Read(AmbColor); // ��
		_File->Read(SpcColor); // ��
		_File->Read(EmvColor); // ��
		_File->Read(SpecularPower);
		_File->Read(TransparencyFactor);
		_File->Read(Shininess);
		_File->Read(DifTexturePath);	// �ؽ�ó
		_File->Read(NorTexturePath); // �ؽ�ó
		_File->Read(SpcTexturePath); // �ؽ�ó
		_File->Read(DifTextureName);	// �ؽ�ó
		_File->Read(NorTextureName); // �ؽ�ó
		_File->Read(SpcTextureName); // �ؽ�ó
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

	// �ִϸ��̼ǰ� ����Ǵ� �Ž��ΰ�?
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

	//       �ڽ��� ������ 
//       ��� �ִ� node
//       �� mesh
//       �̸Ž�����  �������� ���´ٶ�� ���� �˴ϴ�.
//       ���� ���鿡 ���� ��� �����̰�.
//       ���� �ʿ��ϴٸ� �� ���� �Ҽ��� �ִ�.
	std::map<FbxMesh*, std::vector<GameEngineVertex>*> FbxVertexMap;

	//       �ִϸ��̼��� �ִٸ� ä���� �����̴ϴ�.
	std::map<FbxMesh*, std::map<int, std::vector<FBXExIW>>> MapWI;

	std::vector<GameEngineVertex> Vertexs;

	// �Ӹ�
	// �ٸ� 
	// ����
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