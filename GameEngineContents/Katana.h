#pragma once
#include"Skill.h"
//근처범위내에서 제일 가까운 적을 공격
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