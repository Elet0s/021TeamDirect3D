#include "PreCompile.h"
#include "GameEngineFBXAnimation.h"
//#include "GameEngineDevice.h"
#include "GameEngineFBXMesh.h"

GameEngineFBXAnimation::GameEngineFBXAnimation()
{
}

GameEngineFBXAnimation::~GameEngineFBXAnimation()
{
}

GameEngineFBXAnimation* GameEngineFBXAnimation::Load(const std::string& _Path, const std::string& _Name)
{
	GameEngineFBXAnimation* NewRes = CreateNamedRes(_Name);
	NewRes->SetPath(_Path);
	NewRes->LoadMesh(_Path, _Name);
	return NewRes;
}

void GameEngineFBXAnimation::LoadMesh(const std::string& _Path, const std::string& _Name)
{
	FBXInit(_Path);

	CheckAnimation();

	AnimationDatas;
}

bool GameEngineFBXAnimation::CheckAnimation()
{
	std::string Path = GetPath();

	fbxsdk::FbxArray<FbxString*> AniNameArray;
	scene_->FillAnimStackNameArray(AniNameArray);

	if (0 == AniNameArray.Size())
	{
		return false;
	}

	AnimationDatas.resize(AniNameArray.Size());

	for (unsigned int i = 0; i < AnimationDatas.size(); i++)
	{
		AnimationDatas[i].AniName = GameEngineString::UTF8ToAnsiReturn(AniNameArray[i]->Buffer());

		FbxTakeInfo* TakeInfo = scene_->GetTakeInfo(AnimationDatas[i].AniName.c_str());
		AnimationDatas[i].StartTime = TakeInfo->mLocalTimeSpan.GetStart();
		AnimationDatas[i].EndTime = TakeInfo->mLocalTimeSpan.GetStop();
		AnimationDatas[i].TimeMode = scene_->GetGlobalSettings().GetTimeMode();
		AnimationDatas[i].TimeStartCount = AnimationDatas[i].StartTime.GetFrameCount(AnimationDatas[i].TimeMode);

		if (0 >= AnimationDatas[i].TimeStartCount)
		{
			AnimationDatas[i].TimeStartCount *= (FbxLongLong)-1;
		}

		AnimationDatas[i].TimeEndCount = AnimationDatas[i].EndTime.GetFrameCount(AnimationDatas[i].TimeMode);
		AnimationDatas[i].FrameCount = AnimationDatas[i].TimeEndCount - AnimationDatas[i].TimeStartCount;

		AnimationDatas[i].FbxModeCount = (long long)fbxsdk::FbxTime::GetFrameRate(AnimationDatas[i].TimeMode);
		AnimationDatas[i].FbxModeRate = (double)fbxsdk::FbxTime::GetFrameRate(AnimationDatas[i].TimeMode);
	}

	for (int i = 0; i < AniNameArray.Size(); i++)
	{
		delete AniNameArray[i];
	}

	return true;
}

// ���� �� �Ž��� ���� ���� ����� �������°�.
fbxsdk::FbxAMatrix GameEngineFBXAnimation::GetGeometryTransformation(fbxsdk::FbxNode* pNode)
{
	fbxsdk::FbxVector4 translation = pNode->GetGeometricTranslation(fbxsdk::FbxNode::eSourcePivot);
	fbxsdk::FbxVector4 rotation = pNode->GetGeometricRotation(fbxsdk::FbxNode::eSourcePivot);
	fbxsdk::FbxVector4 scale = pNode->GetGeometricScaling(fbxsdk::FbxNode::eSourcePivot);

	return fbxsdk::FbxAMatrix(translation, rotation, scale);
}


