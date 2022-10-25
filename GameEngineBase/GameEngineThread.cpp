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

void GameEngineThread::Start(const std::string& _threadName, std::function<void(GameEngineThread*)> _callback)
{
	this->workFunction_ = _callback;
	//이 스레드가 실행할 함수를 세팅한다.

	this->thread_ = std::thread(GameEngineThreadFunction, this, _threadName);
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
		Sleep(1);	
		this->thread_.join();	//이 스레드의 작업을 멈추고 부모 스레드가 종료될때까지 대기하게 하는 함수.
		//이 함수가 먼저 호출되서 스레드를 비우고 스레드 아이디를 0으로 만들어야만 std::thread의 소멸자가 제대로 실행될 수 있다.

		this->workFunction_ = nullptr;

		//if (true == this->thread_.joinable())
		//{
		//	MsgBoxAssert("이 스레드의 join()이 제대로 이루어지지 않았습니다.");
		//}
		//std::thread의 소멸자에 이미 이런 경우에 에러를 발생시키는 코드가 있다고 한다.
	}
}

void GameEngineThread::GameEngineThreadFunction(GameEngineThread* _thisThread, const std::string& _threadName)
{
	//여기는 스레드의 영역.

	SetThreadDescription(		//스레드에 스레드 설명용 문자열을 붙여주는 함수. 여기서는 이름을 붙여준다.
		GetCurrentThread(),		//현재 스레드의 핸들을 반환하는 함수.
		GameEngineString::AnsiToUnicodeReturn(_threadName).c_str()	//스레드에 붙여줄 문자열. 여기서는 스레드 이름.
	);

	_thisThread->workFunction_(_thisThread);	//_thisThread에 연결시킨 함수 실행.
}
