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
	//�̹� ������ ���۽ð��� time_point������ �����Ѵ�.

	std::chrono::duration<double> time_span = 
		std::chrono::duration_cast<std::chrono::duration<double>>(current - prev_);
	//�̹� ������ ���۽ð� - ���� ������ ���۽ð� = ���� ������ �����ϴµ� �ɸ� �ð� == ��ŸŸ��.
	//��ŸŸ���� duration<double>���·� �����Ѵ�.

	//std::chrono::duration<Rep, Period = std::ratio<1>>: Ư�� ������ �ð� ������ �� ƽ����, 
	// Rep�� �־��� �������� �����ϴ� Ŭ����.
	//ƽ�� ������ Period / 1�� �����̰�, ���ø� �Ű����� Period�� �ƹ� ���� �־����� ������ �⺻���� std::ratio<1>�� �ԷµǾ� �ʴ� 1ƽ���� �����ȴ�. 

	//std::ratio<Num, Denom = 1>: Num / Denom�� ���·� �Է¹��� �м��� ������ ǥ��, ����ϴ� Ŭ����. 
	
	deltaTimeD_ = time_span.count(); 
	//std::chrono::duration::count(): duration<double>���·� ����� ��ŸŸ���� �� ƽ���� ����Ѵ�. 
	// durationŬ���� �������� �ι�° ���ø� �Ű����� Period�� �ƹ� ���� �־����� �ʾ����Ƿ� �ʴ� 1ƽ���� ���ȴ�.
	//std::chrono::duration<Rep, Period>::count(): duration������ ������ ����� �ð��� �� ƽ���� ��ȯ�ϴ� �Լ�.  

	deltaTimeF_ = static_cast<float>(deltaTimeD_);

	prev_ = current;



	fpsCheckTime_ -= deltaTimeD_;

	if (-1 == frameLimit_)	//������ ������ �� ������ ���ٴ� �ǹ�.
	{
		isUpdateOn_ = true;

		if (DBL_EPSILON <= deltaTimeD_)	//��ŸŸ���� �ص��� ���� ���̶�� ����.
		{
			++frameCount_;
			totalFPS_ += static_cast<int>(1.0 / deltaTimeD_);

			if (0 >= fpsCheckTime_)	//1�ʰ� ��� ������ �� ���.
			{
				averageFPS_ = totalFPS_ / frameCount_;		//�ʴ� ��� ������ �� ����.

				fpsCheckTime_ = 1.0;	//���� FPS���� ���� 1�ʷ� ����.
				frameCount_ = 0;
				totalFPS_ = 0;
			}
		}
	}
	else 		
	{
		if (DBL_EPSILON <= deltaTimeD_)	//��ŸŸ���� �ص��� ���� ���̶�� ����.
		{
			curFrameTime_ -= deltaTimeD_;
			sumDeltaTimeF_ += deltaTimeF_;

			if (0.f >= curFrameTime_)
			{
				isUpdateOn_ = true;
				++frameCount_;

				sumDeltaTimeF_ = static_cast<float>(frameInterval_ - curFrameTime_);
				curFrameTime_ = frameInterval_;

				if (0 >= fpsCheckTime_)	//1�ʰ� ��� ������ �� ���.
				{
					averageFPS_ = frameCount_;		//�ʴ� ��� ������ �� ����.
					fpsCheckTime_ = 1.0;	//���� FPS���� ���� 1�ʷ� ����.
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
