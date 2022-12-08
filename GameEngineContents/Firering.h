#pragma once
#include"Skill.h"
//주변의 범위내의 적에게 피해를 입힘 치명타발생하지않음
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