bool GameEngineFBXAnimation::AnimationLoad(GameEngineFBXMesh* _Mesh, fbxsdk::FbxNode* _Node, int AnimationIndex)
{
	FbxAnimStack* stack = scene_->GetSrcObject<FbxAnimStack>(AnimationIndex);
	// �� ���� �ִϸ��̼��� �� ������ �ִϸ��̼����� �������ش�.
	scene_->SetCurrentAnimationStack(stack);

	fbxsdk::FbxMesh* pCurrMesh = _Node->GetMesh();
	int deformerCount = pCurrMesh->GetDeformerCount();
	fbxsdk::FbxAMatrix geometryTransform = GetGeometryTransformation(_Node);



	fbxsdk::FbxTakeInfo* takeInfo = scene_->GetTakeInfo(AnimationDatas[AnimationIndex].AniName.c_str());
	fbxsdk::FbxTime start = takeInfo->mLocalTimeSpan.GetStart();
	fbxsdk::FbxTime end = takeInfo->mLocalTimeSpan.GetStop();
	fbxsdk::FbxTime::EMode timeMode = scene_->GetGlobalSettings().GetTimeMode();

	fbxsdk::FbxAMatrix currentTransformOffset;
	fbxsdk::FbxAMatrix localTransform;
	fbxsdk::FbxAMatrix globalTransform;

	fbxsdk::FbxCluster* pCurrCluster;
	std::string currJointName;
	Bone* pBone;

	fbxsdk::FbxAMatrix transformMatrix;
	fbxsdk::FbxAMatrix transformLinkMatrix;
	fbxsdk::FbxAMatrix globalBindposeInverseMatrix;

	fbxsdk::FbxLongLong fixIndex;

	std::string linkName;

	fbxsdk::FbxLongLong endTime;
	fbxsdk::FbxLongLong startTime;

	fbxsdk::FbxTime currTime;


	for (int deformerIndex = 0; deformerIndex < deformerCount; ++deformerIndex)
	{
		fbxsdk::FbxSkin* pCurrSkin = reinterpret_cast<fbxsdk::FbxSkin*>(pCurrMesh->GetDeformer(deformerIndex, fbxsdk::FbxDeformer::eSkin));
		if (nullptr == pCurrSkin)
		{
			continue;
		}

		unsigned int numOfClusters = pCurrSkin->GetClusterCount();

		endTime = end.GetFrameCount(timeMode);
		startTime = start.GetFrameCount(timeMode);

		FbxExAniData& CurAniData = AnimationDatas[AnimationIndex];
		CurAniData.EndTime = endTime;
		CurAniData.StartTime = startTime;
		CurAniData.TimeMode = timeMode;

		for (size_t MeshIndex = 0; MeshIndex < CurAniData.AniFrameData.size(); ++MeshIndex)
		{
			if (0 == CurAniData.AniFrameData[MeshIndex].size())
			{
				continue;
			}

			for (unsigned int clusterIndex = 0; clusterIndex < numOfClusters; ++clusterIndex)
			{
				pCurrCluster = pCurrSkin->GetCluster(clusterIndex);
				currJointName = pCurrCluster->GetLink()->GetName();
				pBone = _Mesh->FindBone(0, currJointName);

				pCurrCluster->GetTransformMatrix(transformMatrix);
				pCurrCluster->GetTransformLinkMatrix(transformLinkMatrix);
				globalBindposeInverseMatrix = transformLinkMatrix.Inverse();

				linkName = pCurrCluster->GetLink()->GetName();
				fbxsdk::FbxNode* pLinkNode = scene_->FindNodeByName(linkName.c_str());

				FbxExBoneFrame& Frame = CurAniData.AniFrameData[MeshIndex][pBone->Index];
				Frame.BoneMatData.resize(endTime - startTime + 1);
				Frame.BoneIndex = pBone->Index;
				Frame.BoneParentIndex = pBone->ParentIndex;

				for (fbxsdk::FbxLongLong i = startTime; i <= endTime; ++i)
				{
					fixIndex = i - startTime;

					FbxExBoneFrameData& FrameData = Frame.BoneMatData[fixIndex];

					currTime.SetFrame(fixIndex, timeMode);
					// ��
					currentTransformOffset = _Node->EvaluateGlobalTransform(currTime) * jointMatrix_ * geometryTransform;
					// �ð��� �־��ָ� �׶��� ���� ����� ������ �ش�.
					// Ŀ�� 
					globalTransform = currentTransformOffset.Inverse() * pLinkNode->EvaluateGlobalTransform(currTime);

					localTransform.SetS(pLinkNode->EvaluateLocalScaling(currTime));
					localTransform.SetR(pLinkNode->EvaluateLocalRotation(currTime));
					localTransform.SetT(pLinkNode->EvaluateLocalTranslation(currTime));

					FrameData.Time = currTime.GetSecondDouble();
					FrameData.LocalAnimation = localTransform;
					FrameData.GlobalAnimation = globalTransform;
					FrameData.FrameMat = FBXMatrixToFloat4x4(FrameData.GlobalAnimation);
					FrameData.S = FBXVecToFloat4(FrameData.GlobalAnimation.GetS());
					FrameData.Q = FBXQuaternionToFloat4(FrameData.GlobalAnimation.GetQ());
					FrameData.T = FBXVecToTransform(FrameData.GlobalAnimation.GetT());
				}
			}
		}

	}

	return true;
}


