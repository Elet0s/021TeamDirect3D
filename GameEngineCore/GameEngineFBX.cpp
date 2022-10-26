#include "PreCompile.h"
#include "GameEngineFBX.h"

GameEngineFBX::GameEngineFBX()
	: fbxManager_(nullptr),
	ioSetting_(nullptr),
	importer_(nullptr),
	scene_(nullptr),
	rootNode_(nullptr)
{
}

GameEngineFBX::~GameEngineFBX()
{
	if (nullptr != scene_)
	{
		scene_->Destroy();
		scene_ = nullptr;
	}
	if (nullptr != importer_)
	{
		importer_->Destroy();
		importer_ = nullptr;
	}
	if (nullptr != ioSetting_)
	{
		ioSetting_->Destroy();
		ioSetting_ = nullptr;
	}
	if (nullptr != fbxManager_)
	{
		fbxManager_->Destroy();
		fbxManager_ = nullptr;
	}
}

std::vector<FBXNodeInfo> GameEngineFBX::CheckAllNodes()
{
	std::vector<FBXNodeInfo> AllNode;

	RecursiveAllNodes(rootNode_);

	return AllNode;
}

bool GameEngineFBX::CreateFBXSystemInitialize(const std::string& _path)
{
	fbxManager_ = fbxsdk::FbxManager::Create();
	//FBX매니저 생성.

	if (nullptr == fbxManager_)
	{
		MsgBoxAssert("FBX 매니저 생성에 실패했습니다.");
		return false;
	}

	// FBX파일을 읽는 방법을 정의한다.
	// IO적인 측면에서 정의내리는 단계.
	// these defines are used for hierarchical properties names 구조도를 타고 읽겠다.
	ioSetting_ = fbxsdk::FbxIOSettings::Create(fbxManager_, IOSROOT);

	// 실제 FBX파일의 정보를 우리에게 함수들로 제공해주는 클래스 Import
	importer_ = fbxsdk::FbxImporter::Create(fbxManager_, "");

	if (false == importer_->Initialize(GameEngineString::AnsiToUTF8Return(_path).c_str(), -1, ioSetting_))
		//언어 관련 문제가 생기는것을 방지하기 위해 모든 fbx의 모든 문자열은 UTF-8 형식으로 되어있다.
	{
		importer_->Destroy();
		ioSetting_->Destroy();
		MsgBoxAssert("FBX 로드 이니셜라이즈 실패.");
		return false;
	}

	scene_ = fbxsdk::FbxScene::Create(fbxManager_, "");
	//신 생성.

	if (nullptr == scene_)
	{
		MsgBoxAssert("FBX 씬생성 실패.");
		return false;
	}

	// Scene의 내용을 채워준다.
	if (false == importer_->Import(scene_))
	{
		MsgBoxAssert("FBX 임포트 실패.");
		return false;
	}

	return true;
}

