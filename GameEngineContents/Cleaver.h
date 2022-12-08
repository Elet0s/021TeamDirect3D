#pragma once
#include"Skill.h"

//적을 조준 방향으로 밀어내는 약하지만 큰 투사체를 발사
class Cleaver : public Skill
{
private:
	Cleaver();
	~Cleaver();

	Cleaver(const Cleaver& _Other) = delete;
	Cleaver(Cleaver&& _Other) noexcept = delete;
	Cleaver& operator=(const Cleaver& _Other) = delete;
	Cleaver& operator=(Cleaver&& _Other) noexcept = delete;
private:
	float4 referenceVector_;//기준벡터 - 랜더러를 던질 각도에 맞게 회전해줘야함 
};