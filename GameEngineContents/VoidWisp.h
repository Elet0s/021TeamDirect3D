#pragma once
#include"Skill.h"
//���������� ������ ��ȥ�� ��ȭ ���� �߰�����ü ������ ������
class VoidWisp :public Skill
{
private:
	VoidWisp();
	~VoidWisp();

	VoidWisp(const VoidWisp& _Other) = delete;
	VoidWisp(VoidWisp&& _Other) noexcept = delete;
	VoidWisp& operator=(const VoidWisp& _Other) = delete;
	VoidWisp& operator=(VoidWisp&& _Other) noexcept = delete;
};