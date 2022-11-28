#pragma once
#include "GameEngineMath.h"

class GameEngineRandom
{
	//���� ���� Ŭ����.

public:

	static GameEngineRandom mainRandom_;
	//���ӿ��� ������ �ܼ� ���������� �ϸ� ���� �� �ȿ� ������ ������ �䱸������, 
	// ���� �õ尪�� ���� ������������ ���� ���� �Ѱ����� ����, ��ȯ�ϰ� �Ҹ������,
	// mainRandom_�� ���� ��������̹Ƿ� ������ ������ �Ѱ��� ��������� ���α׷��� ������ �Ҹ�Ǳ� ������, 
	// ���� �� �ȿ� ������ ������ �䱸�ص� �Ѱ��� mainRandom_�� ���� �ٸ� ������ �����Ѵ�.


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
		//��κ��� ���� �˰����� ������ ������ �Ҷ� %�� ����ϹǷ� _max -1���� ���´ٴ°��� �׻� ������ �� ��.
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
	std::mt19937_64 mt_;	//Mersenne Twister ���糭�� ������.



};

