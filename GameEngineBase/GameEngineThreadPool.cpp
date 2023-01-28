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

void GameEngineThreadPool::Initialize(const std::string_view& _threadName, int _threadCount /*= 0*/)
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

		this->createdThreadCount_			//�� IOCP�� �۾���ų �� �ִ� �ִ� ������ ��.
		//0�� ������ �ڵ����� ���μ��� ���ڸ� �˾Ƴ��� �־��شٰ� �Ѵ�. 
		// ������ ���⼭�� allThreads_������ ũ�⸦ �����ؾ� �ϹǷ� 0�� ���� �ʰ� 
		// GetSystemInfo()�Լ��� ���� �˾Ƴ� ���μ��� ���ڸ� �־��ش�.
		//�̹� ������ IOCP�ڵ��� �־ �ι�° ���ڷ� �־���ٸ� �� ���� ���õȴ�.
	);

	if (nullptr == iocpHandle_)
	{
		MsgBoxAssert("IOCP �ڵ� ���� ����.");
		return;
	}

	isRunning_ = true;
	destroyedThreadCount_ = 0;
	this->allThreads_.reserve(this->createdThreadCount_);
	for (size_t i = 0; i < this->createdThreadCount_; ++i)
	{
		GameEngineThread* newThread = new GameEngineThread();
		allThreads_.push_back(newThread);

		newThread->SetName(_threadName.data() + std::to_string(i));
		newThread->Start(
			_threadName.data() + std::to_string(i),
			std::bind(ExecuteWork, this, newThread, iocpHandle_)
		);
	}
}

void GameEngineThreadPool::DistributeWork(std::function<void()> _callback)
{
	if (nullptr == _callback)
	{
		MsgBoxAssert("��ȿ���� ���� �Լ� �������Դϴ�.");
		return;
	}

	GameEngineThreadCallbackJob* newJob = new GameEngineThreadCallbackJob();

	newJob->work_ = _callback;

	if (false == PostQueuedCompletionStatus(		//������ IOCP�� IO�Ϸ� ť�� IO�Ϸ� ��Ŷ�� ������ �ִ� �Լ�.
		//���⿡ �־��� IO�Ϸ� ��Ŷ ������ ���� ������� �ϳ��� ������ IOCP�� ó���ϰ� �ȴ�.
		//Release Thread List�� �� �ڸ��� �ִٸ� IOCP�� ������ ������ �Ѱ��� ����� Release Thread List�� �ְ��ϴ� ��ɵ� �ִ�.

		iocpHandle_,	//���⿡ �־��� �ڵ�� ����� IOCP ��ü�� IO�Ϸ� ť�� IO�Ϸ� ��Ŷ ������ �ִ´�.

		static_cast<DWORD>(ThreadWorkType::UserWork),	//���ݱ��� ���޵� ���� ����Ʈ ũ�⸦ ���޹��� DWORD* ����.
		//�����δ� ������ ��ӵ� ������ �����ؼ� �� ������ �ش��ϴ� ThreadWorkType ���������� ��ȯ,
		// � ������ �۾����� �� �� �ְ� �Ѵ�.

		reinterpret_cast<ULONG_PTR>(newJob),	//IOCP ��ü�� �����忡�� ����� �Լ��� �Լ� ������.
		//

		nullptr			//Overlapped IO�۾��� �����ؾ� �ϴ� OVERLAPPED ����ü�� ����������.
		//������ IOCP�� ť�� ���� IO�Ϸ���Ŷ ������ � IO�۾��� �ϷḦ �˸��� ��Ŷ�� �������� �Ǵ��ϴ� �ĺ��� ������ ������,
		//�����常 ����Ҷ��� �ǹ̾��� �����̹Ƿ� nullptr�� ��� ���� ���̴�.
	))
	{
		MsgBoxAssert("�����忡�� �ݹ����� �����ϴµ� �����߽��ϴ�.");
		return;
	}
}

void GameEngineThreadPool::ExecuteWork(GameEngineThreadPool* _threadPool, GameEngineThread* _thread, HANDLE _iocpHandle)
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
			//�� �Լ��� �ѹ��̶� ȣ���� �����带, ù��° ���ڷ� �־��� �ڵ��� IOCP��ü�� �����ϴ� ������Ǯ�� �ִ� ��ɵ� �ִ�.
			//������ �񵿱������� ��ø�Ǽ� ����Ǵ� IO�۾����� �������� �Ϸ� ���θ� IOCP���� �˸��� 
			// CompletionKey�� ���� ���޵� IO�۾� ���� �Լ�(Completion routine)�� �����͸�, 
			// ������� ������� �� �ϳ����� �����ϰ� ����ϴ°��� �� �Լ��� ���� ���������� 
			// ���⼭�� Completion routine�� ������� ������� �� �ϳ����� �����ϰ� ����ϴ� ��ɰ�
			// ����� �۾��� ���ٸ� �����带 �Ͻ����� ���·� ����� ��ɸ� ����Ѵ�.
			//������ Ǯ�� ��� ��������� �ݺ������� �� �Լ��� ȣ���ϰ� �ؾ� IOCP�� ��������� ����� ������ �� �ִ�.

			_iocpHandle, 		  //�� �����带 �����ϰ� �� IOCP ��ü�� �ڵ�.

			&byte,				  //���ݱ��� ���޵� ���� ����Ʈ ũ�⸦ ���޹��� DWORD* ����.
			//�����δ� ������ ��ӵ� ������ ���޹޾Ƽ� �� ������ �ش��ϴ� ThreadWorkType ���������� ��ȯ,
			// � ������ �۾����� �� �� �ְ� �Ѵ�.

			&completionKey,		  //CreateIoCompletionPort()�Լ����� ���� �ڵ鿡 �ٿ��� ���ø��� Ű.
			//IO�۾��� �Ϸ�Ǹ� �� Ű�� ��ϵ� �Լ������Ͱ� IOCP�� ���� ������ �����忡�� ��еǾ� ȣ��ȴ�. 
			//�� �Լ��� ������ �Ϸ� ��ƾ(Completion Routine)�̶�� �Ѵ�.

			&lpOverlapped,		  //Overlapped IO�۾��� ���޹޾ƾ� �ϴ� OVERLAPPED ����ü�� ����������.
			//������ IOCP�� ť�� ���� IO�Ϸ���Ŷ�� � IO�۾��� �ϷḦ �˸��� ��Ŷ���� �Ǵ��ϴ� �ĺ��� ������ ������,
			//�����常 ����Ҷ��� �ǹ̾��� �����̹Ƿ� nullptr�� ��� ������ ���̴�.

			INFINITE	//�ִ� ���ð�. 
			//�� �ð����� IOCP�� �� �Լ��� ȣ���� �����忡�� ����� IO�Ϸ� ��Ŷ�� ���� ������ �Լ��� ��ȯ�� �̷�� ����ϰ� �Ѵ�.
			//�� �ð��� �� ���������� �� �Ϸ� ��Ŷ�� ������ �ʴ´ٸ� ������� �ð��ʰ�(TimeOut)�Ǿ� �ϴ��� ���� ������ �ѹ� ����.
			// ������ ���⼭�� ��� �ð��� INFINITE == 0xffffffff == ��ǻ� ���Ѵ�� ���������Ƿ� 
			// �۾��� ��ģ �����忡�� ���� IO�Ϸ� ��Ŷ == �� �۾��� ���� ������ Waiting Thread List���� ������ ��ٸ��� �Ѵ�.
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
			//MsgBoxAssert("�� �� ���� �ݹ��� �����Դϴ�.");
			break;
		}
	}
}