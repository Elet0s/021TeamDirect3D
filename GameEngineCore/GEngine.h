#pragma once
#include "GameEngineCore.h"




class GEngine
{
	//�л�� �������̽� ���տ� Ŭ����.
	//���ӿ����ھ��� Ŭ�������� �� Ŭ������ ����ؼ� ���� �ȵȴ�. 
	//������ �����ڸ��� ���� �������̽� ������ Ŭ����.

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

