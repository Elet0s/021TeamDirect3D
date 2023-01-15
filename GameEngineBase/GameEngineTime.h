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
	void Reset();			//시간 측정 준비 함수.
	void Update();			//델타타임 갱신 함수.

public:
	static inline GameEngineTime& GetInst()
	{
		return *inst_;
	}

	static void Destroy()
	{
		//값형으로 안 하고 포인터 형식으로 싱글턴을 만드는 이유: 제거 시점을 내 마음대로 통제하기 위해서.
		//싱글톤 삭제'만' 원하는 타이밍에 한다.
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
			//프레임 제한이 없는 상황에서 globalTimeScale_이 곱해진 델타타임 반환.
		}

		return sumDeltaTimeF_ * globalTimeScale_;
		//프레임 제한이 있는 상황에서 globalTimeScale_이 곱해진 누적 델타타임 반환.
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

	//프레임 제한을 설정하는 함수. -1은 제한하지 않겠다는 의미.
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

	std::chrono::steady_clock::time_point prev_;	//이전 루프 시작 시간.
	//std::chrono::time_point: epoch라고 사전에 정해놓은, 특정 시점으로부터 
	// 사용자가 지정한 시점간의 시간 간격이 얼마나 되는지를 duration이라는 클래스로 표현하고 계산하는 클래스.

	//std::chrono::system_clock의 경우에는 유닉스 타임이라고 부르는 그레고리력 1970년 1월 1일 00시 00분 00초가 
	// epoch이며, 시스템 시간 설정에 따라서 시간이 역행해서 duration이 음수가 될 수도 있다.
	//std::chrono::steady_clock의 경우에는 시스템 부팅 시점이 epoch가 되며, 
	// 단방향(monotonic)으로만 시간이 흘러가므로 절대 역행하지 않고, duration이 음수가 나올 수도 없다.

	double deltaTimeD_;				//델타타임: 지난 루프를 한번 수행 할 때 걸린 시간.
	float deltaTimeF_;				//델타타임: 지난 루프를 한번 수행 할 때 걸린 시간.
	//컴퓨터의 성능이 좋을수록 델타타임 값이 작아지므로, 컴퓨터 성능 격차로 인해 각자 다른 속도로 루프를 수행한다고 해도 
	//성능에 반비례해서 델타타임 값이 작게 잡히고, 그로 인해 컴퓨터 성능 상관없이 같은 시간 같은 게임 진행속도를 보여주게 된다.

	std::map<int, float> timeScale_;

	float globalTimeScale_;		//게임 전체 속도 조정용 배수.

	int averageFPS_;					//초당 평균 프레임 갱신 횟수.
	float sumDeltaTimeF_;	//프레임 제한이 있을때 사용되는 프레임간 누적 델타타임.
	double fpsCheckTime_;	//외부 영향을 받지 않는 정확한 FPS 측정용 시간계산 변수.
	double curFrameTime_;	//현재 남은 다음 프레임 갱신 주기.
	double frameInterval_;	//프레임 제한이 걸렸을 때 적용되는 프레임간 간격. 
	int frameCount_;				//1초간 수행한 전체 루프 수.
	int totalFPS_;			//1초간 집계된 FPS의 총합.

	bool isUpdateOn_;		//프레임 제한 중인가 여부. true면 제한을 걸지 않는다.
	int frameLimit_;			//초당 프레임 제한 기준. -1이면 제한하지 않음.
};

