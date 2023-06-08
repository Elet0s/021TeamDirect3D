#pragma once
#include "GameEngineNameObject.h"

class GameEngineThread : public GameEngineNameObject
{
	//std::thread와, 이 스레드가 실행할 함수를 하나로 묶어 관리하는 클래스.
	//GameEngineThread 단독으로 사용할 수도 있고, GameEngineThreadPool에 넣어서 사용할 수도 있다.

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
	//스레드를 생성하고 스레드에게 실행시킬 함수포인터를 연결하는 함수. _callback을 직접 호출하진 않는다.
	void Start(const std::string& _threadName, std::function<void(GameEngineThread*)> _callbackFunction);

	//이 스레드의 작업을 종료하고 대기 상태로 만들어서 부모 스레드로 합류시키는 함수. 
	//이 상태로 다시 스레드를 사용할 수도 있고, 그대로 스레드를 삭제할 수도 있다.
	void Join();

private:
	//std::thread 생성자의 매개변수로 들어가 호출되서, 이 스레드에 이름을 붙여주고, 지정해 둔 함수 포인터의 함수를 호출하는 함수.
	static void LinkFunction(GameEngineThread* _thisThread, const std::string& _threadName);

private:

	std::thread thread_;	//스레드. 
	//모든 스레드는 main()함수가 실행되면서 생성되는 메인 스레드의 자식 스레드이다.


	//std::thread: 각 운영체제마다 다른 스레드 생성 및 운용 방식을, C++위원회에서 통일된 인터페이스로 포장해서 
	// C++ 표준 라이브러리에 등록한 스레드 생성 운용 클래스. 실제로 같은 생성자에서도 Windows환경에서는 _beginthreadex()를, 
	// macOS환경에서는 _VSTD::__libcpp_thread_create()를 호출해서 스레드를 생성한다.

	//  thread(const thread&) = delete;
	//	thread& operator=(const thread&) = delete;
	//std::thread는 복사생성이 불가능하다.

	std::function<void(GameEngineThread*)> workFunction_;	//이 스레드가 실행할 함수의 포인터.

};