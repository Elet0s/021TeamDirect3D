#pragma once

class GameEngineAnimation
{
	//이 클래스의 존재 이유: 지정한 시간간격마다 인덱스 변화.
public:
	GameEngineAnimation();
	~GameEngineAnimation();

protected:
	GameEngineAnimation(const GameEngineAnimation& _other) = delete;
	GameEngineAnimation(GameEngineAnimation&& _other) noexcept = delete;

private:
	GameEngineAnimation& operator=(const GameEngineAnimation& _other) = delete;
	GameEngineAnimation& operator=(const GameEngineAnimation&& _other) = delete;


public:	
	void Initialize(int _startIndex, int _endIndex, float _interval, bool _isLoop = true);
	void Update(float _deltaTime);
	void Reset();

public:
	int GetCurrentIndex() const
	{
		return curFrameIndex_;
	}

private:
	int startIndex_;	//시작 인덱스.
	int curFrameIndex_;	//현재 프레임 인덱스.
	int endIndex_;		//종료 인덱스.

	float curframeTime_;//현재프레임 지난 시간.
	float interval_;	//프레임간 시간간격.
	float playTime_;	//여태까지 애니메이션이 재생된 시간.

	bool isLoop_;		//true == 애니메이션 무한반복. false == 1회반복 후 마지막프레임에서 정지.

	bool hasStarted_;	//true: 애니메이션 시작함. false: 아직 애니메이션 시작하지 않음. 
	bool hasEnded_;		//true: 애니메이션 종료함. false: 아직 애니메이션 종료하지 않음.
	bool isPaused_;	//true: 일시정지.


	//template<typename AnimationData>
	//std::vector<AnimationData> animationDataVector_;

	//std::function<void(const FrameAnimation_Desc&)> start_;		//애니메이션 재생 시작시 호출되는 함수들.
	//std::function<void(const FrameAnimation_Desc&)> frame_;		//애니메이션 재생중 매 프레임마다 호출되는 함수들.
	//std::function<void(const FrameAnimation_Desc&, float)> time_;	//애니메이션 재생중 일정 시간 후에 호출되는 함수들.
	//std::function<void(const FrameAnimation_Desc&)> end_;			//애니메이션 재생 종료시 호출되는 함수들.

};

