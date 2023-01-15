#pragma once

class GameEngineTime
{

	static GameEngineTime* inst_;
private:

	GameEngineTime();
	~GameEngineTime();

	GameEngineTime(const GameEngineTime& _other) = delete;
	GameEngineTime(GameEngineTime&& _other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _other) = delete;


public:
	void Reset();			//�ð� ���� �غ� �Լ�.
	void Update();			//��ŸŸ�� ���� �Լ�.

public:
	static inline GameEngineTime& GetInst()
	{
		return *inst_;
	}

	static void Destroy()
	{
		//�������� �� �ϰ� ������ �������� �̱����� ����� ����: ���� ������ �� ������� �����ϱ� ���ؼ�.
		//�̱��� ����'��' ���ϴ� Ÿ�ֿ̹� �Ѵ�.
		if (nullptr != inst_)
		{
			delete inst_;
			inst_ = nullptr;
		}

	}

	inline float GetDeltaTime()
	{
		if (0.05f <= deltaTimeF_)
		{
			deltaTimeF_ = 0.05f;
		}

		if (-1 == frameLimit_)
		{
			return deltaTimeF_ * globalTimeScale_;
			//������ ������ ���� ��Ȳ���� globalTimeScale_�� ������ ��ŸŸ�� ��ȯ.
		}

		return sumDeltaTimeF_ * globalTimeScale_;
		//������ ������ �ִ� ��Ȳ���� globalTimeScale_�� ������ ���� ��ŸŸ�� ��ȯ.
	}

	inline float GetDeltaTime(int _index)
	{
		return deltaTimeF_ * GetTimeScale(_index);
	}
	template <typename EnumType>
	void GetDeltaTime(EnumType _type)
	{
		return GetDeltaTime(static_cast<int>(_type));
	}



	inline void SetTimeScale(int _index, float _timeScale)
	{
		timeScale_[_index] = _timeScale;
	}
	template <typename EnumType>
	void inline SetTimeScale(EnumType _type, float _timeScale)
	{
		SetTimeScale(static_cast<int>(_type), _timeScale);
	}

	inline float GetTimeScale(int _index)
	{
		if (timeScale_.end() == timeScale_.find(_index))
		{
			timeScale_[_index] = 1.00f;
		}

		return timeScale_[_index];
	}

	inline void SetGlobalTimeScale(float _globalTimeScale)
	{
		globalTimeScale_ = _globalTimeScale;
	}

	//������ ������ �����ϴ� �Լ�. -1�� �������� �ʰڴٴ� �ǹ�.
	inline void SetFrameLimit(int _frameLimit)
	{
		frameLimit_ = _frameLimit;

		if (-1 != frameLimit_)
		{
			frameInterval_ = 1.0 / static_cast<double>(frameLimit_);
			curFrameTime_ = frameInterval_;
		}
	}

	static inline int GetFPS()
	{
		return inst_->averageFPS_;
	}

	static inline bool IsUpdateOn()
	{
		return inst_->isUpdateOn_;
	}

private:

	std::chrono::steady_clock::time_point prev_;	//���� ���� ���� �ð�.
	//std::chrono::time_point: epoch��� ������ ���س���, Ư�� �������κ��� 
	// ����ڰ� ������ �������� �ð� ������ �󸶳� �Ǵ����� duration�̶�� Ŭ������ ǥ���ϰ� ����ϴ� Ŭ����.

	//std::chrono::system_clock�� ��쿡�� ���н� Ÿ���̶�� �θ��� �׷����� 1970�� 1�� 1�� 00�� 00�� 00�ʰ� 
	// epoch�̸�, �ý��� �ð� ������ ���� �ð��� �����ؼ� duration�� ������ �� ���� �ִ�.
	//std::chrono::steady_clock�� ��쿡�� �ý��� ���� ������ epoch�� �Ǹ�, 
	// �ܹ���(monotonic)���θ� �ð��� �귯���Ƿ� ���� �������� �ʰ�, duration�� ������ ���� ���� ����.

	double deltaTimeD_;				//��ŸŸ��: ���� ������ �ѹ� ���� �� �� �ɸ� �ð�.
	float deltaTimeF_;				//��ŸŸ��: ���� ������ �ѹ� ���� �� �� �ɸ� �ð�.
	//��ǻ���� ������ �������� ��ŸŸ�� ���� �۾����Ƿ�, ��ǻ�� ���� ������ ���� ���� �ٸ� �ӵ��� ������ �����Ѵٰ� �ص� 
	//���ɿ� �ݺ���ؼ� ��ŸŸ�� ���� �۰� ������, �׷� ���� ��ǻ�� ���� ������� ���� �ð� ���� ���� ����ӵ��� �����ְ� �ȴ�.

	std::map<int, float> timeScale_;

	float globalTimeScale_;		//���� ��ü �ӵ� ������ ���.

	int averageFPS_;					//�ʴ� ��� ������ ���� Ƚ��.
	float sumDeltaTimeF_;	//������ ������ ������ ���Ǵ� �����Ӱ� ���� ��ŸŸ��.
	double fpsCheckTime_;	//�ܺ� ������ ���� �ʴ� ��Ȯ�� FPS ������ �ð���� ����.
	double curFrameTime_;	//���� ���� ���� ������ ���� �ֱ�.
	double frameInterval_;	//������ ������ �ɷ��� �� ����Ǵ� �����Ӱ� ����. 
	int frameCount_;				//1�ʰ� ������ ��ü ���� ��.
	int totalFPS_;			//1�ʰ� ����� FPS�� ����.

	bool isUpdateOn_;		//������ ���� ���ΰ� ����. true�� ������ ���� �ʴ´�.
	int frameLimit_;			//�ʴ� ������ ���� ����. -1�̸� �������� ����.
};

