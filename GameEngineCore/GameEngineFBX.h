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
	// .fbx 파일에서 버텍스버퍼, 인덱스버퍼를 만드는데 필요한 정보를 추출하는데 필요한 인터페이스를 생성, 초기화하는 클래스.

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
	//FBX SDK 인터페이스 생성 및 초기화 함수. 
	bool CreateFBXSystemInitialize(const std::string& _path);

	void FBXConvertScene();

	void FBXInfoDebugFunction(fbxsdk::FbxNode* _RootNode);

	void RecursiveAllNodes(fbxsdk::FbxNode* _Node, std::function<void(fbxsdk::FbxNode*)> _Function = nullptr);



	//기하 형변환 함수들.

	float4x4 FBXMatrixToFloat4x4(const fbxsdk::FbxMatrix& _baseTransform);
	fbxsdk::FbxMatrix FLoat4x4ToFBXMatirx(const float4x4& _matrix);
	float4 FBXVecToFloat4(const fbxsdk::FbxVector4& _baseVector);
	float4 FBXVecToTransform(const fbxsdk::FbxVector4& _baseVector);
	float4 FBXQuaternionToFloat4(const fbxsdk::FbxQuaternion& _baseQuarternion);

protected:
	fbxsdk::FbxManager* fbxManager_;	//
	fbxsdk::FbxIOSettings* ioSetting_;	//
	fbxsdk::FbxImporter* importer_;		//fbx파일 정보를 가져올 때 필요한 인터페이스.
	fbxsdk::FbxScene* scene_;			//
	fbxsdk::FbxNode* rootNode_;			//

	fbxsdk::FbxAMatrix convertMatrix_;
	fbxsdk::FbxAMatrix jointMatrix_;
	fbxsdk::FbxVector4 axisVector_;



};

