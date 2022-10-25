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
		//�� Ŭ������ ���� ����:
	public:
		virtual void Process() = 0;
	};

	class GameEngineThreadCallbackJob : public GameEngineThreadJob
	{
		//�� Ŭ������ ���� ����:
		//ThreadJob�� ThreadCallbackJob�� ���� �����ϴ� ������??

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



	//�� Ŭ������ ���� ����: IOCP ��ü�� ������ Ǯ�� �̿��ؼ� ��������� �����ϰ� �־��� �۾��� �����ϰ� ����Ѵ�.


	//������Ʈ Ǯ(object pool): ������Ʈ�� �ش��ϴ� ���𰡸� �̸� �뷮���� �����ؼ� Ǯ(pool)�� ������ �ξ��ٰ� 
	// �ʿ��ϸ� ���� ����, �ʿ� �������� �������� �ʰ� �ٽ� Ǯ�� �������� ������ �ݺ��ϴ� ������ ���Ѵ�.
	//C++ ���� �� ���� �ð��� ���� �ʿ��� new�� delete ������ �󵵸� ���� �� �ִٴ� ������,
	// �뷮�� �޸𸮸� �ʿ�� �Ѵٴ� ������ �ִ�. 

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
	//������Ǯ �ʱ�ȭ �Լ�. _threadCount�� �⺻���� 0�̶�� ���ο��� �ڵ����� ������ ������ ������ ���Ѵ�.
	void Initialize(const std::string& _threadName, int _threadCount = 0);
	//�ھ� �� * 2�� ��Ƽ�������� ������ ������ ������� �Ѵ�. 

	void Work(std::function<void()> _callback);

private:
	//
	static void	ThreadPoolFunction(
		GameEngineThreadPool* _threadPool,
		GameEngineThread* _thread,
		HANDLE _iocpHandle
	);


private:
	HANDLE iocpHandle_;		//IOCP ��ü�� ����� �ڵ�. �� Ŭ������ �ٽ�. ������Ǯ�� �� �ڵ�� ����� IOCP ��ü�� �����Ѵ�.
	//IOCP(Input/Output Completion Port: ����� �Ϸ� ��Ʈ): ��������� ���Ǵ� ��Ƽ������ �� IO�۾� ��� ���� �� ���ŷ ���μ���.
	// ���������� IO �𵨵� �� �ְ����̶�� �Ѵ�. 
	//��� IO�۾��� �Ϸ�Ǹ� IO �Ϸ� ��Ŷ(Compleltion Packet)�� ������ IO�Ϸ� ť(Completion Queue)�� ���δ�. 
	// Ȥ�� PostQueuedCompletionStatus()�Լ��� ���� ���� �־��� ���� �ִ�. GetQueuedCompletionStatus()�Լ��� ȣ��Ǹ� �� ť�� ���� ��Ŷ ������ �� 
	// ���� ���� �׿��ִ� ���� �̾Ƽ� �Ϸ� Ű�� ����� �Լ��� ������ ������� ������� �� �ϳ����� ����Ͽ� ó���ϰ� �Ѵ�.
	//�� �����ӿ�ũ���� IOCP�� ������ ���� �� �۾� ��� ��ɸ� ����Ѵ�.

	//Waiting Thread Queue(��� ������ ť):
	//������Ǯ�� Ǯ�� �Ǵ� �����̳�.

	//Release Thread List(��� ����(?) ������ ����Ʈ): �۾� ó�� ���� ��������� ID�� ���⿡ ��ϵȴ�.
	//CreateIoCompletionPort()�Լ����� ���������� �־��� ���� �� ť�� ũ�Ⱑ �ȴ�.

	//Pause Thread List(�Ͻ����� ������ ����Ʈ):
	//���⿡ ������ ID�� ���� ���� �����尡 Alertable Wait ���°� �Ǿ��ٰ� �ϴ� �� ����.


	//IO(Input Output)�۾�: ���μ��� �ܺο� �ִ� Ư���� �޸𸮸� �о���̰ų� �����ϴ� �۾�. �밳�� ���� ������� ���Ѵ�.
	//���ŷ(Blocking): �� �۾��� ���������� �ٸ� �۾��� ������� �ʴ� ��.
	//�� ���ŷ(Non Blocking): �� �۾��� �� �۾����, �� �۾��� �� �۾���� ����Ǹ鼭 ������ ������ ����(Block)���� �ʴ� ��.
	//����(Synchronous): �۾� ���ø� �ϴ� ��ü��, �۾� ���ø� �޴� ��ü�� �۾� ���Ḧ ��ٷȴٰ� ���� �۾��� �����ϴ°�.
	//�񵿱�(Asynchronous): �۾� ���ø� �ϴ� ��ü��, �۾� ���ø� �޴� ��ü�� �۾� ���Ḧ �Ű澲�� �ʰ� ���� �۾��� �����ϴ� ��.


	//���� + ���ŷ: �̱۽�����.
	//���� + �� ���ŷ: 
	//�񵿱� + ���ŷ: ????
	//�񵿱� + �� ���ŷ: ��Ƽ�½�ŷ.



	int createdThreadCount_;		//������ ������ ����.
	std::atomic<bool> isRunning_;	//
	std::atomic<int> destroyedThreadCount_;	//�ı��� ������ ����.

	//std::atomic<T>: ���ڼ�
	//������鳢�� ���� ħ���� �� �ִ� �Ϲ� ������ �ƴ�, ����ó�� �ɰ��� ���� ������ �����ϰ� �Ѵٰ� �ؼ� atomic.

	std::vector<GameEngineThread*> allThreads_;	//������ ��� GameEngineThread ��ü��.
};

