#pragma once
#include"Skill.h"

//가장 낮은 체력의 적을 공격하는 다수의 수리검을 투척
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