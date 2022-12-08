#pragma once
#include "Skill.h"
//자신의 주변으로 적을 관통하고 돌아오는 검을 던짐
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