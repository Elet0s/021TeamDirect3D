#pragma once
#include"Skill.h"
//���� �߻�ü�� �߻�
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
	float4 referenceVector_;//���غ��� - �������� ���� ������ �°� ȸ��������� 
};