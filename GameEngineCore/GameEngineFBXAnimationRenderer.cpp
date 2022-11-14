﻿#include "PreCompile.h"
#include "GameEngineFBXAnimationRenderer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineFBXAnimation.h"	
#include "GameEngineFBXMesh.h"

void FBXRendererAnimation::Init(int _Index)
{
	// GameENgineFBXAnimation의 행렬 정보가 완전해지는것은 
	// CalFbxExBoneFrameTransMatrix가 호출되고 난 후입니다.
	// 애니메이션의 행렬이 계산되는겁니다.
	Animation->AnimationMatrixLoad(Mesh, ParentRenderer->CastThis<GameEngineFBXAnimationRenderer>(), _Index);
	FBXAnimationData = Animation->GetAnimationData(_Index);
	Start = 0;
	End = static_cast<unsigned int>(FBXAnimationData->TimeEndCount);
	FrameTime = 0.02f;
}

void FBXRendererAnimation::Reset()
{
	Start = 0;
}

void FBXRendererAnimation::Update(float _deltaTime)
{
	// 0~24진행이죠?
	CurFrameTime += _deltaTime;
	//                      0.1
	// 1
	while (CurFrameTime >= FrameTime)
	{
		// 여분의 시간이 남게되죠?
		// 여분의 시간이 중요합니다.
		CurFrameTime -= FrameTime;
		++CurFrame;

		if (CurFrame >= End)
		{
			CurFrame = Start;
		}
	}

	unsigned int NextFrame = CurFrame;

	++NextFrame;

	if (NextFrame >= End)
	{
		NextFrame = 0;
	}

	// mesh      subset
	std::vector<std::vector<GameEngineRenderUnit>>& Units = ParentRenderer->GetAllRenderUnit();

	for (size_t UnitSetIndex = 0; UnitSetIndex < Units.size(); ++UnitSetIndex)
	{
		for (size_t RenderUnitIndex = 0; RenderUnitIndex < Units[UnitSetIndex].size(); ++RenderUnitIndex)
		{
			GameEngineRenderUnit& Render = Units[UnitSetIndex][RenderUnitIndex];

			// 위험!!!! 위험!!!! 뭔가 기분이 멜랑ㄹㅁㄴ어ㅏ림ㄴㅇ엉라ㅣㅁㄴ
			std::map<size_t, std::vector<float4x4>>::iterator MatrixIter = ParentRenderer->AnimationBoneMatrixs.find(UnitSetIndex);

			if (MatrixIter == ParentRenderer->AnimationBoneMatrixs.end())
			{
				continue;
			}

			// 68개 
			std::vector<float4x4>& AnimationBoneMatrix = MatrixIter->second;

			std::map<size_t, std::vector<AnimationBoneData>>::iterator AnimationDataIter = ParentRenderer->AnimationBoneDatas.find(UnitSetIndex);
			// 68개 
			std::vector<AnimationBoneData>& AnimationBoneData = AnimationDataIter->second;

			size_t MeshIndex = MatrixIter->first;

			for (int i = 0; i < AnimationBoneMatrix.size(); i++)
			{
				Bone* BoneData = ParentRenderer->GetFBXMesh()->FindBone(MeshIndex, i);

				if (true == FBXAnimationData->AniFrameData[MeshIndex][i].BoneMatData.empty())
				{
					// 본의 프레임데이터가 없을때가 있습니다.
					// 보통 항등행렬이 들어가 있는 경우가 많습니다.
					// 기본행렬로 세팅해주는것.
					// GameEngineDebug::MsgBoxError("아핀행렬 만들어라!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
					AnimationBoneMatrix[i] = float4x4::Affine(BoneData->BonePos.GlobalScale, BoneData->BonePos.GlobalRotation, BoneData->BonePos.GlobalTranslation);
					return;
				}

				// 현재프레임과 
				FbxExBoneFrameData& CurData = FBXAnimationData->AniFrameData[MeshIndex][i].BoneMatData[CurFrame];
				// 다음프레임의 정보가 필요한데
				FbxExBoneFrameData& NextData = FBXAnimationData->AniFrameData[MeshIndex][i].BoneMatData[NextFrame];


				// 블랜드를 하기 위해서는 필요하다.
				// 애니메이션이 바뀌는 순간 한번은 저장해야 한다.
				// 로컬 스케일
				AnimationBoneData[i].Scale = float4::Lerp(CurData.S, NextData.S, CurFrameTime);
				// 로컬 쿼터니온
				AnimationBoneData[i].RotQuaternion = float4::SLerpQuaternion(CurData.Q, NextData.Q, CurFrameTime);
				// 로컬 포지션
				AnimationBoneData[i].Pos = float4::Lerp(CurData.T, NextData.T, CurFrameTime);

				// 새롭게 바뀐 애니메이션

				// 애니메이션이 바뀌는 순간 한번은 저장해야 한다.
				//PrevAnimation[i].Scale;
				//PrevAnimation[i].RotQuaternion;
				//PrevAnimation[i].Pos;

				//AnimationBoneData[i].Scale;
				//AnimationBoneData[i].RotQuaternion;
				//AnimationBoneData[i].Pos;

				// float4::Lerp(PrevAnimation[i].Scale, AnimationBoneData[i].Scale, 0.0);

				size_t Size = sizeof(float4x4);
				// 자신의 원본행렬과 곱해준다 큰 의미는 없다.

				float4x4 Mat = float4x4::Affine(AnimationBoneData[i].Scale, AnimationBoneData[i].RotQuaternion, AnimationBoneData[i].Pos);

				//AnimationBoneData[i].Index = i;
				//AnimationBoneData[i].Scale *= ParentRenderer->GetTransform()->GetTransformData().WorldWorld_;
				//AnimationBoneData[i].RotQ = ParentRenderer->BoneData[i].RotQ.QuaternionMultiplyfloat4x4(ParentRenderer->GetTransform()->GetTransformData().WorldWorld_);
				//AnimationBoneData[i].Pos *= ParentRenderer->GetTransform()->GetTransformData().WorldWorld_;
				//AnimationBoneData[i].RotEuler = float4::QuaternionToEulerAngles(ParentRenderer->BoneData[i].RotQ) + ParentRenderer->GetTransform()->GetWorldRotation();
				//AnimationBoneData[i].RotEuler *= GameEngineMath::RadianToDegree;

				AnimationBoneMatrix[i] = BoneData->BonePos.Offset * Mat;
			}
		}

	}
}

