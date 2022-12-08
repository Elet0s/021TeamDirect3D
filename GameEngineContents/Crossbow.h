#pragma once
#include"Skill.h"
//가장 체력이 많은 적에게 발사
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