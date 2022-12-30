#include "PreCompile.h"
#include "StageCreater.h"
#include "StageObject.h"

StageCreater::StageCreater() 
{
}

StageCreater::~StageCreater() 
{
}

void StageCreater::Start()
{
	{
		std::list<std::shared_ptr<StageObject>>& GroupActor = stageObjects_[7];
		std::shared_ptr<StageObject> object = GetLevel()->CreateActor<StageObject>();
		object->SetMyLevel(0);
		object->posY_ = -650;
		object->GetTransform().SetWorldPosition(1024 - 128.f, -650 * sinf(30.f * GameEngineMath::DegreeToRadian), -650 * cosf(30.f * GameEngineMath::DegreeToRadian));
		GroupActor.push_back(object);
	}

	{
		std::list<std::shared_ptr<StageObject>>& GroupActor = stageObjects_[0];
		std::shared_ptr<StageObject> object = GetLevel()->CreateActor<StageObject>();
		object->SetMyLevel(7);
		object->posY_ = -2400;
		object->GetTransform().SetWorldPosition(1024 - 128.f, -2400 * sinf(30.f * GameEngineMath::DegreeToRadian), -2400 * cosf(30.f * GameEngineMath::DegreeToRadian));
		GroupActor.push_back(object);
	}

	{
		for (int level = 1; level < 7; level++)
		{
			int maxCount = GameEngineRandom::mainRandom_.RandomInt(2, 4);
			for (int Count = 0; Count < maxCount; Count++)
			{
				float x = 400;
				std::list<std::shared_ptr<StageObject>>& GroupActor = stageObjects_[level];
				std::shared_ptr<StageObject> object = GetLevel()->CreateActor<StageObject>();
				object->SetMyLevel(level);
				object->SetStageType(GameEngineRandom::mainRandom_.RandomInt(0, 4));
				object->GetTransform().SetWorldPosition( x + (Count * 1200 / maxCount), (- 2400 + 250.f * level)* sinf(30.f * GameEngineMath::DegreeToRadian), (-2400 + 250.f * level) * cosf(30.f * GameEngineMath::DegreeToRadian));
				float c = -2400.f + (250.f * static_cast<float>(level));
				object->posY_ = c;
				GroupActor.push_back(object);
			}
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
				if (level != 6 && level != 0)
				{
					if (1 >= (*iter)->GetnextLevelList().size() &&(true == (*iter)->IsNextLevelEmpty() || true == CheckPushLevel()))
					{
						std::shared_ptr<GameEngineTextureRenderer> road = CreateComponent<GameEngineTextureRenderer>();
						float PosX = (*iter)->GetTransform().GetWorldPosition().x;
						float PosY = (*iter)->posY_;
						float PosNX = (*nextiter)->GetTransform().GetWorldPosition().x;
						float PosNY = (*nextiter)-> posY_;
						road->SetTexture("Path_alt_travel.png");
						//road->ScaleToTexture();
						road->GetTransform().SetWorldScale(float4(128.f, float4(PosX - PosNX, PosY - PosNY,0.f,0.f).Length() - 60.f));
				
						road->GetTransform().SetWorldPosition(float4((PosNX + PosX) / 2.f, ((PosNY + PosY) / 2.f) * sinf(30.f * GameEngineMath::DegreeToRadian),((PosNY + PosY ) /2.f - 5.f) * cosf(30.f * GameEngineMath::DegreeToRadian)));
						road->GetTransform().SetWorldRotation(60.f, 0, -atan2f(PosNX - PosX, PosNY - PosY) * GameEngineMath::RadianToDegree);
						(*iter)->PushNextlevel(*nextiter);
					}
				}
				else
				{
					std::shared_ptr<GameEngineTextureRenderer> road = CreateComponent<GameEngineTextureRenderer>();
					float PosX = (*iter)->GetTransform().GetWorldPosition().x;
					float PosY = (*iter)->posY_;
					float PosNX = (*nextiter)->GetTransform().GetWorldPosition().x;
					float PosNY = (*nextiter)->posY_;
					road->SetTexture("Path_alt_travel.png");
					//road->ScaleToTexture();
					road->GetTransform().SetWorldScale(float4(128.f, float4(PosX - PosNX, PosY - PosNY, 0.f, 0.f).Length() - 40.f));

					road->GetTransform().SetWorldPosition(float4((PosNX + PosX) / 2.f, ((PosNY + PosY) / 2.f) * sinf(30.f * GameEngineMath::DegreeToRadian), ((PosNY + PosY) / 2.f - 5.f) * cosf(30.f * GameEngineMath::DegreeToRadian)));
					road->GetTransform().SetWorldRotation(60.f, 0, -atan2f(PosNX - PosX, PosNY - PosY) * GameEngineMath::RadianToDegree);
					(*iter)->PushNextlevel(*nextiter);
				}
			}
		}
	}

}




void StageCreater::Update(float _deltaTime)
{
	stageObjects_;
}

bool StageCreater::CheckPushLevel()
{
	int ran = GameEngineRandom::mainRandom_.RandomInt(1, 100);
	if(ran > 50)
	{
		return true;
	}
	else
	{
		return false;
	}
}