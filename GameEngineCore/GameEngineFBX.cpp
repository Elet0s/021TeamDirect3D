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

void GameEngineFBX::FBXInit(const std::string& _path)
{
	if (false == CreateFBXSystemInitialize(_path))
	{
		MsgBoxAssert("�ý��� �ε忡 �����߽��ϴ�.");
	}

	FBXConvertScene();
}

bool GameEngineFBX::CreateFBXSystemInitialize(const std::string& _path)
{
	if (nullptr == fbxManager_)
	{
		fbxManager_ = fbxsdk::FbxManager::Create();

		if (nullptr == fbxManager_)
		{
			MsgBoxAssert("FBX �Ŵ��� ������ �����߽��ϴ�.");
			return false;
		}
	}


	// FBX������ �д� ����� �����Ѵ�.
	// IO���� ���鿡�� ���ǳ����� �ܰ�.
	// these defines are used for hierarchical properties names �������� Ÿ�� �аڴ�.
	ioSetting_ = fbxsdk::FbxIOSettings::Create(fbxManager_, IOSROOT);

	// ���� FBX������ ������ �츮���� �Լ���� �������ִ� Ŭ���� Import
	importer_ = fbxsdk::FbxImporter::Create(fbxManager_, "");

	if (false == importer_->Initialize(GameEngineString::AnsiToUTF8Return(_path).c_str(), -1, ioSetting_))
		//��� ���� ������ ����°��� �����ϱ� ���� ��� fbx�� ��� ���ڿ��� UTF-8 �������� �Ǿ��ִ�.
	{
		importer_->Destroy();
		ioSetting_->Destroy();
		MsgBoxAssert("FBX �ε� �̴ϼȶ����� ����.");
		return false;
	}

	scene_ = fbxsdk::FbxScene::Create(fbxManager_, "");
	//�� ����.

	if (nullptr == scene_)
	{
		MsgBoxAssert("FBX ������ ����.");
		return false;
	}

	// Scene�� ������ ä���ش�.
	if (false == importer_->Import(scene_))
	{
		MsgBoxAssert("FBX ����Ʈ ����.");
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

	// �̰� ���� ����Ʈ ����� �ϴ°̴ϴ�.
	if (SourceAxisSystem != EngineAxisSystem)
	{
		// ���� ��Ʈ�� ����.
		fbxsdk::FbxRootNodeUtility::RemoveAllFbxRoots(scene_);
		// ��Ʈ�� ���Ӱ� ���������.
		EngineAxisSystem.ConvertScene(scene_);

		// �Ž��� ���� ��Ʈ������ �����ɴϴ�.
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
		//origin up vector �� x up vector �϶��� ���� ���������� ���ߴ�.

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

	// �ִϸ��̼ǵ� ����� �����ε�.
	scene_->GetAnimationEvaluator()->Reset();

	// �ٽ��� ��Ʈ��带 ���;� �Ѵ�.
	rootNode_ = scene_->GetRootNode();

	if (nullptr == rootNode_)
	{
		MsgBoxAssert("��Ʈ�������� �����߽��ϴ�.");
	}

	fbxsdk::FbxGeometryConverter Con(fbxManager_);

	// �⺻������ ��� FBX�� �������� ���� �ﰢ������ �ȵǾ��ִ� �����ε�
	// �� �ﰢ���� �Լ��� ���ؼ� �� ���ؽ����� �츮�� ����� �� �ִ� ������ ������ش�.
	if (false == Con.Triangulate(scene_, true))
	{
		MsgBoxAssert("�ﰢȭ�� �����߽��ϴ�.");
	}

	return;
}

void GameEngineFBX::RecursiveAllNodes(fbxsdk::FbxNode* _Node, std::function<void(fbxsdk::FbxNode*)> _Function /*= nullptr*/)
{
	if (nullptr != _Function)
	{
		_Function(_Node);
	}

	int Count = _Node->GetChildCount();

	for (int i = 0; i < Count; i++)
	{
		fbxsdk::FbxNode* Node = _Node->GetChild(i);
		RecursiveAllNodes(Node);
	}
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
	vec.arr1D[2] = -(float)_baseVector.mData[2];	//fbx�� z��ǥ�� ������ �ִ�.
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