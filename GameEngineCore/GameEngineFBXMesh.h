#pragma once
#include "GameEngineRes.h"
#include "GameEngineFBX.h"
#include "GameEngineVertexes.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"


// ���ݼ����ϱ� ����.
class FbxExIW
{
public:
	int Index;
	double Weight;
};


class FbxExMaterialSettingData
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
	FbxExMaterialSettingData() {}
	~FbxExMaterialSettingData() {}
};

struct FbxExMeshInfo
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

	FbxExMeshInfo()
	{
		Name;
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


struct FbxRenderUnit
{
public:
	int Index;
	int IsLodLv;
	bool IsLod;

	//       �ڽ��� ������ 
	//       ��� �ִ� node
	//       �� mesh
	//       �̸Ž�����  �������� ���´ٶ�� ���� �˴ϴ�.
	//       ���� ���鿡 ���� ��� �����̰�.
	//       ���� �ʿ��ϴٸ� �� ���� �Ҽ��� �ִ�.
	std::map<FbxMesh*, std::vector<GameEngineVertex>*> FbxVertexMap;

	//       �ִϸ��̼��� �ִٸ� ä���� �����̴ϴ�.
	std::map<FbxMesh*, std::map<int, std::vector<FbxExIW>>> MapWI;

	std::vector<GameEngineVertex> Vertexs;

	std::vector<std::vector<std::vector<unsigned int>>> Indexs;

	std::vector<std::vector<FbxExMaterialSettingData>> MaterialData;


	std::vector<GameEngineVertexBuffer*> GameEngineVertexBuffers;
	std::vector<std::vector<GameEngineIndexBuffer*>> GameEngineIndexBuffers;
	// std::vector<std::vector<std::shared_ptr<DirectMesh>>> m_Mesh;


	// FbxMeshSet(const FbxMeshSet& _Other) = delete;
	// FbxMeshSet(FbxMeshSet&& _Other) noexcept = delete;
	// FbxMeshSet& operator=(const FbxMeshSet& _Other) = delete;
	// FbxMeshSet& operator=(FbxMeshSet&& _Other) noexcept = delete;

	FbxRenderUnit() :
		IsLod(false),
		IsLodLv(-1)
	{
	}

	~FbxRenderUnit()
	{
		//for (size_t i = 0; i < GameEngineVertexBuffers.size(); i++)
		//{
		//	if (nullptr == GameEngineVertexBuffers[i])
		//	{
		//		continue;
		//	}
		//	delete GameEngineVertexBuffers[i];
		//	GameEngineVertexBuffers[i] = nullptr;
		//}

		//// ����� ������
		//for (size_t i = 0; i < GameEngineIndexBuffers.size(); i++)
		//{
		//	for (size_t j = 0; j < GameEngineIndexBuffers[i].size(); j++)
		//	{
		//		if (nullptr == GameEngineIndexBuffers[i][j])
		//		{
		//			continue;
		//		}
		//		delete GameEngineIndexBuffers[i][j];
		//		GameEngineIndexBuffers[i][j] = nullptr;
		//	}
		//}

	}
};


// ���� :
class GameEngineFBXMesh : public GameEngineFBX, public GameEngineRes<GameEngineFBXMesh>
{
public:
	// constrcuter destructer
	GameEngineFBXMesh();
	~GameEngineFBXMesh();

	// delete Function
	GameEngineFBXMesh(const GameEngineFBXMesh& _Other) = delete;
	GameEngineFBXMesh(GameEngineFBXMesh&& _Other) noexcept = delete;
	GameEngineFBXMesh& operator=(const GameEngineFBXMesh& _Other) = delete;
	GameEngineFBXMesh& operator=(GameEngineFBXMesh&& _Other) noexcept = delete;

	static GameEngineFBXMesh* Load(const std::string& _Path)
	{
		return Load(_Path, GameEnginePath::GetFileName(_Path));
	}

	static GameEngineFBXMesh* Load(const std::string& _Path, const std::string& _Name);


protected:
	std::vector<FbxExMeshInfo> MeshInfos;
	std::vector<FbxRenderUnit> RenderUnitInfos;

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
	void FbxRenderUnitMaterialSetting(fbxsdk::FbxNode* _Node, FbxRenderUnit* _RenderData);
	float4 MaterialColor(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _ColorName, const char* _FactorName);
	float MaterialFactor(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _FactorName);
	std::string MaterialTex(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _FactorName);

};