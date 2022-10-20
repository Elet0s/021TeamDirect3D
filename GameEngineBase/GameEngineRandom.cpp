#include "PreCompile.h"
#include "GameEngineRandom.h"

GameEngineRandom GameEngineRandom::mainRandom_;

GameEngineRandom::GameEngineRandom(long long _seed /*= -1*/)
{
	if (-1 == _seed)
	{
		mt_ = std::mt19937_64(
			std::chrono::system_clock::to_time_t(	//�Էµ� time_point����ü ������ �ð��� time_t(long long)�������� ����ȯ�ϴ� �Լ�.
				std::chrono::system_clock::now()	//������ �ʴ��� �ð��� time_point����ü �������� ��ȯ�ϴ� �Լ�.
		));
	}
	else
	{
		mt_ = std::mt19937_64(_seed);
	}
}

GameEngineRandom::~GameEngineRandom()
{
}
