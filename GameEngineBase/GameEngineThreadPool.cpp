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
			MsgBoxAssert("�����忡�� �ݹ����� �����ϴµ� �����߽��ϴ�.");
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
		GetSystemInfo(&info);	//OS���� �ý��� ������ ������ �Լ�.
		createdThreadCount_ = info.dwNumberOfProcessors;	// ������ ������ ���� �� �ý����� ���μ��� ������ ���Ѵ�.
	}

	this->iocpHandle_ = CreateIoCompletionPort(	//IOCP ��ü�� �����ϰ� �ű⿡ ����� �ڵ��� �ִ� �Լ�.
		//���� �ڵ��� NULL�� �ƴ϶�� �־��� ���� �ڵ鿡 ������ IOCP �ڵ��� �����ؼ� ��ȯ�ϱ⵵ �Ѵ�.
		//���� �ڵ�� ���� IOCP�ڵ��� �־��شٸ� IOCP �ڵ鿡 ���� �ڵ��� ��Ͻ����ִ� �۾��� �ϴ� �Լ��̱⵵ �ϴ�.

		INVALID_HANDLE_VALUE,		//���� �ڵ�. ������ ���� �����ϸ� INVALID_HANDLE_VALUE�� �ִ´�.
		//MSDN�� ���ϸ� �̰� �ܼ��� ���� �ڵ鸸�� ����Ű�°��� �ƴ϶� 
		// ��Ʈ��ũ ��������Ʈ, TCP ����, ���ӵ� ������ ���� �� ���� ���԰� ���� overlapped I/O�� �����ϴ� 
		// ��� �ý��� ��ü���� �ڵ���� ��� �����ϴ� �����̶�� �Ѵ�.
		//IOCP �ڵ�� �����ؾ��ϴ� ���� �ڵ��� �ְ� �� �Լ��� ��� ȣ���ؼ� 
		// �Ѱ��� IOCP �ڵ鿡 ���� ���� �ڵ���� ��Ͻ�Ű�°��� �� �Լ��� ���� �� �Ѱ���� �Ѵ�.

		NULL,						//���� IOCP�ڵ�. ���� �����Ѵٸ� NULL�� �ִ´�.

		NULL,						//���� �ڵ鿡 ����� �Ϸ� Ű(Completion Key). ����� �Է� ������.
		//8����Ʈ ������ �����̹Ƿ� ���⿡ �����忡�� �����ų �Լ��� �����͸� �־� ������ �� �ִ�. 
		// �� �Լ��� �Ϸ� ��ƾ(Completion Routine)�̶�� �Ѵ�. �Ϸ� ��ƾ�� ����� Ű���̶� �Ϸ� Ű��� �ϴ°��ϼ��� �ִ�.
		//������ IOCP �ڵ� ������ �� �� ���̹Ƿ� NULL�� �ִ´�. 

		this->createdThreadCount_			//�� IOCP ��ü�� �����ϰ� �� �ִ� ������ ��.
		//0�� ������ �ڵ����� ���μ��� ���ڸ� �˾Ƴ��� �־��شٰ� �Ѵ�.
	);

	if (nullptr == iocpHandle_)
	{
		MsgBoxAssert("IOCP �ڵ� ���� ����.");
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
		MsgBoxAssert("��ȿ���� ���� �Լ� �������Դϴ�.");
		return;
	}

	GameEngineThreadCallbackJob* newJob = new GameEngineThreadCallbackJob();

	newJob->work_ = _callback;

	//�־��� �ڵ�� ����� IOCP ��ü����, ������ �ϳ��� ������ ULONG_PTR ���·� ��ȯ�� �Լ������͸� ������ �����尡 �����ϰ� �Ѵ�.

	if (false == PostQueuedCompletionStatus(		//������ IOCP��ü�� IO�Ϸ� ť�� IO�Ϸ� ��Ŷ�� �̺�Ʈ�� �ִ� �Լ�.
		//���⿡ �־��� IO�Ϸ� ��Ŷ �̺�Ʈ�� GetQueuedCompletionStatus()�Լ��� ȣ��ɶ����� ���� ������� �ϳ��� ������ IOCP ��ü�� ó���ϰ� �ȴ�.
		//

		iocpHandle_,	//���⿡ �־��� �ڵ�� ����� IOCP ��ü�� IO�Ϸ� ť�� IO�Ϸ� ��Ŷ�� �ִ´�.

		static_cast<DWORD>(ThreadWorkType::UserWork),	//���ݱ��� ���޵� ���� ����Ʈ ũ�⸦ ���޹��� DWORD* ����.
		//�����δ� ������ ��ӵ� ������ �����ؼ� �� ������ �ش��ϴ� ThreadWorkType ���������� ��ȯ,
		// � ������ �۾����� �� �� �ְ� �Ѵ�.

		reinterpret_cast<ULONG_PTR>(newJob),	//IOCP ��ü�� �����忡�� ����� �Լ��� �Լ� ������.

		nullptr			//Overlapped IO�۾��� �����ؾ� �ϴ� OVERLAPPED ����ü�� ����������.
		//������ IOCP�� ť�� ���� IO�Ϸ���Ŷ ������ � IO�۾��� �ϷḦ �˸��� ��Ŷ�� �������� �Ǵ��ϴ� �ĺ��� ������ ������,
		//�����常 ����Ҷ��� �ǹ̾��� �����̹Ƿ� nullptr�� ��� ���� ���̴�.
	))
	{
		MsgBoxAssert("�����忡�� �ݹ����� �����ϴµ� �����߽��ϴ�.");
		return;
	}


}

