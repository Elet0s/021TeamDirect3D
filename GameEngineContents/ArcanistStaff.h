#pragma once
#include"Skill.h"
//샤먼 스태프와 마법완드의 진화
class ArcanistStaff :public Skill	
{
private:
	ArcanistStaff();
	~ArcanistStaff();

	ArcanistStaff(const ArcanistStaff& _Other) = delete;
	ArcanistStaff(ArcanistStaff&& _Other) noexcept = delete;
	ArcanistStaff& operator=(const ArcanistStaff& _Other) = delete;
	ArcanistStaff& operator=(ArcanistStaff&& _Other) noexcept = delete;
};