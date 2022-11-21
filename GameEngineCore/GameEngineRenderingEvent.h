#pragma once

class GameEngineRenderingEvent
{
	//�� Ŭ������ ���� ����:
public:
	class GameEngineRenderer* parentRenderer_;	//�� �ִϸ��̼��� ����� ������.
	//std::weak_ptr<class GameEngineRenderer> �� �ٲ� ��.

	std::string resourceName_;

	std::vector<unsigned int> frames_;	//����� ������ ��ȣ ����.

	unsigned int curFrame_;	//���� ������� �������� �ε���. 

	float curFrameTime_;	//���������� ���� �ð�.

	float interval_;	//�����Ӱ� �ð�����.

	bool isLoop_;	//true == �ִϸ��̼� ���ѹݺ�. false == 1ȸ�ݺ� �� �����������ӿ��� ����.

	float playTime_;	//���±��� �ִϸ��̼��� ����� �ð�.

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

