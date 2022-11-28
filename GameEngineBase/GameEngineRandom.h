#pragma once
#include "GameEngineMath.h"

class GameEngineRandom
{
	//난수 생성 클래스.

public:

	static GameEngineRandom mainRandom_;
	//게임엔진 랜덤을 단순 지역변수로 하면 같은 초 안에 여러번 난수를 요구했을때, 
	// 같은 시드값의 여러 지역변수들이 같은 난수 한개씩만 생성, 반환하고 소멸되지만,
	// mainRandom_은 정적 멤버변수이므로 데이터 영역에 한개만 만들어지고 프로그램이 끝날때 소멸되기 때문에, 
	// 같은 초 안에 난수를 여러번 요구해도 한개의 mainRandom_이 각각 다른 난수를 생성한다.


public:

	GameEngineRandom(long long _seed = -1);
	~GameEngineRandom();

	GameEngineRandom(const GameEngineRandom& _other) = delete;
	GameEngineRandom(GameEngineRandom&& _other) noexcept = delete;
	GameEngineRandom& operator=(const GameEngineRandom& _other) = delete;
	GameEngineRandom& operator=(GameEngineRandom&& _other) = delete;

public:
	int RandomInt(int _min, int _max)
	{
		//대부분의 난수 알고리즘이 마지막 제한을 할때 %를 사용하므로 _max -1까지 나온다는것을 항상 염두해 둘 것.
		std::uniform_int_distribution<int> intDistribution(_min, _max);
		return intDistribution(mt_);
	}

	float RandomFloat(float _min, float _max)
	{
		std::uniform_real_distribution<float> floatDistribution(_min, _max);
		return floatDistribution(mt_);
	}

	float4 RandomFloat4(float _min, float _max)
	{
		std::uniform_real_distribution<float> floatDistribution(_min, _max);
		return float4(floatDistribution(mt_), floatDistribution(mt_), floatDistribution(mt_));
	}

	float4 RandomFloat4(int _min, int _max)
	{
		std::uniform_int_distribution<int> intDistribution(_min, _max);
		return float4(intDistribution(mt_), intDistribution(mt_), intDistribution(mt_));
	}


private:
	std::mt19937_64 mt_;	//Mersenne Twister 유사난수 생성기.



};

