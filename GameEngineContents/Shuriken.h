#pragma once
#include"Skill.h"

//���� ���� ü���� ���� �����ϴ� �ټ��� �������� ��ô
class Shuriken:public Skill
{
private:
	Shuriken();
	~Shuriken();

	Shuriken(const Shuriken& _Other) = delete;
	Shuriken(Shuriken&& _Other) noexcept = delete;
	Shuriken& operator=(const Shuriken& _Other) = delete;
	Shuriken& operator=(Shuriken&& _Other) noexcept = delete;
};