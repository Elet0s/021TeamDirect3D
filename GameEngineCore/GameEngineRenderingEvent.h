#pragma once

class GameEngineRenderingEvent
{
	//이 클래스의 존재 이유:
public:
	class GameEngineRenderer* parentRenderer_;	//이 애니메이션을 재생할 렌더러.
	//std::weak_ptr<class GameEngineRenderer> 로 바꿀 것.

	std::string resourceName_;

	std::vector<unsigned int> frames_;	//재생할 프레임 번호 순서.

	unsigned int curFrame_;	//현재 재생중인 프레임의 인덱스. 

	float curFrameTime_;	//현재프레임 지난 시간.

	float interval_;	//프레임간 시간간격.

	bool isLoop_;	//true == 애니메이션 무한반복. false == 1회반복 후 마지막프레임에서 정지.

	float playTime_;	//여태까지 애니메이션이 재생된 시간.

public:
	GameEngineRenderingEvent()
		: parentRenderer_(nullptr),
		isLoop_(false),
		interval_(0.1f),
		curFrame_(-1),
		curFrameTime_(0.0f),
		playTime_(0.f)
	{
	}

	GameEngineRenderingEvent(const std::string_view& _resourceName, unsigned int _start, unsigned int _end, float _interval, bool _isLoop = true)
		: parentRenderer_(nullptr),
		resourceName_(_resourceName),
		isLoop_(_isLoop),
		interval_(_interval),
		curFrame_(0),
		curFrameTime_(0.0f),
		playTime_(0.f)
	{
		frames_.reserve(static_cast<size_t>(_end - _start + 1));
		for (unsigned int i = _start; i <= _end; ++i)
		{
			frames_.push_back(i);
		}
	}

	GameEngineRenderingEvent(const std::string_view& _resourceName, const std::vector<unsigned int>& _frames, float _interval, bool _isLoop = true)
		: parentRenderer_(nullptr),
		resourceName_(_resourceName),
		isLoop_(_isLoop),
		interval_(_interval),
		frames_(_frames),
		curFrameTime_(0.0f),
		curFrame_(0),
		playTime_(0.f)
	{
	}


	GameEngineRenderingEvent(const std::string_view& _resourceName, float _interval, bool _isLoop = true)
		: parentRenderer_(nullptr),
		resourceName_(_resourceName),
		isLoop_(_isLoop),
		interval_(_interval),
		curFrame_(0),
		curFrameTime_(0.0f),
		playTime_(0.f)
	{
	}

};

