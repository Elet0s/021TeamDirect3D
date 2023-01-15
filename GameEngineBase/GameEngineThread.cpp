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
	//이 스레드가 실행할 함수를 세팅한다.

	this->thread_ = std::thread(LinkFunction, this, _threadName);
	//std::thread를 생성하면서 실행할 함수로 GameEngineThreadFunction()을, 넣어줄 매개변수로 
	// 이 GameEngineThread 객체와 붙여줄 스레드 이름을 넣어준다. 내가 넣어준 함수를 직접 호출하지 않는것에 주의할 것.
	//이렇게 생성된 스레드는 true == joinable 상태로 생성된다.
	//기본 생성자로 생성된 스레드는 false == joinable 상태로 생성된다. 
	// 아마 어떤 함수든 함수포인터가 스레드에 연결되어야만 true == joinable이 되는것 같다.
}

void GameEngineThread::Join()
{
	if (nullptr != this->workFunction_)
	{
		Sleep(1);	//원래는 지정한 시간만큼 스레드를 대기시키는 함수이지만, 
		//여기서는 대기 상태인 스레드는 스케줄링 대상에서 빼고 스레드가 가지고 있던 CPU 사용권을 가져와 다른 스레드에게 배분하게 하는게 주 목적이다.
		//Sleep(0)으로 하면 CPU 사용권을 같은 우선순위 스레드들 중 하나에게만 넘겨주고 같은 우선순위 스레드가 없으면 CPU 사용권을 다시 가져가 버리므로 
		// Sleep(1)이어야 우선순위 상관없이 아무 스레드 하나에게 CPU사용권을 넘겨줄 수 있다고 한다.

		this->thread_.join();	//이 스레드의 작업을 멈추고 부모 스레드가 종료될때까지 대기하게 하는 함수.
		//이 함수가 먼저 호출되서 스레드를 비우고 스레드 아이디를 0으로 만들어야만 std::thread의 소멸자가 제대로 실행될 수 있다.

		this->workFunction_ = nullptr;
	}
}

void GameEngineThread::LinkFunction(GameEngineThread* _thisThread, const std::string& _threadName)
{
	SetThreadDescription(		//스레드에 스레드 설명용 문자열을 붙여주는 함수. 여기서는 이름을 붙여준다.
		GetCurrentThread(),		//현재 스레드의 핸들을 반환하는 함수.
		GameEngineString::AnsiToUnicodeReturn(_threadName).c_str()	//스레드에 붙여줄 문자열. 여기서는 스레드 이름.
	);

	_thisThread->workFunction_(_thisThread);	//_thisThread에 연결시킨 함수 실행.
}