void GameEngineFBX::FBXConvertScene()
{
	this->axisVector_ = { 0.0f, 0.0f, 0.0f, 1.0f };

	fbxsdk::FbxAxisSystem::EFrontVector FrontVector = (fbxsdk::FbxAxisSystem::EFrontVector)-fbxsdk::FbxAxisSystem::eParityOdd;
	fbxsdk::FbxAxisSystem::EUpVector UpVector = fbxsdk::FbxAxisSystem::eYAxis;
	fbxsdk::FbxAxisSystem::ECoordSystem CooreSystem = fbxsdk::FbxAxisSystem::ECoordSystem::eRightHanded;

	fbxsdk::FbxAxisSystem EngineAxisSystem(UpVector, FrontVector, CooreSystem);
	// fbxsdk::FbxAxisSystem EngineAxisSystem(fbxsdk::FbxAxisSystem::EPreDefinedAxisSystem::eDirectX);

	fbxsdk::FbxAxisSystem SourceAxisSystem = this->scene_->GetGlobalSettings().GetAxisSystem();

	// 이건 이제 컨버트 해줘야 하는겁니다.
	if (SourceAxisSystem != EngineAxisSystem)
	{
		// 먼저 루트를 지워.
		fbxsdk::FbxRootNodeUtility::RemoveAllFbxRoots(scene_);
		// 루트가 새롭게 만들어진다.
		EngineAxisSystem.ConvertScene(scene_);

		// 매쉬의 기존 매트릭스를 가져옵니다.
		fbxsdk::FbxAMatrix SourceMatrix;
		SourceAxisSystem.GetMatrix(SourceMatrix);

		fbxsdk::FbxAMatrix EngineMatrix;
		EngineAxisSystem.GetMatrix(EngineMatrix);

		this->convertMatrix_ = SourceMatrix.Inverse() * EngineMatrix;
	}

	int OriginUpSign = 0;
	int OriginFrontSign = 0;
	int EngineUpSign = 0;
	int EngineFrontSign = 0;

	fbxsdk::FbxAxisSystem::EFrontVector OriginFrontVector = SourceAxisSystem.GetFrontVector(OriginFrontSign);
	fbxsdk::FbxAxisSystem::EFrontVector EngineFrontVector = EngineAxisSystem.GetFrontVector(EngineFrontSign);

	fbxsdk::FbxAxisSystem::EUpVector OriginUpVector = SourceAxisSystem.GetUpVector(OriginUpSign);
	fbxsdk::FbxAxisSystem::EUpVector EngineUpVector = EngineAxisSystem.GetUpVector(EngineUpSign);

	fbxsdk::FbxAxisSystem::ECoordSystem  OriginCoordSystem = SourceAxisSystem.GetCoorSystem();
	fbxsdk::FbxAxisSystem::ECoordSystem  EngineCoordSystem = EngineAxisSystem.GetCoorSystem();

	if (OriginUpVector == EngineUpVector && OriginUpSign == EngineUpSign)
	{
		if (OriginFrontSign != EngineFrontSign && OriginCoordSystem == EngineCoordSystem)
		{
			axisVector_.mData[static_cast<int>(OriginUpVector) - 1] += 180;
		}
	}
	else if (OriginUpVector == EngineUpVector && OriginUpSign != EngineUpSign)
	{
		if (OriginUpVector == fbxsdk::FbxAxisSystem::EUpVector::eXAxis)
		{
			axisVector_.mData[1] += 180.0;
		}
		else
		{
			axisVector_.mData[0] += 180.0;
		}

		if (OriginFrontSign != EngineFrontSign && OriginCoordSystem == EngineCoordSystem)
		{
			axisVector_.mData[static_cast<int>(OriginUpVector) - 1] += 180.0;
		}
	}
	else if (OriginUpVector == fbxsdk::FbxAxisSystem::EUpVector::eXAxis)
	{
		//origin up vector 가 x up vector 일때를 아직 만나보지를 못했다.

		axisVector_.mData[1] += OriginUpSign * 90.0;
	}
	else
	{
		axisVector_.mData[0] += OriginUpSign * 90.0;
		if (OriginUpSign != EngineFrontSign)
		{
			axisVector_.mData[static_cast<int>(OriginUpVector) - 1] += OriginUpSign * 180.0;
		}
	}

	this->jointMatrix_.SetR(axisVector_);

	if (true == jointMatrix_.IsIdentity())
	{
		jointMatrix_ = convertMatrix_;
	}

	// 애니메이션도 행렬의 집합인데.
	scene_->GetAnimationEvaluator()->Reset();

	// 핵심인 루트노드를 얻어와야 한다.
	rootNode_ = scene_->GetRootNode();

	if (nullptr == rootNode_)
	{
		MsgBoxAssert("루트노드생성에 실패했습니다.");
	}

	fbxsdk::FbxGeometryConverter Con(fbxManager_);

	// 기본적으로 모든 FBX는 랜더링을 위한 삼각측량이 안되어있는 상태인데
	// 이 삼각측량 함수를 통해서 각 버텍스들을 우리가 사용할 수 있는 구조로 만들어준다.
	if (false == Con.Triangulate(scene_, true))
	{
		MsgBoxAssert("삼각화에 실패했습니다.");
	}

	return;
}

