#include "PreCompile.h"
#include "StageCreater.h"
#include "StageObject.h"
#include "Mouse.h"
#include "PlayerObject.h"
#include "GlobalContentsValue.h"
#include "RoadObject.h"

StageCreater::StageCreater()
{
}

StageCreater::~StageCreater()
{
}

void StageCreater::Start()
{
	std::shared_ptr<GameEngineInstancingRenderer> worldRenderer_ = GetLevel()->GetMainCamera()->GetInstancingRenderer("1-DirtPatch");
	{
		worldRenderer_->Initialize(
			100,
			"Rect",
			"DeferredInstanceRendering"
		);
		worldRenderer_->SetTexture2DArray("Inst_Textures", "Field");
		worldRenderer_->SetSampler("POINTCLAMP", "POINTCLAMP");
		//fieldRenderer_->SetAllUnitsWorldScale(256, 256, 1);
		//그려질 필요없는 렌더유닛들이 256, 256 크기로 그려지는 버그 발생.
	}

	{
		std::list<std::shared_ptr<StageObject>>& GroupActor = stageObjects_[7];
		std::shared_ptr<StageObject> object = GetLevel()->CreateActor<StageObject>();
		object->SetMyLevel(0);
		object->SetStageType(static_cast<int>(StageType::Boss));
		object->posY_ = -650;
		worldRenderer_->GetInstancingUnit(0).GetAtlasData().SetData(0.f, 0.f, 1.f, 1.f, 0.f, 0.0f);
		worldRenderer_->GetInstancingUnit(0).SetColorTextureIndex(4);
		worldRenderer_->GetInstancingUnit(0).SetNormalMapTextureIndex(5);
		worldRenderer_->GetInstancingUnit(0).SetWorldScale(256.f, 256.f, 1.f);
		worldRenderer_->GetInstancingUnit(0).SetWorldRotation(float4(60.f, 0.f, 0.f));
		worldRenderer_->GetInstancingUnit(0).SetWorldPosition(1024 - 128.f, -650 * sinf(30.f * GameEngineMath::DegreeToRadian), -651 * cosf(30.f * GameEngineMath::DegreeToRadian));
		object->GetTransform().SetWorldPosition(1024 - 128.f, -650 * sinf(30.f * GameEngineMath::DegreeToRadian), -650 * cosf(30.f * GameEngineMath::DegreeToRadian));
		GroupActor.push_back(object);
	}

	{
		std::list<std::shared_ptr<StageObject>>& GroupActor = stageObjects_[0];
		std::shared_ptr<StageObject> object = GetLevel()->CreateActor<StageObject>();
		object->SetMyLevel(7);
		object->SetStageType(static_cast<int>(StageType::Empty));
		object->posY_ = -2400;
		object->GetTransform().SetWorldPosition(1024 - 128.f, -2400 * sinf(30.f * GameEngineMath::DegreeToRadian), -2400 * cosf(30.f * GameEngineMath::DegreeToRadian));
		GroupActor.push_back(object);
		worldRenderer_->GetInstancingUnit(1).GetAtlasData().SetData(0.f, 0.f, 1.f, 1.f, 0.f, 0.0f);
		worldRenderer_->GetInstancingUnit(1).SetColorTextureIndex(4);
		worldRenderer_->GetInstancingUnit(1).SetNormalMapTextureIndex(5);
		worldRenderer_->GetInstancingUnit(1).SetWorldScale(256.f, 256.f, 1.f);
		worldRenderer_->GetInstancingUnit(1).SetWorldRotation(float4(60.f, 0.f, 0.f));
		worldRenderer_->GetInstancingUnit(1).SetWorldPosition(1024 - 128.f, -2400 * sinf(30.f * GameEngineMath::DegreeToRadian), -2401 * cosf(30.f * GameEngineMath::DegreeToRadian));
		curlevel_ = object;
		playerObject_ = GetLevel()->CreateActor<PlayerObject>(ObjectOrder::Player);
		playerObject_->GetTransform().SetWorldPosition(1024 - 128.f, -2400 * sinf(30.f * GameEngineMath::DegreeToRadian), -2400 * cosf(30.f * GameEngineMath::DegreeToRadian));
	}


	



	{
		int PrevMaxCount = 0;
		int unitIndex = 2;
		std::shared_ptr<GameEngineInstancingRenderer> worldRenderer_ = GetLevel()->GetMainCamera()->GetInstancingRenderer("1-DirtPatch");
		for (int level = 1; level < 7; level++)
		{
			int maxCount = GameEngineRandom::mainRandom_.RandomInt(2, 5);
			if (maxCount == PrevMaxCount)
			{
				maxCount = GameEngineRandom::mainRandom_.RandomInt(2, 5);
			}
			float x = 400;
			float xInterval = 0.f;
			for (int Count = 0; Count < maxCount; Count++)
			{
				std::list<std::shared_ptr<StageObject>>& GroupActor = stageObjects_[level];
				std::shared_ptr<StageObject> object = GetLevel()->CreateActor<StageObject>();
				object->SetMyLevel(level);
				object->SetStageType(GameEngineRandom::mainRandom_.RandomInt(0, 3));

				if (maxCount == 2)
				{
					if (Count == 0)
					{
						xInterval = 200.f;
					}
					else if (Count == 1)
					{
						xInterval = 800.f;
					}
				}
				else if (maxCount == 3)
				{
					if (Count == 0)
					{
						xInterval = 200.f;
					}
					else if (Count == 1)
					{
						xInterval = 500.f;
					}
					else if (Count == 2)
					{
						xInterval = 800.f;
					}
				}
				else if (maxCount == 4)
				{
					if (Count == 0)
					{
						xInterval = 0.f;
					}
					else if (Count == 1)
					{
						xInterval = 250.f;
					}
					else if (Count == 2)
					{
						xInterval = 750.f;
					}
					else if (Count == 3)
					{
						xInterval = 1000.f;
					}
				}
				else if (maxCount == 5)
				{
					xInterval = Count * 250.f;
				}
				x = 400 + xInterval + GameEngineRandom().mainRandom_.RandomFloat(-100.f, 50.f);
				object->GetTransform().SetWorldPosition(x, (-2400 + 250.f * level) * sinf(30.f * GameEngineMath::DegreeToRadian), (-2400 + 250.f * level) * cosf(30.f * GameEngineMath::DegreeToRadian));
				worldRenderer_->GetInstancingUnit(unitIndex).GetAtlasData().SetData(0.f, 0.f, 1.f, 1.f, 0.f, 0.0f);
				//NewGrassTexture.png 전체를 다 그린다.

				worldRenderer_->GetInstancingUnit(unitIndex).SetColorTextureIndex(4);
				//NewGrassTexture.png는 2번으로 삽입되어 있다.
				worldRenderer_->GetInstancingUnit(unitIndex).SetNormalMapTextureIndex(5);
				worldRenderer_->GetInstancingUnit(unitIndex).SetWorldScale(256.f, 256.f, 1.f);
				//타일을 그리는 인스턴싱유닛들만 크기 설정을 해준다.

				worldRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(x, (-2400 + 250.f * level)* sinf(30.f * GameEngineMath::DegreeToRadian), (-2401 + 250.f * level)* cosf(30.f * GameEngineMath::DegreeToRadian));	//타일 렌더하는 인스턴싱유닛들의 위치 설정.

				worldRenderer_->GetInstancingUnit(unitIndex).SetWorldRotation(float4(60.f, 0.f, 0.f));

				++unitIndex;
				//worldRenderer_->GetInstancingUnit(unitIndex).SetWorldPosition(x, (-2400 + 250.f * level)* sinf(30.f * GameEngineMath::DegreeToRadian), (-2401 + 250.f * level)* cosf(30.f * GameEngineMath::DegreeToRadian));	//타일 렌더하는 인스턴싱유닛들의 위치 설정.
				float c = -2400.f + (250.f * static_cast<float>(level));
				object->posY_ = c;
				GroupActor.push_back(object);
				++unitIndex;
			}
			PrevMaxCount = maxCount;
		}
	}
	
	 
	for (int level = 0; level < 7; level++)
	{
		std::list<std::shared_ptr<StageObject>>& GroupActor = stageObjects_[level];
		for (std::list<std::shared_ptr<StageObject>>::iterator iter = GroupActor.begin();
			iter != GroupActor.end(); iter++)
		{
			std::list<std::shared_ptr<StageObject>>& nextGroupActor = stageObjects_[level + 1];
			for (std::list<std::shared_ptr<StageObject>>::iterator nextiter = nextGroupActor.begin();
				nextiter != nextGroupActor.end(); nextiter++)
			{
				float PosX = (*iter)->GetTransform().GetWorldPosition().x;
				float PosY = (*iter)->posY_;
				float PosNX = (*nextiter)->GetTransform().GetWorldPosition().x;
				float PosNY = (*nextiter)->posY_;

				std::shared_ptr<RoadObject> road = GetLevel()->CreateActor<RoadObject>(ObjectOrder::Road);
				road->GetTransform().SetWorldPosition(float4((PosNX + PosX) / 2.f, ((PosNY + PosY) / 2.f) * sinf(30.f * GameEngineMath::DegreeToRadian), ((PosNY + PosY) / 2.f - 5.f) * cosf(30.f * GameEngineMath::DegreeToRadian)));
				road->GetTransform().SetWorldRotation(60.f, 0, -atan2f(PosNX - PosX, PosNY - PosY) * GameEngineMath::RadianToDegree);

				road->GetRenderer().get()->GetTransform().SetWorldScale(float4(128.f, float4(PosX - PosNX, PosY - PosNY, 0.f, 0.f).Length() - 60.f));
				road->GetCol().get()->GetTransform().SetWorldScale(float4(40.f, float4(PosX - PosNX, PosY - PosNY, 0.f, 0.f).Length() - 60.f));
				
				if (level != 0 && level != 6)
				{
					if (true == road->GetCol().get()->IsCollision(CollisionType::CT_AABB, ObjectOrder::Road, CollisionType::CT_AABB))
					{
						road->Death();
					}

					else if (420.f < float4(PosX - PosNX, PosY - PosNY, 0.f, 0.f).Length() - 60.f)
					{
						road->Death();
					}
				

					else
					{
						(*iter)->PushNextlevel(*nextiter);

					}
				}
				(*iter)->PushNextlevel(*nextiter);
			}
		}
	}
}

