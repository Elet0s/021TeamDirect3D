#pragma once
#include"Skill.h"
//���� �������� �����ϵ��� ��ȭ
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