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



	//�� Ŭ������ ���� ����: IOCP ��ü�� ���� ������ Ǯ�� �̿��ؼ� ��������� �����ϰ� �־��� �۾��� �����ϰ� ����ϴ� ��.

	//������Ʈ Ǯ(object pool): ������Ʈ�� �ش��ϴ� ���𰡸� �̸� �뷮���� �����ؼ� Ǯ(pool)�� ������ �ξ��ٰ� 
	// �ʿ��ϸ� ���� ����, �ʿ� �������� �������� �ʰ� �ٽ� Ǯ�� �������� ������ �ݺ��ϴ� ������ ���Ѵ�.
	//C++ ���� �� ���� ���� �ҿ䰡 ū new�� delete ������ �󵵸� ���� �� �ִٴ� ������,
	// �뷮�� �޸𸮸� �ʿ�� �Ѵٴ� ������ �ִ�. 
	
	//���׷����Ͼ(Heterogeneous: ����) ���:
	//�۾��� �������� �ɰ��� �ش� �۾� ���� �����忡�� �ñ�� ��Ÿ��.
	//���� �ʱ���� ��Ƽ������ ��Ȳ�� ���ο� �ξ��ٸ� �� ����� �� ���ٰ� �Ѵ�.
	
	//ȣ�����Ͼ(Homogenous: ����) ���:
	//�۾� ���� ������� ������ ������� ������� �����忡�� �ñ�� ��Ÿ��.
	//�̺�Ʈ�� �߻��ؾ� �۵��ϴ� ����̶� �̺�Ʈ �帮��(Event Driven), ������ �帮��(Data Driven) ����̶�� �Ѵ�.
	//�ַ� �������� ���.
	//�� �����ӿ�ũ���� �� ������� ��Ƽ������ ���.

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
	//������Ǯ �ʱ�ȭ �Լ�. _threadCount�� �⺻���� 0�̶�� IOCP ��ü�� �ڵ����� ������ ������ ������ ���Ѵ�.
	void Initialize(const std::string_view& _threadName, int _threadCount = 0);
	//�ھ� �� * 2�� ��Ƽ�������� ������ ������ ������� �Ѵ�. 

	//���ν����尡 ���� ������ �۾��ϴ� ���� �ƴ϶�, IO�Ϸ�ť�� �۾��� �й�, ��Ͻ�Ű�� �Լ�.
	//IO�Ϸ�ť�� ��ϵ� �۾� �Լ������ʹ� IOCP�� �޾Ƽ� �ڱⰡ ���� ������Ǯ �ȿ��� ���� ������ �����忡�� �ñ�� �ȴ�. 
	void DistributeWork(std::function<void()> _callback);

private:
	//���� �����尡 ���� ȣ���� �Լ��� �ƴ�, ������Ǯ�� ��ϵ� ��������� ������ ���ÿ� LinkFunction()�Լ��� ���� ȣ���ϰ� �� �Լ�. 
	//GameEngineThreadPool ��ü�� �ı��Ǳ� ������ ��� GetQueuedCompletionStatus()�Լ��� ȣ���ϴ� ������ �Ǿ� �����Ƿ�
	//IOCP�� GameEngineThread ��ü���� �ڱ� ������Ǯ�� �ְ� ������ �� �ְ� �ȴ�.
	static void	ExecuteWork(
		GameEngineThreadPool* _threadPool,
		GameEngineThread* _thread,
		HANDLE _iocpHandle
	);


