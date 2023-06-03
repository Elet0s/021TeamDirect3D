#include "PreCompile.h"
#include "GameEngineTime.h"

GameEngineTime* GameEngineTime::inst_ = new GameEngineTime();

GameEngineTime::GameEngineTime()
	: deltaTimeD_(0.00),
	deltaTimeF_(0.00f),
	globalTimeScale_(1.f),
	averageFPS_(0),
	sumDeltaTimeF_(0.f),
	fpsCheckTime_(0.0),
	curFrameTime_(1.0),
	frameInterval_(0.0),
	frameCount_(0),
	totalFPS_(0),
	isUpdateOn_(true),
	frameLimit_(-1)
{
}

GameEngineTime::~GameEngineTime()
{
}

void GameEngineTime::Reset()
{
	prev_ = std::chrono::steady_clock::now();

	averageFPS_ = 0;
	fpsCheckTime_ = 1.0;
	totalFPS_ = 0;
	frameCount_ = 0;
	isUpdateOn_ = true;

	Update();
}

void GameEngineTime::Update()
{
	std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();
	//이번 루프의 시작시간을 time_point형으로 저장한다.

	std::chrono::duration<double> time_span = 
		std::chrono::duration_cast<std::chrono::duration<double>>(current - prev_);
	//이번 루프의 시작시간 - 지난 루프의 시작시간 = 지난 루프를 수행하는데 걸린 시간 == 델타타임.
	//델타타임을 duration<double>형태로 저장한다.

	//std::chrono::duration<Rep, Period = std::ratio<1>>: 특정 길이의 시간 간격이 몇 틱인지, 
	// Rep에 넣어준 형식으로 저장하는 클래스.
	//틱간 간격은 Period / 1초 간격이고, 템플릿 매개변수 Period에 아무 값도 넣어주지 않으면 기본값인 std::ratio<1>이 입력되어 초당 1틱으로 설정된다. 

	//std::ratio<Num, Denom = 1>: Num / Denom의 형태로 입력받은 분수나 비율을 표현, 계산하는 클래스. 

	deltaTimeD_ = time_span.count(); 
	//std::chrono::duration::count(): duration<double>형태로 저장된 델타타임이 몇 틱인지 계산한다. 
	// duration클래스 생성자의 두번째 템플릿 매개변수 Period에 아무 값도 넣어주지 않았으므로 초당 1틱으로 계산된다.
	//std::chrono::duration<Rep, Period>::count(): duration형식의 변수에 저장된 시간이 몇 틱인지 반환하는 함수.  

	deltaTimeF_ = static_cast<float>(deltaTimeD_);

	prev_ = current;



	fpsCheckTime_ -= deltaTimeD_;

	if (-1 == frameLimit_)	//프레임 제한을 할 생각이 없다는 의미.
	{
		isUpdateOn_ = true;

		if (DBL_EPSILON <= deltaTimeD_)	//델타타임이 극도로 작은 값이라면 무시.
		{
			++frameCount_;
			totalFPS_ += static_cast<int>(1.0 / deltaTimeD_);

			if (0 >= fpsCheckTime_)	//1초간 평균 프레임 수 계산.
			{
				averageFPS_ = totalFPS_ / frameCount_;		//초당 평균 프레임 수 갱신.

				fpsCheckTime_ = 1.0;	//남은 FPS갱신 간격 1초로 복구.
				frameCount_ = 0;
				totalFPS_ = 0;
			}
		}
	}
	else 		
	{
		if (DBL_EPSILON <= deltaTimeD_)	//델타타임이 극도로 작은 값이라면 무시.
		{
			curFrameTime_ -= deltaTimeD_;
			sumDeltaTimeF_ += deltaTimeF_;

			if (0.f >= curFrameTime_)
			{
				isUpdateOn_ = true;
				++frameCount_;

				sumDeltaTimeF_ = static_cast<float>(frameInterval_ - curFrameTime_);
				curFrameTime_ = frameInterval_;

				if (0 >= fpsCheckTime_)	//1초간 평균 프레임 수 계산.
				{
					averageFPS_ = frameCount_;		//초당 평균 프레임 수 갱신.
					fpsCheckTime_ = 1.0;	//남은 FPS갱신 간격 1초로 복구.
					frameCount_ = 0;
					totalFPS_ = 0;
				}
			}
			else
			{
				isUpdateOn_ = false;
			}
		}
	}
}
