#pragma once
#include"Skill.h"
//���� ����� ������ �߻�
class Bow:public Skill
{
private:
	Bow();
	~Bow();

	Bow(const Bow& _Other) = delete;
	Bow(Bow&& _Other) noexcept = delete;
	Bow& operator=(const Bow& _Other) = delete;
	Bow& operator=(Bow&& _Other) noexcept = delete;
};