void GameEngineFBX::RecursiveAllNodes(fbxsdk::FbxNode* _Node, std::function<void(fbxsdk::FbxNode*)> _Function /*= nullptr*/)
{
	if (nullptr != _Function)
	{
		_Function(_Node);
	}

	//FBXNodeInfo& NewNodeInfo = _AllNode.emplace_back();
	//NewNodeInfo.Name = _Node->GetName();
	//NewNodeInfo.Node = _Node;

	int Count = _Node->GetChildCount();

	for (int i = 0; i < Count; i++)
	{
		fbxsdk::FbxNode* Node = _Node->GetChild(i);
		RecursiveAllNodes(Node);
	}

	//std::vector<T,Allocator>::emplace_back<class... Args>(): std::vector<T,Allocator>::push_back()은 
	// 주어진 객체를 복사하거나 지정된 자료형의 생성자로 임시 객체(rValue)를 생성하고 
	// 그 임시 객체(rValue)를 다시 복사 생성해서 벡터에 넣는데, emplace_back<>()은 넣어준 변수에 맞는 생성자를 호출해서 
	// 임시 객체 없이 바로 벡터에 삽입해서 효율이 더 좋다고 한다. 
	// 그리고 emplace_back<>()은 생성한 객체의 참조를 바로 받아볼 수도 있다.
	//하지만, 가변인자를 매개변수로 받는 emplace_back<>()은 어떤 생성자를 호출해서 생성 삽입할 지 알 수 없어서, 
	// push_back()이라면 거부할 비정상 인자도 emplace_back<>()은 그대로 받아서 저장해버리기때문에 
	// 컴파일 단계가 아니라 런타임 중간에 문제를 일으킬 수 있으니 주의해야 한다고 한다. 

}

void GameEngineFBX::FBXInfoDebugFunction(fbxsdk::FbxNode* _RootNode)
{
	if (nullptr == _RootNode)
	{
		return;
	}

	std::string Name = _RootNode->GetName();
}

float4x4 GameEngineFBX::FBXMatrixToFloat4x4(const fbxsdk::FbxMatrix& _baseTransform)
{
	float4x4 mat;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			mat.arr2D[y][x] = (float)_baseTransform.Get(y, x);
		}
	}

	return mat;
}

fbxsdk::FbxMatrix GameEngineFBX::FLoat4x4ToFBXMatirx(const float4x4& _matrix)
{
	fbxsdk::FbxAMatrix mat;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			mat.mData[y].mData[x] = _matrix.arr2D[y][x];
		}
	}

	return mat;
}

float4 GameEngineFBX::FBXVecToFloat4(const fbxsdk::FbxVector4& _baseVector)
{
	float4 vec;
	vec.arr1D[0] = (float)_baseVector.mData[0];
	vec.arr1D[1] = (float)_baseVector.mData[1];
	vec.arr1D[2] = (float)_baseVector.mData[2];
	vec.arr1D[3] = (float)_baseVector.mData[3];

	return vec;
}

float4 GameEngineFBX::FBXVecToTransform(const fbxsdk::FbxVector4& _baseVector)
{
	float4 vec;
	vec.arr1D[0] = (float)_baseVector.mData[0];
	vec.arr1D[1] = (float)_baseVector.mData[1];
	vec.arr1D[2] = -(float)_baseVector.mData[2];	//fbx는 z좌표가 뒤집혀 있다.
	vec.arr1D[3] = (float)_baseVector.mData[3];

	return vec;
}

float4 GameEngineFBX::FBXQuaternionToFloat4(const fbxsdk::FbxQuaternion& _baseQuarternion)
{
	float4 Vec;
	Vec.arr1D[0] = (float)_baseQuarternion.mData[0];
	Vec.arr1D[1] = (float)_baseQuarternion.mData[1];
	Vec.arr1D[2] = -(float)_baseQuarternion.mData[2];
	Vec.arr1D[3] = -(float)_baseQuarternion.mData[3];
	return Vec;
}