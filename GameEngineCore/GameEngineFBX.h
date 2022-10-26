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
	// .fbx ���Ͽ��� ���ؽ�����, �ε������۸� ����µ� �ʿ��� ������ �����ϴµ� �ʿ��� �������̽��� ����, �ʱ�ȭ�ϴ� Ŭ����.

protected:
	GameEngineFBX();
	~GameEngineFBX();

protected:
	GameEngineFBX(const GameEngineFBX& _other) = delete;
	GameEngineFBX(GameEngineFBX&& _other) noexcept = delete;

private:
	GameEngineFBX& operator=(const GameEngineFBX& _other) = delete;
	GameEngineFBX& operator=(const GameEngineFBX&& _other) = delete;

	//����ȯ�� �ּ�ȭ.
	//�޸� ��ġ�� �ִ��� ����������.
	//���� ���� == ��������� ��� �ּ�ȭ.

public:
	std::vector<FBXNodeInfo> CheckAllNodes();



protected:
	//FBX SDK �������̽� ���� �� �ʱ�ȭ �Լ�. 
	bool CreateFBXSystemInitialize(const std::string& _path);

	void FBXConvertScene();

	void FBXInfoDebugFunction(fbxsdk::FbxNode* _RootNode);

	void RecursiveAllNodes(fbxsdk::FbxNode* _Node, std::function<void(fbxsdk::FbxNode*)> _Function = nullptr);



	//���� ����ȯ �Լ���.

	float4x4 FBXMatrixToFloat4x4(const fbxsdk::FbxMatrix& _baseTransform);
	fbxsdk::FbxMatrix FLoat4x4ToFBXMatirx(const float4x4& _matrix);
	float4 FBXVecToFloat4(const fbxsdk::FbxVector4& _baseVector);
	float4 FBXVecToTransform(const fbxsdk::FbxVector4& _baseVector);
	float4 FBXQuaternionToFloat4(const fbxsdk::FbxQuaternion& _baseQuarternion);

protected:
	fbxsdk::FbxManager* fbxManager_;	//
	fbxsdk::FbxIOSettings* ioSetting_;	//
	fbxsdk::FbxImporter* importer_;		//fbx���� ������ ������ �� �ʿ��� �������̽�.
	fbxsdk::FbxScene* scene_;			//
	fbxsdk::FbxNode* rootNode_;			//

	fbxsdk::FbxAMatrix convertMatrix_;
	fbxsdk::FbxAMatrix jointMatrix_;
	fbxsdk::FbxVector4 axisVector_;



};

