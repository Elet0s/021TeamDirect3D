#include "PreCompile.h"
#include "GameEngineRandom.h"

GameEngineRandom GameEngineRandom::mainRandom_;

GameEngineRandom::GameEngineRandom(long long _seed /*= -1*/)
{
	if (-1 == _seed)
	{
		mt_ = std::mt19937_64(
			std::chrono::system_clock::to_time_t(	//입력된 time_point구조체 형식의 시간을 time_t(long long)형식으로 형변환하는 함수.
				std::chrono::system_clock::now()	//현재의 초단위 시간을 time_point구조체 형식으로 반환하는 함수.
			)
		);
	}
	else
	{
		mt_ = std::mt19937_64(_seed);
	}
}

GameEngineRandom::~GameEngineRandom()
{
}
