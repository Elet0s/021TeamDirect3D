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

	//형변환은 최소화.
	//메모리 배치는 최대한 연속적으로.
	//깊은 복사 == 복사생성자 사용 최소화.

public:
	std::vector<FBXNodeInfo> CheckAllNodes();



protected:
	bool CreateFBXSystemInitialize(const std::string& _path);

	void FBXConvertScene();

	float4x4 FBXMatrixToFloat4x4(const fbxsdk::FbxMatrix& _baseTransform);
	fbxsdk::FbxMatrix FLoat4x4ToFBXMatirx(const float4x4& _matrix);
	float4 FBXVecToFloat4(const fbxsdk::FbxVector4& _baseVector);
	float4 FBXVecToTransform(const fbxsdk::FbxVector4& _baseVector);
	float4 FBXQuaternionToFloat4(const fbxsdk::FbxQuaternion& _baseQuarternion);

	void RecursiveAllNodes(fbxsdk::FbxNode* _node, std::vector<FBXNodeInfo>& _allNodes);



protected:
	fbxsdk::FbxManager* fbxManager_;
	fbxsdk::FbxIOSettings* ioSetting_;
	fbxsdk::FbxImporter* importer_;
	fbxsdk::FbxScene* scene_;
	fbxsdk::FbxNode* rootNode_;

	fbxsdk::FbxAMatrix convertMatrix_;
	fbxsdk::FbxAMatrix jointMatrix_;
	fbxsdk::FbxVector4 axisVector_;



};

