#pragma once
#include "GameEngineNameObject.h"

class GameEngineThread : public GameEngineNameObject
{
	//std::thread와, 이 스레드가 실행할 함수를 하나로 묶어 관리하는 클래스.
	//GameEngineThread 단독으로 사용할 수도 있고, GameEngineThreadPool에 넣어서 사용할 수도 있다.

	//Heterogeneous Style
	//작업을 종류별로 쪼개서 해당 작업 전담 스레드에게 맡기는 스타일.
	//구성 초기부터 멀티스레딩 상황을 염두에 두었다면 이 방식이 더 낫다고 한다.

	//Homogenous(Event Driven, Data Driven) Style
	//작업 종류 상관없이 들어오는 순서대로 대기중인 스레드에게 맡기는 스타일.
	//주로 서버에서 사용.
	//이 프레임워크에선 이 방식으로 진행.


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
	void Start(const std::string& _threadName, std::function<void(GameEngineThread*)> _callback);

	//이 스레드의 작업을 종료하고 대기 상태로 만들어서 부모 스레드로 합류시키는 함수. 
	//이 상태로 다시 스레드를 사용할 수도 있고, 그대로 스레드를 삭제할 수도 있다.
	void Join();

private:
	//std::thread 생성자의 매개변수로 들어가 호출되서, 이 스레드에 이름을 붙여주고, 지정해 둔 함수 포인터의 함수를 호출하는 함수.
	static void GameEngineThreadFunction(GameEngineThread* _thisThread, const std::string& _threadName);

private:

	std::thread thread_;	//스레드. 
	//모든 스레드는 main()함수가 실행되면서 생성되는 메인 스레드의 자식 스레드이다.
	//  thread(const thread&) = delete;
	//	thread& operator=(const thread&) = delete;
	//std::thread는 복사생성이 불가능하다.

	std::function<void(GameEngineThread*)> workFunction_;	//이 스레드가 실행할 함수의 포인터.
	//자기가 자기 안의 함수를 호출할때 매개변수가 자기 자신이면 무한 재귀되는게 아닌가??
};