#pragma once
#include "GameEngineNameObject.h"

class GameEngineThread : public GameEngineNameObject
{
	//std::thread��, �� �����尡 ������ �Լ��� �ϳ��� ���� �����ϴ� Ŭ����.
	//GameEngineThread �ܵ����� ����� ���� �ְ�, GameEngineThreadPool�� �־ ����� ���� �ִ�.

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
	void Start(const std::string& _threadName, std::function<void(GameEngineThread*)> _callbackFunction);

	//�� �������� �۾��� �����ϰ� ��� ���·� ���� �θ� ������� �շ���Ű�� �Լ�. 
	//�� ���·� �ٽ� �����带 ����� ���� �ְ�, �״�� �����带 ������ ���� �ִ�.
	void Join();

private:
	//std::thread �������� �Ű������� �� ȣ��Ǽ�, �� �����忡 �̸��� �ٿ��ְ�, ������ �� �Լ� �������� �Լ��� ȣ���ϴ� �Լ�.
	static void LinkFunction(GameEngineThread* _thisThread, const std::string& _threadName);

private:

	std::thread thread_;	//������. 
	//��� ������� main()�Լ��� ����Ǹ鼭 �����Ǵ� ���� �������� �ڽ� �������̴�.


	//std::thread: �� �ü������ �ٸ� ������ ���� �� ��� �����, C++����ȸ���� ���ϵ� �������̽��� �����ؼ� 
	// C++ ǥ�� ���̺귯���� ����� ������ ���� ��� Ŭ����. ������ ���� �����ڿ����� Windowsȯ�濡���� _beginthreadex()��, 
	// macOSȯ�濡���� _VSTD::__libcpp_thread_create()�� ȣ���ؼ� �����带 �����Ѵ�.

	//  thread(const thread&) = delete;
	//	thread& operator=(const thread&) = delete;
	//std::thread�� ��������� �Ұ����ϴ�.

	std::function<void(GameEngineThread*)> workFunction_;	//�� �����尡 ������ �Լ��� ������.

};