void GameEngineThreadPool::ThreadPoolFunction(GameEngineThreadPool* _threadPool, GameEngineThread* _thread, HANDLE _iocpHandle)
{
	DWORD byte = 0;		//���ݱ��� ���޵� ���� ����Ʈ ũ��. �����δ� �����忡�� �����ų �۾��� ����.

	//IOCP ��ü�� ���� �����忡�� ������ �Լ�������. 
	ULONG_PTR completionKey = NULL;
	//IO�۾��� ������ ������� �����忡�� �����ų �Լ��� �Ϸ� ��ƾ(Completion Routine)�̶�� �ϴ� ��,
	// �� �Լ��� �����Ͷ� Completion Key�ΰ� ����.

	LPOVERLAPPED lpOverlapped = NULL;	//Overlapped IO�۾��� �ʿ��� OVERLAPPED ����ü�� ������. �����δ� ������� ����.


	while (_threadPool->isRunning_)
	{
		GetQueuedCompletionStatus(	//IOCP ��ü���� IO�Ϸ� ť���� IO �Ϸ���Ŷ(Completion Packet)�� ���� �ϳ��� �������� �ϴ� �Լ�.
			// GQCS()��� ���ڷε� ���°� ����.
			//������ �񵿱������� ��ø�Ǽ� ����Ǵ� IO�۾����� �������� �Ϸ� ���θ� PostQueuedCompletionStatus()�Լ��� ���� 
			// IOCP ��ü���� �˸��� CompletionKey�� ���� ���޵� �Լ�(Completion routine)�� �����͸�, 
			// ������� ������� �� �ϳ����� �����ϰ� ����ϰ� �ϴ°��� �� �Լ��� ���������� 
			// ���⼭�� Completion routine�� ������� ������� �� �ϳ����� �����ϰ� ����ϴ� ��ɸ� ����Ѵ�.
			//� �����忡�� Completion routine�� ��е� ���� �� �� ����.

			_iocpHandle, 		  //IOCP �ڵ�.

			&byte,				  //���ݱ��� ���޵� ���� ����Ʈ ũ�⸦ ���޹��� DWORD* ����.
			//�����δ� ������ ��ӵ� ������ ���޹޾Ƽ� �� ������ �ش��ϴ� ThreadWorkType ���������� ��ȯ,
			// � ������ �۾����� �� �� �ְ� �Ѵ�.

			&completionKey,		  //CreateIoCompletionPort()�Լ����� ���� �ڵ鿡 �ٿ��� ���ø��� Ű.
			//IO�۾��� �Ϸ�Ǹ� �� Ű�� ��ϵ� �Լ������Ͱ� OS�� ���� ���(Alertable wait)���� �ƹ� �����忡�� ��еǾ� ȣ��ȴ�. 
			//�� �Լ��� ������ Completion Routine�̶�� �Ѵ�.

			&lpOverlapped,		  //Overlapped IO�۾��� ���޹޾ƾ� �ϴ� OVERLAPPED ����ü�� ����������.
			//������ IOCP�� ť�� ���� IO�Ϸ���Ŷ�� � IO�۾��� �ϷḦ �˸��� ��Ŷ���� �Ǵ��ϴ� �ĺ��� ������ ������,
			//�����常 ����Ҷ��� �ǹ̾��� �����̹Ƿ� nullptr�� ��� ������ ���̴�.

			INFINITE			  //�ִ� ���ð�. INFINITE == 0xffffffff == ��ǻ� ���Ѵ�.
			//byte�� ����� ���޵Ǿ��ٸ� �����忡�� ��� ���·� ������ ��ٸ��� �Ѵ�.
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
			MsgBoxAssert("�� �� ���� �ݹ��� �����Դϴ�.");
			break;
		}
	}
}