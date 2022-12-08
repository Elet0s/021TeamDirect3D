#pragma once
#include "Skill.h"
// ������ ������ ���ʴ�� �����ϰ� ��ο� �ִ� �ٸ� ��� ���� ������ �߰� ����ü�� ������ �������� ����
class MagicWisp:public Skill
{
private:
	MagicWisp();
	~MagicWisp();

	MagicWisp(const MagicWisp& _Other) = delete;
	MagicWisp(MagicWisp&& _Other) noexcept = delete;
	MagicWisp& operator=(const MagicWisp& _Other) = delete;
	MagicWisp& operator=(MagicWisp&& _Other) noexcept = delete;
};