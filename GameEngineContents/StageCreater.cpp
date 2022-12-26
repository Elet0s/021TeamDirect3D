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
		object->GetTransform().SetWorldPosition(1024 - 128.f, -650 * sinf(30.f * GameEngineMath::DegreeToRadian), -650 * cosf(30.f * GameEngineMath::DegreeToRadian));
		GroupActor.push_back(object);
	}

	{
		std::list<std::shared_ptr<StageObject>>& GroupActor = stageObjects_[0];
		std::shared_ptr<StageObject> object = GetLevel()->CreateActor<StageObject>();
		object->SetMyLevel(7);
		object->GetTransform().SetWorldPosition(1024 - 128.f, -2400 * sinf(30.f * GameEngineMath::DegreeToRadian), -2400 * cosf(30.f * GameEngineMath::DegreeToRadian));
		GroupActor.push_back(object);
	}

	{
		for (int level = 1; level < 7; level++)
		{
			int maxCount = GameEngineRandom::mainRandom_.RandomInt(2, 5);
			for (int Count = 0; Count < maxCount; Count++)
			{
				float x = 1200 / maxCount + GameEngineRandom::mainRandom_.RandomInt(1, 3) * 256.f;
				std::list<std::shared_ptr<StageObject>>& GroupActor = stageObjects_[level];
				std::shared_ptr<StageObject> object = GetLevel()->CreateActor<StageObject>();
				object->SetMyLevel(level);
				object->SetStageType(GameEngineRandom::mainRandom_.RandomInt(0, 4));
				object->GetTransform().SetWorldPosition( x , (- 2400 + 250 * level)* sinf(30.f * GameEngineMath::DegreeToRadian), (-2400 + 250 * level) * cosf(30.f * GameEngineMath::DegreeToRadian));
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
				if (level != 6)
				{
					if (true == CheckPushLevel())
					{
						(*iter)->PushNextlevel(*nextiter);
					}
				}
				else
				{
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