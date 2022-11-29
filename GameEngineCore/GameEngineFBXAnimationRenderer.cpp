#include "PreCompile.h"
#include "GameEngineFBXAnimationRenderer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineFBXAnimation.h"	
#include "GameEngineFBXMesh.h"

GameEngineFBXAnimationRenderer::GameEngineFBXAnimationRenderer() :Pause(false)
{
}

GameEngineFBXAnimationRenderer::~GameEngineFBXAnimationRenderer()
{
	Animations.clear();
}


// _Index
// 애니메이션을 가진 fbx의 AnimationDatas(vector)의 index를 의미한다.

void FBXRendererAnimation::Init(const std::string_view& _Name, int _Index)
{
	// GameENgineFBXAnimation의 행렬 정보가 완전해지는것은 
	// CalFbxExBoneFrameTransMatrix가 호출되고 난 후입니다.
	// 애니메이션의 행렬이 계산되는겁니다.
	Animation->AnimationMatrixLoad(Mesh, _Name, _Index);
	FBXAnimationData = Animation->GetAnimationData(_Index);
	Start = 0;
	End = static_cast<unsigned int>(FBXAnimationData->TimeEndCount);
}

void FBXRendererAnimation::Update(float _DeltaTime)
{
	// 0~24진행이죠?
	if (false == ParentRenderer->Pause)
	{
		Info.curFrameTime_ += _DeltaTime;
		Info.playTime_ += _DeltaTime;

		while (Info.curFrameTime_ >= Info.interval_)
		{
			// 여분의 시간이 남게되죠?
			// 여분의 시간이 중요합니다.
			Info.curFrameTime_ -= Info.interval_;

			//if (Info.curFrame_ >= End)
			//{
			//	Info.curFrame_ = Start;
			//}

			if (false == bOnceStart
				&& Info.curFrame_ == 0)
			{
				if (nullptr != StartEvent)
				{
					StartEvent(Info);
				}
				bOnceStart = true;
				bOnceEnd = false;
			}

			if (Info.curFrame_ == static_cast<UINT>(Info.frames_.size() - 1)
				&& false == bOnceEnd)
			{
				if (nullptr != EndEvent)
				{
					EndEvent(Info);
				}
				bOnceEnd = true;
				bOnceStart = false;
				break;
			}

			++Info.curFrame_;
			if (nullptr != FrameEvent)
			{
				FrameEvent(Info);
			}

			if (nullptr != TimeEvent)
			{
				TimeEvent(Info, _DeltaTime);
			}

			if (Info.curFrame_ >= Info.frames_.size() - 1)
			{
				if (true == Info.isLoop_)
				{
					Info.curFrame_ = Start;
				}
				else
				{
					Info.curFrame_ = static_cast<unsigned int>(Info.frames_.size()) - 1;
				}
			}
		}
	}

	unsigned int NextFrame = Info.curFrame_;

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
				FbxExBoneFrameData& CurData = FBXAnimationData->AniFrameData[MeshIndex][i].BoneMatData[Info.curFrame_];
				// 다음프레임의 정보가 필요한데
				FbxExBoneFrameData& NextData = FBXAnimationData->AniFrameData[MeshIndex][i].BoneMatData[NextFrame];

				// 애니메이션이 바뀌는 순간 한번은 저장해야 한다.
				// 로컬 스케일
				AnimationBoneData[i].Scale = float4::Lerp(CurData.S, NextData.S, Info.curFrameTime_);
				// 로컬 쿼터니온
				AnimationBoneData[i].RotQuaternion = float4::SLerpQuaternion(CurData.Q, NextData.Q, Info.curFrameTime_);
				// 로컬 포지션
				AnimationBoneData[i].Pos = float4::Lerp(CurData.T, NextData.T, Info.curFrameTime_);
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
				//AnimationBoneMatrix[i].Transpose();
			}
		}
	}
}

void FBXRendererAnimation::Reset()
{
	Info.curFrameTime_ = 0.0f;
	Info.curFrame_ = 0;
	Info.playTime_ = 0.0f;
	// Start = 0;
}

void GameEngineFBXAnimationRenderer::SetFBXMesh(const std::string& _fbxMeshName, const std::string& _materialName)
{
	std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Find(_materialName);

	if (nullptr == Mat)
	{
		MsgBoxAssert("존재하지 않는 머티리얼 입니다.");
		return;
	}

	if (false == Mat->GetVertexShader()->IsStructuredBuffer("ArrAnimationMatrix"))
	{
		MsgBoxAssert("FBX 애니메이션 랜더러에 애니메이션이 불가능한 머티리얼을 세팅했습니다.");
		return;
	}


	GameEngineFBXRenderer::SetFBXMesh(_fbxMeshName, _materialName);
}

