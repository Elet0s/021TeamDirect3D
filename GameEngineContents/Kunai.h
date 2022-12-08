#pragma once
#include"Skill.h"
// 자신의 주변으로 쿠나이를 던집니다.
class Kunai:public Skill
{
private:
	Kunai();
	~Kunai();

	Kunai(const Kunai& _Other) = delete;
	Kunai(Kunai&& _Other) noexcept = delete;
	Kunai& operator=(const Kunai& _Other) = delete;
	Kunai& operator=(Kunai&& _Other) noexcept = delete;
private:
	float4 referenceVector_;//기준벡터 - 랜더러를 던질 각도에 맞게 회전해줘야함 
};