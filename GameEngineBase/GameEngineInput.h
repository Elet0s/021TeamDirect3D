#pragma once


class GameEngineInput
{
	class GameEngineKey
	{
		friend GameEngineInput;

		int keyValue_;
		bool isDown_;
		bool isPressed_;
		bool isUp_;
		bool isFree_;
		float time_;

	public:
		GameEngineKey()
			: keyValue_(0),
			isDown_(false),
			isPressed_(false),
			isUp_(false),
			isFree_(true),
			time_(0.f)
		{
		}
		

	public:
		void Update(float _deltaTime);
		void Reset()
		{
			isDown_ = false;
			isPressed_ = false;
			isUp_ = false;
			isFree_ = true;
			time_ = 0.f;
		}
	};

	static GameEngineInput* inst_;


public:	
	void CreateKey(const std::string& _keyName, int _keyValue);
	void Update(float _deltaTime);
	void Reset();
	float GetTime(const std::string& _keyName);
	bool IsDown(const std::string& _keyName);
	bool IsPressed(const std::string& _keyName);
	bool IsUp(const std::string& _keyName);
	bool IsFree(const std::string& _keyName);
	bool IsKey(const std::string& _keyName);


public:
	static GameEngineInput* GetInst()
	{
		return inst_;
	}

	static void Destroy()
	{
		//�̱��� ����'��' ���ϴ� Ÿ�ֿ̹� �Ѵ�.
		if (nullptr != inst_)
		{
			delete inst_;
			inst_ = nullptr;
		}
	}

	void SetWheelValue(int _value)
	{
		wheelValue_ = _value;
	}

private:
	GameEngineInput();
	~GameEngineInput();
	GameEngineInput(const GameEngineInput& _other) = delete;
	GameEngineInput(GameEngineInput&& _other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _other) = delete;
	GameEngineInput& operator=(const GameEngineInput&& _other) = delete;

private:
	int wheelValue_;
	int curWheelValue_;
	std::map<std::string, GameEngineKey> allKeys_;


};



