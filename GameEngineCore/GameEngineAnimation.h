#pragma once

class GameEngineAnimation
{
	//�� Ŭ������ ���� ����: ������ �ð����ݸ��� �ε��� ��ȭ.
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
	int startIndex_;	//���� �ε���.
	int curFrameIndex_;	//���� ������ �ε���.
	int endIndex_;		//���� �ε���.

	float curframeTime_;//���������� ���� �ð�.
	float interval_;	//�����Ӱ� �ð�����.
	float playTime_;	//���±��� �ִϸ��̼��� ����� �ð�.

	bool isLoop_;		//true == �ִϸ��̼� ���ѹݺ�. false == 1ȸ�ݺ� �� �����������ӿ��� ����.

	bool hasStarted_;	//true: �ִϸ��̼� ������. false: ���� �ִϸ��̼� �������� ����. 
	bool hasEnded_;		//true: �ִϸ��̼� ������. false: ���� �ִϸ��̼� �������� ����.
	bool isPaused_;	//true: �Ͻ�����.


	//template<typename AnimationData>
	//std::vector<AnimationData> animationDataVector_;

	//std::function<void(const FrameAnimation_Desc&)> start_;		//�ִϸ��̼� ��� ���۽� ȣ��Ǵ� �Լ���.
	//std::function<void(const FrameAnimation_Desc&)> frame_;		//�ִϸ��̼� ����� �� �����Ӹ��� ȣ��Ǵ� �Լ���.
	//std::function<void(const FrameAnimation_Desc&, float)> time_;	//�ִϸ��̼� ����� ���� �ð� �Ŀ� ȣ��Ǵ� �Լ���.
	//std::function<void(const FrameAnimation_Desc&)> end_;			//�ִϸ��̼� ��� ����� ȣ��Ǵ� �Լ���.

};

