#include "PreCompile.h"
#include "GameEngineThread.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

GameEngineThread::GameEngineThread()
{
}

GameEngineThread::GameEngineThread(
	const std::string& _threadName,
	std::function<void(GameEngineThread*)> _callback
)
{
	this->Start(_threadName, _callback);
}

GameEngineThread::~GameEngineThread()
{
	this->Join();
}

void GameEngineThread::Start(const std::string& _threadName, std::function<void(GameEngineThread*)> _callbackFunction)
{
	this->workFunction_ = _callbackFunction;
	//�� �����尡 ������ �Լ��� �����Ѵ�.

	this->thread_ = std::thread(LinkFunction, this, _threadName);
	//std::thread�� �����ϸ鼭 ������ �Լ��� GameEngineThreadFunction()��, �־��� �Ű������� 
	// �� GameEngineThread ��ü�� �ٿ��� ������ �̸��� �־��ش�. ���� �־��� �Լ��� ���� ȣ������ �ʴ°Ϳ� ������ ��.
	//�̷��� ������ ������� true == joinable ���·� �����ȴ�.
	//�⺻ �����ڷ� ������ ������� false == joinable ���·� �����ȴ�. 
	// �Ƹ� � �Լ��� �Լ������Ͱ� �����忡 ����Ǿ�߸� true == joinable�� �Ǵ°� ����.
}

void GameEngineThread::Join()
{
	if (nullptr != this->workFunction_)
	{
		Sleep(1);	//������ ������ �ð���ŭ �����带 ����Ű�� �Լ�������, 
		//���⼭�� ��� ������ ������� �����ٸ� ��󿡼� ���� �����尡 ������ �ִ� CPU ������ ������ �ٸ� �����忡�� ����ϰ� �ϴ°� �� �����̴�.
		//Sleep(0)���� �ϸ� CPU ������ ���� �켱���� ������� �� �ϳ����Ը� �Ѱ��ְ� ���� �켱���� �����尡 ������ CPU ������ �ٽ� ������ �����Ƿ� 
		// Sleep(1)�̾�� �켱���� ������� �ƹ� ������ �ϳ����� CPU������ �Ѱ��� �� �ִٰ� �Ѵ�.

		this->thread_.join();	//�� �������� �۾��� ���߰� �θ� �����尡 ����ɶ����� ����ϰ� �ϴ� �Լ�.
		//�� �Լ��� ���� ȣ��Ǽ� �����带 ���� ������ ���̵� 0���� �����߸� std::thread�� �Ҹ��ڰ� ����� ����� �� �ִ�.

		this->workFunction_ = nullptr;
	}
}

void GameEngineThread::LinkFunction(GameEngineThread* _thisThread, const std::string& _threadName)
{
	SetThreadDescription(		//�����忡 ������ ����� ���ڿ��� �ٿ��ִ� �Լ�. ���⼭�� �̸��� �ٿ��ش�.
		GetCurrentThread(),		//���� �������� �ڵ��� ��ȯ�ϴ� �Լ�.
		GameEngineString::AnsiToUnicodeReturn(_threadName).c_str()	//�����忡 �ٿ��� ���ڿ�. ���⼭�� ������ �̸�.
	);

	_thisThread->workFunction_(_thisThread);	//_thisThread�� �����Ų �Լ� ����.
}
