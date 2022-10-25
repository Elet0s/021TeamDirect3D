#include "PreCompile.h"
#include "GameEngineThreadPool.h"
#include "GameEngineThread.h"
#include "GameEngineDebug.h"

GameEngineThreadPool::GameEngineThreadPool()
	: iocpHandle_(nullptr),
	createdThreadCount_(0),
	isRunning_(false),
	destroyedThreadCount_(0)
{
}

GameEngineThreadPool::GameEngineThreadPool(const std::string& _threadName, int _threadCount /*= 0*/)
	: iocpHandle_(nullptr), createdThreadCount_(0), isRunning_(false), destroyedThreadCount_(0)
{
	Initialize(_threadName, _threadCount);
}

GameEngineThreadPool::~GameEngineThreadPool()
{
	this->isRunning_ = false;

	while (true)
	{
		if (false == PostQueuedCompletionStatus(
			iocpHandle_,
			static_cast<DWORD>(ThreadWorkType::Destroy),
			0,
			nullptr
		))
		{
			MsgBoxAssert("스레드에게 콜백잡을 전달하는데 실패했습니다.");
			return;
		}

		Sleep(1);

		if (destroyedThreadCount_ == createdThreadCount_)
		{
			break;
		}
	}

	for (size_t i = 0; i < this->allThreads_.size(); i++)
	{
		allThreads_[i]->Join();
		delete allThreads_[i];
	}

}

void GameEngineThreadPool::Initialize(const std::string& _threadName, int _threadCount /*= 0*/)
{
	this->createdThreadCount_ = _threadCount;

	if (0 == this->createdThreadCount_)
	{
		SYSTEM_INFO info = { 0 };
		GetSystemInfo(&info);	//OS에게 시스템 정보를 얻어오는 함수.
		createdThreadCount_ = info.dwNumberOfProcessors;	// 생성할 스레드 수를 이 시스템의 프로세서 개수로 정한다.
	}

	this->iocpHandle_ = CreateIoCompletionPort(	//IOCP 객체를 생성하고 거기에 연결된 핸들을 주는 함수.
		//파일 핸들이 NULL이 아니라면 넣어준 파일 핸들에 생성한 IOCP 핸들을 연결해서 반환하기도 한다.
		//파일 핸들과 기존 IOCP핸들을 넣어준다면 IOCP 핸들에 파일 핸들을 등록시켜주는 작업도 하는 함수이기도 하다.

		INVALID_HANDLE_VALUE,		//파일 핸들. 완전히 새로 생성하면 INVALID_HANDLE_VALUE을 넣는다.
		//MSDN에 의하면 이게 단순한 파일 핸들만을 가리키는것이 아니라 
		// 네트워크 엔드포인트, TCP 소켓, 네임드 파이프 서버 및 메일 슬롯과 같이 overlapped I/O를 지원하는 
		// 모든 시스템 개체들의 핸들까지 모두 포함하는 개념이라고 한다.
		//IOCP 핸들과 연결해야하는 여러 핸들을 넣고 이 함수를 계속 호출해서 
		// 한개의 IOCP 핸들에 여러 파일 핸들들을 등록시키는것이 이 함수의 사용법 중 한개라고 한다.

		NULL,						//기존 IOCP핸들. 새로 생성한다면 NULL을 넣는다.

		NULL,						//파일 핸들에 연결될 완료 키(Completion Key). 사용자 입력 데이터.
		//8바이트 포인터 형식이므로 여기에 스레드에게 실행시킬 함수의 포인터를 넣어 전송할 수 있다. 
		// 이 함수를 완료 루틴(Completion Routine)이라고 한다. 완료 루틴과 관계된 키값이라서 완료 키라고 하는것일수도 있다.
		//당장은 IOCP 핸들 생성만 해 둘 것이므로 NULL을 넣는다. 

		this->createdThreadCount_			//이 IOCP 객체가 관리하게 될 최대 스레드 수.
		//0을 넣으면 자동으로 프로세서 숫자를 알아내서 넣어준다고 한다.
	);

	if (nullptr == iocpHandle_)
	{
		MsgBoxAssert("IOCP 핸들 생성 실패.");
		return;
	}

	isRunning_ = true;
	destroyedThreadCount_ = 0;

	for (size_t i = 0; i < this->createdThreadCount_; i++)
	{
		GameEngineThread* newThread = new GameEngineThread();
		allThreads_.push_back(newThread);

		newThread->SetName(_threadName + std::to_string(i));
		newThread->Start(
			_threadName + std::to_string(i),
			std::bind(ThreadPoolFunction, this, newThread, iocpHandle_)
		);
	}
}

