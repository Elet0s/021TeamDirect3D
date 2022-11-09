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

	//FBX SDK 인터페이스 생성 및 초기화 함수. 
	bool CreateFBXSystemInitialize(const std::string& _path);

	//.fbx 안의 메쉬 기본 화전값 알아내는 함수.
	void FBXConvertScene();

	//
	void FBXInfoDebugFunction(fbxsdk::FbxNode* _RootNode);

	//전체 노드 순회.
	void RecursiveAllNodes(fbxsdk::FbxNode* _Node, std::function<void(fbxsdk::FbxNode*)> _Function = nullptr);



	//기하 형변환 함수들.

	//FBXMatrix->float4x4.
	float4x4 FBXMatrixToFloat4x4(const fbxsdk::FbxMatrix& _baseTransform);

	//float4x4->FBXAMatrix.
	fbxsdk::FbxAMatrix Float4x4ToFBXAMatrix(const float4x4& _matrix);

	//FBXVector4->float4
	float4 FBXVecToFloat4(const fbxsdk::FbxVector4& _baseVector);

	//FBXVector4->float4 트랜스폼 변환 함수. Z축 반전 주의.
	float4 FBXVecToTransform(const fbxsdk::FbxVector4& _baseVector);

	//FBXQuarternion->float4
	float4 FBXQuaternionToFloat4(const fbxsdk::FbxQuaternion& _baseQuarternion);

protected:
	fbxsdk::FbxManager* fbxManager_;	//
	fbxsdk::FbxIOSettings* ioSetting_;	//
	fbxsdk::FbxImporter* importer_;		//fbx파일 정보를 가져올 때 필요한 인터페이스.
	fbxsdk::FbxScene* scene_;			//
	fbxsdk::FbxNode* rootNode_;			//

	fbxsdk::FbxAMatrix convertMatrix_;
	fbxsdk::FbxAMatrix jointMatrix_;
	fbxsdk::FbxVector4 axisVector_;		//.fbx파일의 기본 회전값. 
	//파일 내 메쉬가 어느 방향을 향하고 있을 지 알 수 없으므로 기본 회전값을 알아둬야 한다.



};