private:
	HANDLE iocpHandle_;		//IOCP ��ü�� ����� �ڵ�. �� Ŭ������ �ٽ�. ������Ǯ�� �� �ڵ�� ����� IOCP ��ü�� �����Ѵ�.
	//Ư���� ���Ƶ����� �ʾ����� IOCP ��ü�� �����ϴ� ������Ǯ�� �Ѱ��� �� �� ���� Ȯ���ϹǷ� GameEngineThreadPool ��ü�� 
	//GameEngineCore���� ���� ��������� �Ѱ��� ������ �Ѵ�.
	//IOCP ��ü�� ���� ������ �� ����.

	//IOCP(Input/Output Completion Port: ����� �Ϸ� ��Ʈ): ��������� �����ϴ�
	// ������ ���� ���� Ŀ�� ������Ʈ(���μ����� �ƴ�, �ü�� ���ؿ��� ������ ���μ���, ������, ���� ���� ���ҽ� ������ ����ü).
	//�����峪 ���μ����� �����ϴ� ������Ʈ�� �ƴ϶� �ü���� ���� ���� �����ϴ� ������Ʈ�̹Ƿ� �����峪 ���μ����� ���¿� ���� ���� 
	// �ǽð����� ������Ǯ�� ������ �� �ִ�.

	//IOCP �۵� ����:
	//��� IO�۾��� �Ϸ�Ǹ� IO �Ϸ� ��Ŷ(Completion Packet)�� ����(���� ��Ŷ �ƴ�)�� IO�Ϸ� ť(Completion Queue)�� ���δ�. 
	// Ȥ�� PostQueuedCompletionStatus()�Լ��� ���� ���� �־��� ���� �ִ�. 
	//� ������ε� IO�Ϸ� ť�� IO �Ϸ� ��Ŷ ������ ���̸� IOCP�� ������Ǯ ���� ������ �� �ϳ��� ��� �����.
	//��� �����尡 GetQueuedCompletionStatus()�Լ��� ȣ���ϸ� �� ť�� ���� ��Ŷ ������ �� 
	// ���� ���� �׿��ִ� ���� �̾Ƽ� �Ϸ� Ű�� ����� �Լ��� ó���Ѵ�.


	//���ؽ�Ʈ ����Ī(Context Switching):
	//�� ������/���μ����� ���� CPU ��� ������ �ٸ� ������/���μ������� �Ѱ��ִ� �۾�. 
	//CPU ������ �Ѱ��ֱ� ���� ���� �������̴� �۾��� ������ �ٸ� ���� ������ �ξ�� �ϰ�, 
	//CPU ������ �Ѱܹޱ� ���� ������ �����ϰ��ִ� �۾� ������ �ٽ� �ҷ��;� �ϴµ� 
	//���ؽ�Ʈ ����Ī�� �ʹ� ���� �Ͼ�� �Ǹ� �۾��� �����ϴ°ͺ��� �۾� ������ �����ϰų� �ҷ����µ� 
	//�� ���� ������ �ϰ� �Ǵ� ��ȿ���� ����� �ȴ�. �׷��� ���ؽ�Ʈ ����Ī�� �ּ������θ� �Ͼ�� �Ѵ�.
	//�޸𸮸� �������� �ʴ� ���μ����� ���ؽ�Ʈ ����Ī���� �޸𸮸� ���� �κ� �����ϴ� �����尣 ���ؽ�Ʈ ����Ī�� �� �����ٰ� �Ѵ�.


	//IOCP�� ������ �����̳ʵ�.
	//Release Thread List(Ȱ��ȭ ������ ����Ʈ): ���� �۾� ���� ���� ��������� ID�� ����Ǵ� ����Ʈ.
	//CreateIoCompletionPort()�Լ����� ���������� �־��� ���� �� ����Ʈ�� ũ�Ⱑ �ȴ�. 
	// 
	//Pause Thread List(�Ͻ����� ������ ����Ʈ):
	//Release Thread List���� �۾��ϴ� �� Sleep()�Լ��� ȣ���ϰų� �ϴ� ���� ������ �Ͻ����� ���°� �� ��������� ID�� �����Ǵ� ����Ʈ.
	//�Ͻ����� ������ ��������� ���� ����Ʈ����, �Ͻ������� ����� Release Thread List�� �� �ڸ��� ���ٸ� ��� ���⿡�� ����Ѵ�.
	//  
	//Waiting Thread Queue(��� ������ ť):  
	// ������Ǯ�� ó�� ���� ������� Release Thread List�� ������ �� �Ϸ��ƾ�� ���� ������� GetQueuedCompletionStatus()�Լ���
	// ȣ���Ͽ����� IOCP�κ��� �۾��� ���� ���ϰ� ������� ��� ��������� ID�� ���⿡ ����. 
	//� �����ε� Release Thread List�� �� �ڸ��� ����µ� IO�Ϸ�ť�� �� �۾��� ������, 
	// IOCP�� ���⿡ �ִ� ������ �� �ϳ��� ���� Release Thread List�� �ְ� �۾��� ��Ų��.
	//�̸��� ť���� LIFO����̶� ���� ���������� �� ��������� �ٽ� ȣ��Ǵ� �����̴�.
	//�����带 �غ��Ű�� ���ؽ�Ʈ ����Ī�� ���� �ҿ��̹Ƿ�, 
	// �̹� �غ�Ǿ��־ ���ؽ�Ʈ ����Ī�� �ʿ���� Ȯ���� ���� ���� ������ ��������� �����ϱ� ���� ������� �Ѵ�.



	int createdThreadCount_;		//������ ������ ����.
	std::atomic<bool> isRunning_;	//true: ������Ǯ �۵���. 
	std::atomic<int> destroyedThreadCount_;	//�ı��� ������ ����.

	//std::atomic<T>: ���ڼ�
	//������鳢�� ���� ħ���� �� �ִ� �Ϲ� ������ �ƴ�, ����ó�� �ɰ��� ���� ������ �����ϰ� �Ѵٰ� �ؼ� atomic.

	std::vector<GameEngineThread*> allThreads_;	//IOCP�� �����ϰ� �� ��� GameEngineThread ��ü��.
};