GameEngineRenderUnit* GameEngineFBXAnimationRenderer::SetFBXMesh(
	const std::string& _fbxMeshName,
	const std::string& _materialName,
	size_t _meshIndex,
	size_t _subsetIndex /*= 0*/
)
{
	std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Find(_materialName);

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

	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_fbxMeshName);

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("존재하지 않는 FBXMesh를 세팅했습니다.");
		return nullptr;
	}

	if (AnimationBoneMatrixs.end() == AnimationBoneMatrixs.find(_meshIndex))
	{
		size_t BoneCount = FindFBXMesh->GetBoneCount(_meshIndex);
		AnimationBoneMatrixs.insert(std::make_pair(_meshIndex, std::vector<float4x4>()));
		AnimationBoneMatrixs[_meshIndex].resize(BoneCount);

		AnimationBoneDatas.insert(std::make_pair(_meshIndex, std::vector<AnimationBoneData>()));
		AnimationBoneDatas[_meshIndex].resize(BoneCount);
	}

	FindFBXMesh->GetMeshInfosCount();

	// 텍스처 세팅은 부모님이 맡아서 처리해주고
	GameEngineRenderUnit* Unit = GameEngineFBXRenderer::SetFBXMesh(_fbxMeshName, _materialName, _meshIndex, _subsetIndex);

	if (nullptr == Unit)
	{
		MsgBoxAssert("FBX애니메이션 랜더유니트를 만들어내지 못했습니다.");
		return nullptr;
	}

	// 이때 스트럭처드 버퍼를 세팅할거냐.
	if (Unit->GetShaderResourceHelper().IsStructuredBuffer("ArrAniMationMatrix"))
	{
		GameEngineStructuredBufferSetter* AnimationBuffer = Unit->GetShaderResourceHelper().GetStructuredBufferSetter("ArrAnimationMatrix");

		// ?? _MeshIndex
		AnimationBuffer->structuredBuffer_ = GetFBXMesh()->GetAnimationStructuredBuffer(_meshIndex);

		if (nullptr == AnimationBuffer->structuredBuffer_)
		{
			MsgBoxAssert("애니메이션용 스트럭처드 버퍼가 존재하지 않습니다.");
			return Unit;
		}

		if (0 == AnimationBoneMatrixs[_meshIndex].size())
		{
			return Unit;
		}

		// 링크를 걸어준것.
		AnimationBuffer->settingDataToGPU_ = &AnimationBoneMatrixs[_meshIndex][0];
		AnimationBuffer->size_ = sizeof(float4x4);
		AnimationBuffer->count_ = AnimationBoneMatrixs[_meshIndex].size();
		AnimationBuffer->Bind();

	}

	return Unit;
}

void GameEngineFBXAnimationRenderer::PauseSwitch()
{
	Pause = !Pause;
}

void GameEngineFBXAnimationRenderer::CreateFBXAnimation(const std::string& _AnimationName, const GameEngineRenderingEvent& _Desc, int _Index /* = 0*/)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	// 본을 가진 fbx가 세팅되어 있는지 검사한다.
	if (nullptr == GetFBXMesh())
	{
		MsgBoxAssert("골격 FBX가 세팅되어 있지 않습니다.");
		return;
	}

	// 여기있는 함수를 외부에서 호출하면 됩니다.

	if (Animations.end() != Animations.find(UpperName))
	{
		MsgBoxAssertString("이미 존재하는 이름의 애니메이션입니다." + UpperName);
		return;
	}

	std::shared_ptr<GameEngineFBXAnimation> Animation = GameEngineFBXAnimation::Find(_Desc.resourceName_);

	if (nullptr == Animation)
	{
		MsgBoxAssertString("GameEngineFBXAnimation이 존재하지 않습니다. " + _Desc.resourceName_);
		return;
	}

	std::shared_ptr<FBXRendererAnimation> NewAnimation = std::make_shared<FBXRendererAnimation>();

	NewAnimation->Info = _Desc;
	NewAnimation->Info.parentRenderer_ = this;
	NewAnimation->Mesh = GetFBXMesh();
	NewAnimation->Animation = Animation;
	NewAnimation->ParentRenderer = this;
	NewAnimation->Reset();

	NewAnimation->Init(_AnimationName, _Index);

	for (UINT i = 0; i < NewAnimation->End - NewAnimation->Start; i++)
	{
		NewAnimation->Info.frames_.push_back(i);
	}

	// 이순간 애니메이션 프레임 행렬에 대한 계산이 이때 이뤄지는데.
	// 이건 느릴것이기 때문에 아마 추후 분명히.
	// 다른 툴이나 함수로 한번 로드하고 우리 포맷으로 저장하는 일을 해야할겁니다.

	renderOptionInst_.isAnimation_ = 1;

	Animations.insert(std::make_pair(UpperName, NewAnimation));

	Animation;
}

void GameEngineFBXAnimationRenderer::ChangeAnimation(const std::string& _AnimationName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<FBXRendererAnimation>>::iterator FindIter = Animations.find(UpperName);

	if (Animations.end() == FindIter)
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 하려고 했습니다.");
		return;
	}

	CurAnimation = FindIter->second;
}

void GameEngineFBXAnimationRenderer::Update(float _DeltaTime)
{
	if (nullptr == CurAnimation)
	{
		return;
	}

	CurAnimation->Update(_DeltaTime);
}