GameEngineFBXAnimationRenderer::GameEngineFBXAnimationRenderer()
{
}

GameEngineFBXAnimationRenderer::~GameEngineFBXAnimationRenderer()
{
	Animations.clear();
}

void GameEngineFBXAnimationRenderer::SetFBXMesh(const std::string& _fbxMeshName, const std::string& _materialName)
{
	std::shared_ptr<GameEngineMaterial> Material = GameEngineMaterial::Find(_materialName);

	if (nullptr == Material)
	{
		MsgBoxAssert("존재하지 않는 머티리얼 입니다.");
		return;
	}

	if (false == Material->GetVertexShader()->IsStructuredBuffer("ArrAnimationMatrix"))
	{
		MsgBoxAssert("FBX 애니메이션 랜더러에 애니메이션이 불가능한 머티리얼을 세팅했습니다.");
		return;
	}

	GameEngineFBXRenderer::SetFBXMesh(_fbxMeshName, _materialName);
}

GameEngineRenderUnit* GameEngineFBXAnimationRenderer::SetFBXMesh(
	const std::string& _Name,
	const std::string& _Material,
	size_t _MeshIndex,
	size_t _SubSetIndex /*= 0*/
)
{
	std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Find(_Material);

	if (nullptr == Mat)
	{
		MsgBoxAssert("존재하지 않는 머티리얼 입니다.");
		return nullptr;
	}

	if (false == Mat->GetVertexShader()->IsStructuredBuffer("ArrAnimationMatrix"))
	{
		MsgBoxAssert("FBX 애니메이션 랜더러에 애니메이션이 불가능한 머티리얼을 세팅했습니다.");
		return nullptr;
	}

	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("존재하지 않는 FBXMesh를 세팅했습니다.");
		return nullptr;
	}

	if (AnimationBoneMatrixs.end() == AnimationBoneMatrixs.find(_MeshIndex))
	{
		size_t BoneCount = FindFBXMesh->GetBoneCount(_MeshIndex);
		AnimationBoneMatrixs.insert(std::make_pair(_MeshIndex, std::vector<float4x4>()));
		AnimationBoneMatrixs[_MeshIndex].resize(BoneCount);

		AnimationBoneDatas.insert(std::make_pair(_MeshIndex, std::vector<AnimationBoneData>()));
		AnimationBoneDatas[_MeshIndex].resize(BoneCount);
	}

	FindFBXMesh->GetMeshInfosCount();

	// 텍스처 세팅은 부모님이 맡아서 처리해주고
	GameEngineRenderUnit* Unit = GameEngineFBXRenderer::SetFBXMesh(_Name, _Material, _MeshIndex, _SubSetIndex);

	if (nullptr == Unit)
	{
		MsgBoxAssert("FBX애니메이션 랜더유니트를 만들어내지 못했습니다.");
		return nullptr;
	}

	// 이때 스트럭처드 버퍼를 세팅할거냐.
	if (Unit->GetShaderResourceHelper().IsStructuredBuffer("ArrAnimationMatrix"))
	{
		GameEngineStructuredBufferSetter* AnimationBuffer = Unit->GetShaderResourceHelper().GetStructuredBufferSetter("ArrAnimationMatrix");

		// ?? _MeshIndex
		AnimationBuffer->structuredBuffer_ = GetFBXMesh()->GetAnimationStructuredBuffer(_MeshIndex);

		if (nullptr == AnimationBuffer->structuredBuffer_)
		{
			MsgBoxAssert("애니메이션용 스트럭처드 버퍼가 존재하지 않습니다.");
			return Unit;
		}

		if (0 == AnimationBoneMatrixs[_MeshIndex].size())
		{
			return Unit;
		}

		// 링크를 걸어준것.
		AnimationBuffer->settingDataToGPU_ = &AnimationBoneMatrixs[_MeshIndex][0];
		AnimationBuffer->size_ = AnimationBoneMatrixs[_MeshIndex].size() * sizeof(float4x4);
		AnimationBuffer->Bind();

	}

	return Unit;
}

