#pragma once
#include "GameEngineRes.h"
#include "GameEngineFBX.h"

class GameEngineFBXAnimation: public GameEngineRes<GameEngineFBXAnimation>, public GameEngineFBX
{
	friend GameEngineRes<GameEngineFBXAnimation>;
	//GameEngineFBXAnimation Ŭ������ �����̺� �Ҹ��ڸ� GameEngineResŬ�������� ȣ���ϱ� ���� ���.

	//$resourcetype$ resource_;
	//���ҽ�Ÿ�Կ� �°� ��ĥ ��.

private:
	GameEngineFBXAnimation();
	~GameEngineFBXAnimation();
	//�ܺο��� ���ڴ�� ���ҽ��� ����/�����ϴ°� ���� ���ؼ� ������/�Ҹ��ڸ� �����̺����� �����ؼ� �ܺ� ������ ���´�.
	//�� �����ӿ�ũ�� ���ҽ��� �ݵ�� �Ҹ��ڰ� �ƴ϶� ResourceDestroy()�Լ����� �����ؾ� �Ѵ�.
	//���α׷� ���������� ���ҽ������� ���ϸ� ������ �������� �׷��� �ִ��� ���Ƶд�.

	GameEngineFBXAnimation(const GameEngineFBXAnimation& _other) = delete;
	GameEngineFBXAnimation(GameEngineFBXAnimation&& _other) noexcept = delete;
	GameEngineFBXAnimation& operator=(const GameEngineFBXAnimation& _other) = delete;
	GameEngineFBXAnimation& operator=(const GameEngineFBXAnimation&& _other) = delete;


public:	
	static GameEngineFBXAnimation* Create(const std::string& _name);

	void Setting();	//�ش� ���ҽ��� ������ ���������ο� �����ϴ� �Լ�.

};