void GameEngineFBXAnimation::ProcessAnimationCheckState(GameEngineFBXMesh* _Fbx, int userAniDataIndex)
{
	// �ڴ�
	FbxExAniData& userAniData = AnimationDatas.at(userAniDataIndex);
	fbxsdk::FbxLongLong fbxTime = userAniData.EndTime.Get() - userAniData.StartTime.Get() + 1;

	// �ִϸ��̼� ������ ����ִ� �༮���� ���� offset�̶�� �ϴ� T
	// 
	// ����
	for (size_t MeshIndex = 0; MeshIndex < userAniData.AniFrameData.size(); MeshIndex++)
	{
		// 30�������� ������
		size_t aniFrameDataSize = userAniData.AniFrameData[MeshIndex].size();
		for (size_t aniFrameDataIndex = 0; aniFrameDataIndex < aniFrameDataSize; ++aniFrameDataIndex)
		{
			FbxExBoneFrame& aniFrameData = userAniData.AniFrameData[MeshIndex].at(aniFrameDataIndex);
			// ���������.
			if (0 == aniFrameData.BoneMatData.size())
			{
				aniFrameData.BoneMatData.resize(fbxTime);
				Bone& curBone = _Fbx->AllBones[0][aniFrameDataIndex];
				aniFrameData.BoneIndex = curBone.Index;
				aniFrameData.BoneParentIndex = curBone.ParentIndex;
				if (-1 != curBone.ParentIndex)
				{
					FbxExBoneFrame& parentAniFrameData = userAniData.AniFrameData[MeshIndex].at(curBone.ParentIndex);
					for (fbxsdk::FbxLongLong start = 0; start < fbxTime; ++start)
					{
						aniFrameData.BoneMatData[start].Time = parentAniFrameData.BoneMatData[start].Time;
						aniFrameData.BoneMatData[start].LocalAnimation = Float4x4ToFBXAMatrix(curBone.BonePos.Local);
						aniFrameData.BoneMatData[start].GlobalAnimation = parentAniFrameData.BoneMatData[start].GlobalAnimation * aniFrameData.BoneMatData[start].LocalAnimation;
						aniFrameData.BoneMatData[start].FrameMat = FBXMatrixToFloat4x4(aniFrameData.BoneMatData[start].GlobalAnimation);
						aniFrameData.BoneMatData[start].S = FBXVecToFloat4(aniFrameData.BoneMatData[start].GlobalAnimation.GetS());
						aniFrameData.BoneMatData[start].Q = FBXQuaternionToFloat4(aniFrameData.BoneMatData[start].GlobalAnimation.GetQ());
						aniFrameData.BoneMatData[start].T = FBXVecToTransform(aniFrameData.BoneMatData[start].GlobalAnimation.GetT());
					}
				}
				else
				{
					for (fbxsdk::FbxLongLong start = 0; start < fbxTime; ++start)
					{
						aniFrameData.BoneMatData[start].Time = 0;
						aniFrameData.BoneMatData[start].LocalAnimation = Float4x4ToFBXAMatrix(curBone.BonePos.Local);
						aniFrameData.BoneMatData[start].GlobalAnimation = aniFrameData.BoneMatData[start].LocalAnimation;
						aniFrameData.BoneMatData[start].FrameMat = FBXMatrixToFloat4x4(aniFrameData.BoneMatData[start].GlobalAnimation);
						aniFrameData.BoneMatData[start].S = FBXVecToFloat4(aniFrameData.BoneMatData[start].GlobalAnimation.GetS());
						aniFrameData.BoneMatData[start].Q = FBXQuaternionToFloat4(aniFrameData.BoneMatData[start].GlobalAnimation.GetQ());
						aniFrameData.BoneMatData[start].T = FBXVecToTransform(aniFrameData.BoneMatData[start].GlobalAnimation.GetT());
					}
				}
			}
		}
	}
}


