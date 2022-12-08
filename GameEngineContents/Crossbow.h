#pragma once
#include"Skill.h"
//���� ü���� ���� ������ �߻�
class Crossbow :public Skill
{
private:
	Crossbow();
	~Crossbow();

	Crossbow(const Crossbow& _Other) = delete;
	Crossbow(Crossbow&& _Other) noexcept = delete;
	Crossbow& operator=(const Crossbow& _Other) = delete;
	Crossbow& operator=(Crossbow&& _Other) noexcept = delete;
};