#pragma once
#include"Skill.h"

//���� ���� �������� �о�� �������� ū ����ü�� �߻�
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
	float4 referenceVector_;//���غ��� - �������� ���� ������ �°� ȸ��������� 
};