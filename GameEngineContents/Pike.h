#pragma once
#include "Skill.h"

//조준된 방향으로 빠르게 찌름
class Pike:public Skill
{
private:
	Pike();
	~Pike();

	Pike(const Pike& _Other) = delete;
	Pike(Pike&& _Other) noexcept = delete;
	Pike& operator=(const Pike& _Other) = delete;
	Pike& operator=(Pike&& _Other) noexcept = delete;

private:
	float4 referenceVector_;//기준벡터 - 랜더러를 던질 각도에 맞게 회전해줘야함 
};