#pragma once
#include"Skill.h"
//�ֺ��� �������� ������ ���ظ� ���� ġ��Ÿ�߻���������
class Firering:public Skill
{
private:
	Firering();
	~Firering();

	Firering(const Firering& _Other) = delete;
	Firering(Firering&& _Other) noexcept = delete;
	Firering& operator=(const Firering& _Other) = delete;
	Firering& operator=(Firering&& _Other) noexcept = delete;
};