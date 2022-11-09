#pragma once
#include <fbxsdk.h>

#pragma comment(lib, "zlib-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "libfbxsdk-md.lib")

struct FBXNodeInfo
{
	std::string_view nodeName_;
	fbxsdk::FbxNode* node_;
};

class GameEngineFBX
{

protected:
	GameEngineFBX();
	~GameEngineFBX();

protected:
	GameEngineFBX(const GameEngineFBX& _other) = delete;
	GameEngineFBX(GameEngineFBX&& _other) noexcept = delete;

private:
	GameEngineFBX& operator=(const GameEngineFBX& _other) = delete;
	GameEngineFBX& operator=(const GameEngineFBX&& _other) = delete;

public:
	std::vector<FBXNodeInfo> CheckAllNodes();



protected:
	void FBXInit(const std::string& _path);

	//FBX SDK �������̽� ���� �� �ʱ�ȭ �Լ�. 
	bool CreateFBXSystemInitialize(const std::string& _path);

	//.fbx ���� �޽� �⺻ ȭ���� �˾Ƴ��� �Լ�.
	void FBXConvertScene();

	//
	void FBXInfoDebugFunction(fbxsdk::FbxNode* _RootNode);

	//��ü ��� ��ȸ.
	void RecursiveAllNodes(fbxsdk::FbxNode* _Node, std::function<void(fbxsdk::FbxNode*)> _Function = nullptr);



	//���� ����ȯ �Լ���.

	//FBXMatrix->float4x4.
	float4x4 FBXMatrixToFloat4x4(const fbxsdk::FbxMatrix& _baseTransform);

	//float4x4->FBXAMatrix.
	fbxsdk::FbxAMatrix Float4x4ToFBXAMatrix(const float4x4& _matrix);

	//FBXVector4->float4
	float4 FBXVecToFloat4(const fbxsdk::FbxVector4& _baseVector);

	//FBXVector4->float4 Ʈ������ ��ȯ �Լ�. Z�� ���� ����.
	float4 FBXVecToTransform(const fbxsdk::FbxVector4& _baseVector);

	//FBXQuarternion->float4
	float4 FBXQuaternionToFloat4(const fbxsdk::FbxQuaternion& _baseQuarternion);

protected:
	fbxsdk::FbxManager* fbxManager_;	//
	fbxsdk::FbxIOSettings* ioSetting_;	//
	fbxsdk::FbxImporter* importer_;		//fbx���� ������ ������ �� �ʿ��� �������̽�.
	fbxsdk::FbxScene* scene_;			//
	fbxsdk::FbxNode* rootNode_;			//

	fbxsdk::FbxAMatrix convertMatrix_;
	fbxsdk::FbxAMatrix jointMatrix_;
	fbxsdk::FbxVector4 axisVector_;		//.fbx������ �⺻ ȸ����. 
	//���� �� �޽��� ��� ������ ���ϰ� ���� �� �� �� �����Ƿ� �⺻ ȸ������ �˾Ƶ־� �Ѵ�.



};

