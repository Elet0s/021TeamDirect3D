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

	public:
		virtual void Process() = 0;
	};

	class GameEngineThreadCallbackJob : public GameEngineThreadJob
	{

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



	//이 클래스의 존재 이유: IOCP 객체가 가진 스레드 풀을 이용해서 스레드들을 관리하고 주어진 작업을 적절하게 배분하는 것.

	//오브젝트 풀(object pool): 오브젝트에 해당하는 무언가를 미리 대량으로 생성해서 풀(pool)에 보관해 두었다가 
	// 필요하면 꺼내 쓰고, 필요 없어져도 삭제하지 않고 다시 풀에 돌려놓는 과정을 반복하는 개념을 말한다.
	//C++ 연산 중 가장 연산 소요가 큰 new와 delete 연산의 빈도를 줄일 수 있다는 장점과,
	// 대량의 메모리를 필요로 한다는 단점이 있다. 
	
	//헤테로지니어스(Heterogeneous: 이종) 방식:
	//작업을 종류별로 쪼개서 해당 작업 전담 스레드에게 맡기는 스타일.
	//구성 초기부터 멀티스레딩 상황을 염두에 두었다면 이 방식이 더 낫다고 한다.
	
	//호모지니어스(Homogenous: 동종) 방식:
	//작업 종류 상관없이 들어오는 순서대로 대기중인 스레드에게 맡기는 스타일.
	//이벤트가 발생해야 작동하는 방식이라서 이벤트 드리븐(Event Driven), 데이터 드리븐(Data Driven) 방식이라고도 한다.
	//주로 서버에서 사용.
	//이 프레임워크에선 이 방식으로 멀티스레드 사용.

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
	//스레드풀 초기화 함수. _threadCount가 기본값인 0이라면 IOCP 객체가 자동으로 적절한 스레드 개수를 정한다.
	void Initialize(const std::string_view& _threadName, int _threadCount = 0);
	//코어 수 * 2가 멀티스레딩에 적절한 스레드 개수라고 한다. 

	//메인스레드가 직접 뭔가를 작업하는 것이 아니라, IO완료큐에 작업을 분배, 등록시키는 함수.
	//IO완료큐에 등록된 작업 함수포인터는 IOCP가 받아서 자기가 가진 스레드풀 안에서 가장 적합한 스레드에게 맡기게 된다. 
	void DistributeWork(std::function<void()> _callback);

private:
	//메인 스레드가 직접 호출할 함수가 아닌, 스레드풀에 등록된 스레드들이 생성과 동시에 LinkFunction()함수를 통해 호출하게 될 함수. 
	//GameEngineThreadPool 객체가 파괴되기 전까지 계속 GetQueuedCompletionStatus()함수를 호출하는 구조로 되어 있으므로
	//IOCP가 GameEngineThread 객체들을 자기 스레드풀에 넣고 관리할 수 있게 된다.
	static void	ExecuteWork(
		GameEngineThreadPool* _threadPool,
		GameEngineThread* _thread,
		HANDLE _iocpHandle
	);


private:
	HANDLE iocpHandle_;		//IOCP 객체와 연결된 핸들. 이 클래스의 핵심. 스레드풀도 이 핸들과 연결된 IOCP 객체가 관리한다.
	//특별히 막아두지는 않았지만 IOCP 객체가 관리하는 스레드풀을 한개만 쓸 게 거의 확실하므로 GameEngineThreadPool 객체도 
	//GameEngineCore에서 정적 멤버변수로 한개만 가지게 한다.
	//IOCP 자체는 직접 통제할 수 없다.

	//IOCP(Input/Output Completion Port: 입출력 완료 포트): 윈도우즈에서 제공하는
	// 스레드 관리 전문 커널 오브젝트(프로세스가 아닌, 운영체제 수준에서 생성한 프로세스, 스레드, 파일 등의 리소스 관리용 구조체).
	//스레드나 프로세스가 생성하는 오브젝트가 아니라 운영체제가 직접 생성 관리하는 오브젝트이므로 스레드나 프로세스의 상태와 관계 없이 
	// 실시간으로 스레드풀을 관리할 수 있다.

	//IOCP 작동 원리:
	//어느 IO작업이 완료되면 IO 완료 패킷(Completion Packet)의 정보(실제 패킷 아님)가 IO완료 큐(Completion Queue)에 쌓인다. 
	// 혹은 PostQueuedCompletionStatus()함수를 통해 직접 넣어줄 수도 있다. 
	//어떤 방식으로든 IO완료 큐에 IO 완료 패킷 정보가 쌓이면 IOCP가 스레드풀 안의 스레드 중 하나를 골라 깨운다.
	//깨어난 스레드가 GetQueuedCompletionStatus()함수를 호출하면 그 큐에 쌓인 패킷 정보들 중 
	// 가장 먼저 쌓여있던 것을 뽑아서 완료 키에 연결된 함수를 처리한다.


	//컨텍스트 스위칭(Context Switching):
	//이 스레드/프로세스가 가진 CPU 사용 권한을 다른 스레드/프로세스에게 넘겨주는 작업. 
	//CPU 사용권을 넘겨주기 전에 현재 진행중이던 작업의 정보를 다른 곳에 저장해 두어야 하고, 
	//CPU 사용권을 넘겨받기 전에 이전에 진행하고있던 작업 정보를 다시 불러와야 하는데 
	//컨텍스트 스위칭이 너무 자주 일어나게 되면 작업을 진행하는것보다 작업 정보를 저장하거나 불러오는데 
	//더 많은 연산을 하게 되는 비효율이 생기게 된다. 그래서 컨텍스트 스위칭은 최소한으로만 일어나야 한다.
	//메모리를 공유하지 않는 프로세스간 컨텍스트 스위칭보다 메모리를 많은 부분 공유하는 스레드간 컨텍스트 스위칭이 더 빠르다고 한다.


	//IOCP의 스레드 컨테이너들.
	//Release Thread List(활성화 스레드 리스트): 현재 작업 진행 중인 스레드들의 ID가 저장되는 리스트.
	//CreateIoCompletionPort()함수에서 마지막으로 넣어준 값이 이 리스트의 크기가 된다. 
	// 
	//Pause Thread List(일시정지 스레드 리스트):
	//Release Thread List에서 작업하던 중 Sleep()함수를 호출하거나 하는 등의 이유로 일시정지 상태가 된 스레드들의 ID가 보관되는 리스트.
	//일시정지 상태의 스레드들이 오는 리스트지만, 일시정지가 끝났어도 Release Thread List에 빈 자리가 없다면 계속 여기에서 대기한다.
	//  
	//Waiting Thread Queue(대기 스레드 큐):  
	// 스레드풀에 처음 들어가는 스레드든 Release Thread List의 스레드 중 완료루틴이 끝난 스레드든 GetQueuedCompletionStatus()함수를
	// 호출하였지만 IOCP로부터 작업을 받지 못하고 대기중인 모든 스레드들의 ID가 여기에 들어간다. 
	//어떤 이유로든 Release Thread List에 빈 자리가 생겼는데 IO완료큐에 새 작업이 들어오면, 
	// IOCP가 여기에 있는 스레드 중 하나를 빼서 Release Thread List에 넣고 작업을 시킨다.
	//이름은 큐지만 LIFO방식이라서 가장 마지막으로 들어간 스레드부터 다시 호출되는 구조이다.
	//스레드를 준비시키는 컨텍스트 스위칭도 연산 소요이므로, 
	// 이미 준비되어있어서 컨텍스트 스위칭이 필요없을 확률이 가장 높은 마지막 스레드부터 재사용하기 위한 구조라고 한다.



	int createdThreadCount_;		//생성된 스레드 개수.
	std::atomic<bool> isRunning_;	//true: 스레드풀 작동중. 
	std::atomic<int> destroyedThreadCount_;	//파괴된 스레드 개수.

	//std::atomic<T>: 원자성
	//스레드들끼리 서로 침범할 수 있는 일반 연산이 아닌, 원자처럼 쪼갤수 없는 연산을 가능하게 한다고 해서 atomic.

	std::vector<GameEngineThread*> allThreads_;	//IOCP가 관리하게 될 모든 GameEngineThread 객체들.
};

