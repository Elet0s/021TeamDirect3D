#pragma once
#include "Skill.h"

//���ص� �������� ������ �
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
	float4 referenceVector_;//���غ��� - �������� ���� ������ �°� ȸ��������� 
};