void GameEngineFBXAnimationRenderer::CreateFBXAnimation(
	const std::string& _AnimationName,
	const std::string& _AnimationFBX,
	int _Index/* = 0*/
)
{
	// 본을 가진 fbx가 세팅되어 있는지 검사한다.
	if (nullptr == GetFBXMesh())
	{
		MsgBoxAssert("골격 FBX가 세팅되어 있지 않습니다.");
		return;
	}

	// 여기있는 함수를 외부에서 호출하면 됩니다.

	if (Animations.end() != Animations.find(_AnimationName))
	{
		MsgBoxAssertString("이미 존재하는 이름의 애니메이션입니다." + _AnimationName);
		return;
	}

	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Find(_AnimationFBX);

	if (nullptr == Animation)
	{
		MsgBoxAssertString("GameEngineFBXAnimation이 존재하지 않습니다. " + _AnimationFBX);
		return;
	}

	std::shared_ptr<FBXRendererAnimation> NewAnimation = std::make_shared<FBXRendererAnimation>();

	NewAnimation->Mesh = GetFBXMesh();
	NewAnimation->Animation = Animation;
	NewAnimation->ParentRenderer = this;

	NewAnimation->Init(_Index);

	// 이순간 애니메이션 프레임 행렬에 대한 계산이 이때 이뤄지는데.
	// 이건 느릴것이기 때문에 아마 추후 분명히.
	// 다른 툴이나 함수로 한번 로드하고 우리 포맷으로 저장하는 일을 해야할겁니다.
	renderOptionInst_.isAnimation_ = 1;

	Animations.insert(std::make_pair(_AnimationName, NewAnimation));

	NewAnimation;
}

void GameEngineFBXAnimationRenderer::ChangeAnimation(const std::string& _AnimationName)
{
	std::map<std::string, std::shared_ptr<FBXRendererAnimation>>::iterator FindIter = Animations.find(_AnimationName);

	if (Animations.end() == FindIter)
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 하려고 했습니다.");
		return;
	}

	CurAnimation = FindIter->second;
}

void GameEngineFBXAnimationRenderer::Update(float _deltaTime)
{
	if (nullptr == CurAnimation)
	{
		return;
	}

	CurAnimation->Update(_deltaTime);
}
