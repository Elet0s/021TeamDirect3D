#pragma once
#include "GameEngineCore.h"




class GEngine
{
	//분산된 인터페이스 통합용 클래스.
	//게임엔진코어의 클래스들은 이 클래스를 사용해선 절대 안된다. 
	//컨텐츠 제작자만을 위한 인터페이스 제공용 클래스.

	static bool isCollisionDebug_;


private:

	GEngine();
	virtual ~GEngine() = 0;

	GEngine(const GEngine& _other) = delete;
	GEngine(GEngine&& _other) noexcept = delete;
	GEngine& operator=(const GEngine& _other) = delete;
	GEngine& operator=(GEngine&& _other) = delete;

public:
	static void ChangeLevel(const std::string& _levelName);
	static void CollisionDebugOn();
	static void CollisionDebugOff();
	static void CollisionDebugSwitch();
	static bool IsCollisionDebug();
	static GameEngineLevel* GetCurrentLevel();


};

