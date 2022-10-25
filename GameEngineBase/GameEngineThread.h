#pragma once
#include "GameEngineNameObject.h"

class GameEngineThread : public GameEngineNameObject
{
	//std::thread��, �� �����尡 ������ �Լ��� �ϳ��� ���� �����ϴ� Ŭ����.
	//GameEngineThread �ܵ����� ����� ���� �ְ�, GameEngineThreadPool�� �־ ����� ���� �ִ�.

	//Heterogeneous Style
	//�۾��� �������� �ɰ��� �ش� �۾� ���� �����忡�� �ñ�� ��Ÿ��.
	//���� �ʱ���� ��Ƽ������ ��Ȳ�� ���ο� �ξ��ٸ� �� ����� �� ���ٰ� �Ѵ�.

	//Homogenous(Event Driven, Data Driven) Style
	//�۾� ���� ������� ������ ������� ������� �����忡�� �ñ�� ��Ÿ��.
	//�ַ� �������� ���.
	//�� �����ӿ�ũ���� �� ������� ����.


public:
	GameEngineThread();
	GameEngineThread(const std::string& _threadName, std::function<void(GameEngineThread*)> _callback);
	~GameEngineThread();

protected:
	GameEngineThread(const GameEngineThread& _other) = delete;
	GameEngineThread(GameEngineThread&& _other) noexcept = delete;

private:
	GameEngineThread& operator=(const GameEngineThread& _other) = delete;
	GameEngineThread& operator=(const GameEngineThread&& _other) = delete;


public:
	//�����带 �����ϰ� �����忡�� �����ų �Լ������͸� �����ϴ� �Լ�. _callback�� ���� ȣ������ �ʴ´�.
	void Start(const std::string& _threadName, std::function<void(GameEngineThread*)> _callback);

	//�� �������� �۾��� �����ϰ� ��� ���·� ���� �θ� ������� �շ���Ű�� �Լ�. 
	//�� ���·� �ٽ� �����带 ����� ���� �ְ�, �״�� �����带 ������ ���� �ִ�.
	void Join();

private:
	//std::thread �������� �Ű������� �� ȣ��Ǽ�, �� �����忡 �̸��� �ٿ��ְ�, ������ �� �Լ� �������� �Լ��� ȣ���ϴ� �Լ�.
	static void GameEngineThreadFunction(GameEngineThread* _thisThread, const std::string& _threadName);

private:

	std::thread thread_;	//������. 
	//��� ������� main()�Լ��� ����Ǹ鼭 �����Ǵ� ���� �������� �ڽ� �������̴�.
	//  thread(const thread&) = delete;
	//	thread& operator=(const thread&) = delete;
	//std::thread�� ��������� �Ұ����ϴ�.

	std::function<void(GameEngineThread*)> workFunction_;	//�� �����尡 ������ �Լ��� ������.
	//�ڱⰡ �ڱ� ���� �Լ��� ȣ���Ҷ� �Ű������� �ڱ� �ڽ��̸� ���� ��͵Ǵ°� �ƴѰ�??
};