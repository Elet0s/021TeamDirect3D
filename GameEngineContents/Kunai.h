#pragma once
#include"Skill.h"
// �ڽ��� �ֺ����� ���̸� �����ϴ�.
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
	float4 referenceVector_;//���غ��� - �������� ���� ������ �°� ȸ��������� 
};