void StageCreater::Update(float _deltaTime)
{
	//Mouse::GetMouseInfo().get()->mouseCollision_->IsCollision(CollisionType::CT_OBB2D, ObjectOrder::MapObject, CollisionType::CT_OBB2D,
	//	std::bind(&StageCreater::CheckNextLevel, this, std::placeholders::_1, std::placeholders::_2));
}

CollisionReturn StageCreater::CheckNextLevel(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	if (true == GameEngineInput::GetInst()->IsDown("Click") && playerObject_->IsObjectIdle() == true)
	{
		std::shared_ptr<StageObject> Other = _Other->GetActor<StageObject>();
		if (true == curlevel_->CheckNextLevel(Other))
		{
			float4 Pos = playerObject_->GetTransform().GetWorldPosition();
			float4 NPos = _Other->GetActor()->GetTransform().GetWorldPosition();

			float4 dir = NPos - Pos;
			playerObject_->SetMoveDir(dir);
			curlevel_ = _Other->GetActor<StageObject>();

		}
	
	}
	return CollisionReturn::Stop;
}

void StageCreater::SendPlayerToNextStage(std::weak_ptr<StageObject> _nextStageObject)
{
	if (true == curlevel_->CheckNextLevel(_nextStageObject.lock()))
	{
		float4 Pos = playerObject_->GetTransform().GetWorldPosition();
		float4 NPos = _nextStageObject.lock()->GetTransform().GetWorldPosition();

		float4 dir = NPos - Pos;
		playerObject_->SetMoveDir(dir);
		curlevel_ = _nextStageObject.lock();
	}
}

void StageCreater::LevelStartEvent()
{
	curlevel_->Off();
}