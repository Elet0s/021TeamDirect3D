#pragma once
#include "Skill.h"
//�ڽ��� �ֺ����� ���� �����ϰ� ���ƿ��� ���� ����
class Swordrang:public Skill
{
private:
	Swordrang();
	~Swordrang();

	Swordrang(const Swordrang& _Other) = delete;
	Swordrang(Swordrang&& _Other) noexcept = delete;
	Swordrang& operator=(const Swordrang& _Other) = delete;
	Swordrang& operator=(Swordrang&& _Other) noexcept = delete;
};