// �ִϸ��̼��� ����� ��Ʈ����Ʈ�� �� eMesh�� �༮���� ��������Ƿ� �׳༮���Լ� �ִϸ��̼� �ε� �Լ��� �����Ű�� ������ �Ѵ�.
void GameEngineFBXAnimation::ProcessAnimationLoad(GameEngineFBXMesh* _Mesh, fbxsdk::FbxNode* pNode, int _index)
{
	// ��� ��带 �� �ȱ� ���ؼ�

	fbxsdk::FbxNodeAttribute* pNodeAttribute = pNode->GetNodeAttribute();
	if (nullptr != pNodeAttribute)
	{
		fbxsdk::FbxNodeAttribute::EType typetype = pNodeAttribute->GetAttributeType();
		switch (pNodeAttribute->GetAttributeType())
		{
		case fbxsdk::FbxNodeAttribute::eLODGroup:
		{
			if (0 != pNode->GetChildCount())
			{
				ProcessAnimationLoad(_Mesh, pNode->GetChild(0), _index);
				return;
			}
		}
		break;
		case fbxsdk::FbxNodeAttribute::eMesh:
		{
			AnimationLoad(_Mesh, pNode, _index);
		}
		break;
		default:
			break;
		}
	}

	for (int n = 0; n < pNode->GetChildCount(); ++n)
	{
		ProcessAnimationLoad(_Mesh, pNode->GetChild(n), _index);
	}
}


// ���� ���� GameEngineFBXMesh������� �ִϸ��̼� ����� ������.
void GameEngineFBXAnimation::AnimationMatrixLoad(GameEngineFBXMesh* _Mesh, int _AnimationIndex)
{
	if (0 == AnimationDatas.size())
	{
		MsgBoxAssert("�ִϸ��̼� �����Ͱ� �������� �ʴ� �Ž��� �ִϸ��̼��� ������� �߽��ϴ�.");
		return;
	}

	if (0 != AnimationDatas[_AnimationIndex].AniFrameData.size())
	{
		return;
	}

	// �� fbx�� �ѹ� CheckAnimation�ϸ鼭 �ִϸ��̼��� ��ִ��� üũ�������̰�
	// std::vector<std::vector<FbxExBoneFrame>> AniFrameData;
	// _Mesh->MeshInfos�� 
	AnimationDatas[_AnimationIndex].AniFrameData.resize(_Mesh->MeshInfos.size());
	// FBX���� ���� ���� Case1�� ��Ȳ������ �׷���.
	// MeshInfos
	// std::vector<std::vector<Bone>> AllBones; // ������ü
	// GameEngineFBXAnimation 
	for (UINT MeshCount = 0; MeshCount < _Mesh->MeshInfos.size(); MeshCount++)
	{
		// std::vector<std::vector<FbxExBoneFrame>> AniFrameData;
		//    �Ž�        ������ 
		AnimationDatas[_AnimationIndex].AniFrameData[MeshCount].resize(_Mesh->GetBoneCount(MeshCount));
	}

	ProcessAnimationLoad(_Mesh, _Mesh->rootNode_, _AnimationIndex);

	ProcessAnimationCheckState(_Mesh, _AnimationIndex);

	AnimationDatas;
}