void GameEngineThreadPool::Work(std::function<void()> _callback)
{
	if (nullptr == _callback)
	{
		MsgBoxAssert("유효하지 않은 함수 포인터입니다.");
		return;
	}

	GameEngineThreadCallbackJob* newJob = new GameEngineThreadCallbackJob();

	newJob->work_ = _callback;

	//넣어준 핸들과 연결된 IOCP 객체에게, 스레드 하나를 깨워서 ULONG_PTR 형태로 변환한 함수포인터를 전달해 스레드가 실행하게 한다.

	if (false == PostQueuedCompletionStatus(		//지정한 IOCP객체의 IO완료 큐에 IO완료 패킷의 이벤트를 넣는 함수.
		//여기에 넣어진 IO완료 패킷 이벤트는 GetQueuedCompletionStatus()함수가 호출될때마다 넣은 순서대로 하나씩 뽑혀서 IOCP 객체가 처리하게 된다.
		//

		iocpHandle_,	//여기에 넣어준 핸들과 연결된 IOCP 객체의 IO완료 큐에 IO완료 패킷을 넣는다.

		static_cast<DWORD>(ThreadWorkType::UserWork),	//지금까지 전달된 누적 바이트 크기를 전달받을 DWORD* 변수.
		//실제로는 사전에 약속된 정수를 전달해서 그 정수에 해당하는 ThreadWorkType 열거형으로 변환,
		// 어떤 종류의 작업인지 알 수 있게 한다.

		reinterpret_cast<ULONG_PTR>(newJob),	//IOCP 객체가 스레드에게 배분할 함수의 함수 포인터.

		nullptr			//Overlapped IO작업시 전달해야 하는 OVERLAPPED 구조체의 이중포인터.
		//원래는 IOCP의 큐에 쌓인 IO완료패킷 정보가 어떤 IO작업의 완료를 알리는 패킷의 정보인지 판단하는 식별자 역할을 하지만,
		//스레드만 운용할때는 의미없는 변수이므로 nullptr만 계속 보낼 것이다.
	))
	{
		MsgBoxAssert("스레드에게 콜백잡을 전달하는데 실패했습니다.");
		return;
	}


}

void GameEngineThreadPool::ThreadPoolFunction(GameEngineThreadPool* _threadPool, GameEngineThread* _thread, HANDLE _iocpHandle)
{
	DWORD byte = 0;		//지금까지 전달된 누적 바이트 크기. 실제로는 스레드에게 실행시킬 작업의 유형.

	//IOCP 객체를 통해 스레드에게 전달할 함수포인터. 
	ULONG_PTR completionKey = NULL;
	//IO작업이 끝나면 대기중인 스레드에게 실행시킬 함수를 완료 루틴(Completion Routine)이라고 하는 데,
	// 그 함수의 포인터라서 Completion Key인것 같다.

	LPOVERLAPPED lpOverlapped = NULL;	//Overlapped IO작업시 필요한 OVERLAPPED 구조체의 포인터. 실제로는 사용하지 않음.


	while (_threadPool->isRunning_)
	{
		GetQueuedCompletionStatus(	//IOCP 객체에게 IO완료 큐에서 IO 완료패킷(Completion Packet)의 정보 하나를 꺼내오게 하는 함수.
			// GQCS()라는 약자로도 쓰는것 같다.
			//원래는 비동기적으로 중첩되서 실행되는 IO작업들의 제각각인 완료 여부를 PostQueuedCompletionStatus()함수를 통해 
			// IOCP 객체에게 알리고 CompletionKey를 통해 전달된 함수(Completion routine)의 포인터를, 
			// 대기중인 스레드들 중 하나에게 적절하게 배분하게 하는것이 이 함수의 목적이지만 
			// 여기서는 Completion routine을 대기중인 스레드들 중 하나에게 적절하게 배분하는 기능만 사용한다.
			//어떤 스레드에게 Completion routine이 배분될 지는 알 수 없다.

			_iocpHandle, 		  //IOCP 핸들.

			&byte,				  //지금까지 전달된 누적 바이트 크기를 전달받을 DWORD* 변수.
			//실제로는 사전에 약속된 정수를 전달받아서 그 정수에 해당하는 ThreadWorkType 열거형으로 변환,
			// 어떤 종류의 작업인지 알 수 있게 한다.

			&completionKey,		  //CreateIoCompletionPort()함수에서 파일 핸들에 붙여준 컴플리션 키.
			//IO작업이 완료되면 이 키로 등록된 함수포인터가 OS에 의해 대기(Alertable wait)중인 아무 스레드에게 배분되어 호출된다. 
			//이 함수를 가리켜 Completion Routine이라고 한다.

			&lpOverlapped,		  //Overlapped IO작업시 전달받아야 하는 OVERLAPPED 구조체의 이중포인터.
			//원래는 IOCP의 큐에 쌓인 IO완료패킷이 어떤 IO작업의 완료를 알리는 패킷인지 판단하는 식별자 역할을 하지만,
			//스레드만 운용할때는 의미없는 변수이므로 nullptr만 계속 수신할 것이다.

			INFINITE			  //최대 대기시간. INFINITE == 0xffffffff == 사실상 무한대.
			//byte에 양수가 전달되었다면 스레드에게 대기 상태로 무한정 기다리게 한다.
		);

		ThreadWorkType workType = static_cast<ThreadWorkType>(byte);

		switch (workType)
		{
		case ThreadWorkType::UserWork:
		{
			GameEngineThreadCallbackJob* job = reinterpret_cast<GameEngineThreadCallbackJob*>(completionKey);
			job->Process();
			delete job;
			break;
		}
		case ThreadWorkType::Destroy:
			++_threadPool->destroyedThreadCount_;
			return;


		default:
			MsgBoxAssert("알 수 없는 콜백잡 유형입니다.");
			break;
		}
	}
}