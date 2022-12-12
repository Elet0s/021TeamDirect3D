#include "PreCompile.h"
#include "GameEngineAnimation.h"

GameEngineAnimation::GameEngineAnimation()
	: startIndex_(-1),
	curFrameIndex_(-1),
	endIndex_(-1),
	curframeTime_(-1.f),
	interval_(-1.f),
	playTime_(-1.f),
	isLoop_(false),
	hasStarted_(false),
	hasEnded_(false),
	isPaused_(false)
{
}

GameEngineAnimation::~GameEngineAnimation()
{
}

void GameEngineAnimation::Initialize(int _startIndex, int _endIndex, float _interval, bool _isLoop /*= true*/)
{
	startIndex_ = _startIndex;
	curFrameIndex_ = _startIndex;
	endIndex_ = _endIndex;
	interval_ = _interval;
	isLoop_ = _isLoop;
}

void GameEngineAnimation::Update(float _deltaTime)
{
	if (false == isPaused_)
	{
		curframeTime_ += _deltaTime;
		playTime_ += _deltaTime;

		//if (nullptr != time_)
		//{
		//	this->time_(info_, _deltaTime);
		//}

		if (false == hasStarted_ && curFrameIndex_ == 0)
		{
			//if (nullptr != start_)
			//{
			//	this->start_(info_);
			//}

			hasStarted_ = true;
			hasEnded_ = false;
		}

		if (interval_ <= curframeTime_)
		{
			if (curFrameIndex_ == endIndex_ && false == hasEnded_)
			{
				//if (nullptr != end_)
				//{
				//	end_(info_);
				//}
				hasStarted_ = false;
				hasEnded_ = true;
				return;
			}

			++curFrameIndex_;
			//if (nullptr != frame_)
			//{
			//	frame_(info_);
			//}

			if (curFrameIndex_ >= endIndex_ + 1)
			{
				if (true == isLoop_)
				{
					curFrameIndex_ = 0;
				}
				else
				{
					curFrameIndex_ = endIndex_;
				}
			}
			curframeTime_ -= interval_;
		}
	}
}

void GameEngineAnimation::Reset()
{
	curframeTime_ = 0.f;
	curFrameIndex_ = 0;
	playTime_ = 0.f;
}
