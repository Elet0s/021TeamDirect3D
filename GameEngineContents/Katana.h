#pragma once
#include"Skill.h"
//��ó���������� ���� ����� ���� ����
class Katana :public Skill
{
private:
	Katana();
	~Katana();

	Katana(const Katana& _Other) = delete;
	Katana(Katana&& _Other) noexcept = delete;
	Katana& operator=(const Katana& _Other) = delete;
	Katana& operator=(Katana&& _Other) noexcept = delete;
};