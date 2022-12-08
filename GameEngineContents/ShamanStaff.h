#pragma once
#include"Skill.h"
//많은 발사체를 발사
class ShamanStaff:public Skill
{
private:
	ShamanStaff();
	~ShamanStaff();

	ShamanStaff(const ShamanStaff& _Other) = delete;
	ShamanStaff(ShamanStaff&& _Other) noexcept = delete;
	ShamanStaff& operator=(const ShamanStaff& _Other) = delete;
	ShamanStaff& operator=(ShamanStaff&& _Other) noexcept = delete;

private:
	float4 referenceVector_;//기준벡터 - 랜더러를 던질 각도에 맞게 회전해줘야함 
};