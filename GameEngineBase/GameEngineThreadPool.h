#pragma once

enum class ThreadWorkType
{
	UserWork = -1,
	Destroy = -2
};

class GameEngineThread;
class GameEngineThreadPool
{
	class GameEngineThreadJob
	{
		//이 클래스의 존재 이유:
	public:
		virtual void Process() = 0;
	};

	class GameEngineThreadCallbackJob : public GameEngineThreadJob
	{
		//이 클래스의 존재 이유:
		//ThreadJob과 ThreadCallbackJob이 따로 존재하는 이유는??

	public:
		std::function<void()> work_;

		void Process() override
		{
			if (nullptr != work_)
			{
				work_();
			}
		}
	};



	//이 클래스의 존재 이유: IOCP 객체의 스레드 풀을 이용해서 스레드들을 관리하고 주어진 작업을 적절하게 배분한다.


	//오브젝트 풀(object pool): 오브젝트에 해당하는 무언가를 미리 대량으로 생성해서 풀(pool)에 보관해 두었다가 
	// 필요하면 꺼내 쓰고, 필요 없어져도 삭제하지 않고 다시 풀에 돌려놓는 과정을 반복하는 개념을 말한다.
	//C++ 연산 중 가장 시간이 많이 필요한 new와 delete 연산의 빈도를 줄일 수 있다는 장점과,
	// 대량의 메모리를 필요로 한다는 단점이 있다. 

public:
	GameEngineThreadPool();
	GameEngineThreadPool(const std::string& _threadName, int _threadCount = 0);
	~GameEngineThreadPool();

protected:
	GameEngineThreadPool(const GameEngineThreadPool& _other) = delete;
	GameEngineThreadPool(GameEngineThreadPool&& _other) noexcept = delete;

private:
	GameEngineThreadPool& operator=(const GameEngineThreadPool& _other) = delete;
	GameEngineThreadPool& operator=(const GameEngineThreadPool&& _other) = delete;


public:
	//스레드풀 초기화 함수. _threadCount가 기본값인 0이라면 내부에서 자동으로 적절한 스레드 개수를 정한다.
	void Initialize(const std::string& _threadName, int _threadCount = 0);
	//코어 수 * 2가 멀티스레딩에 적절한 스레드 개수라고 한다. 

	void Work(std::function<void()> _callback);

private:
	//
	static void	ThreadPoolFunction(
		GameEngineThreadPool* _threadPool,
		GameEngineThread* _thread,
		HANDLE _iocpHandle
	);


private:
	HANDLE iocpHandle_;		//IOCP 객체와 연결된 핸들. 이 클래스의 핵심. 스레드풀도 이 핸들과 연결된 IOCP 객체가 관리한다.
	//IOCP(Input/Output Completion Port: 입출력 완료 포트): 윈도우즈에서 사용되는 멀티스레딩 시 IO작업 배분 전문 논 블로킹 프로세스.
	// 윈도우즈의 IO 모델들 중 최고성능이라고 한다. 
	//어느 IO작업이 완료되면 IO 완료 패킷(Compleltion Packet)의 정보가 IO완료 큐(Completion Queue)에 쌓인다. 
	// 혹은 PostQueuedCompletionStatus()함수를 통해 직접 넣어줄 수도 있다. GetQueuedCompletionStatus()함수가 호출되면 그 큐에 쌓인 패킷 정보들 중 
	// 가장 먼저 쌓여있던 것을 뽑아서 완료 키에 연결된 함수를 적절한 방식으로 스레드들 중 하나에게 배분하여 처리하게 한다.
	//이 프레임워크에선 IOCP의 스레드 관리 및 작업 배분 기능만 사용한다.

	//Waiting Thread Queue(대기 스레드 큐):
	//스레드풀의 풀이 되는 컨테이너.

	//Release Thread List(대기 해제(?) 스레드 리스트): 작업 처리 중인 스레드들의 ID가 여기에 등록된다.
	//CreateIoCompletionPort()함수에서 마지막으로 넣어준 값이 이 큐의 크기가 된다.

	//Pause Thread List(일시정지 스레드 리스트):
	//여기에 스레드 ID가 들어가는 것이 스레드가 Alertable Wait 상태가 되었다고 하는 것 같다.


	//IO(Input Output)작업: 프로세스 외부에 있는 특정한 메모리를 읽어들이거나 수정하는 작업. 대개는 파일 입출력을 말한다.
	//블로킹(Blocking): 한 작업이 끝날때까지 다른 작업이 진행되지 않는 것.
	//논 블로킹(Non Blocking): 이 작업은 이 작업대로, 저 작업은 저 작업대로 진행되면서 서로의 진행을 방해(Block)하지 않는 것.
	//동기(Synchronous): 작업 지시를 하는 주체가, 작업 지시를 받는 객체의 작업 종료를 기다렸다가 다음 작업을 지시하는것.
	//비동기(Asynchronous): 작업 지시를 하는 주체가, 작업 지시를 받는 객체의 작업 종료를 신경쓰지 않고 다음 작업을 지시하는 것.


	//동기 + 블로킹: 싱글스레딩.
	//동기 + 논 블로킹: 
	//비동기 + 블로킹: ????
	//비동기 + 논 블로킹: 멀티태스킹.



	int createdThreadCount_;		//생성된 스레드 개수.
	std::atomic<bool> isRunning_;	//
	std::atomic<int> destroyedThreadCount_;	//파괴된 스레드 개수.

	//std::atomic<T>: 원자성
	//스레드들끼리 서로 침범할 수 있는 일반 연산이 아닌, 원자처럼 쪼갤수 없는 연산을 가능하게 한다고 해서 atomic.

	std::vector<GameEngineThread*> allThreads_;	//생성된 모든 GameEngineThread 객체들.
};

