#pragma once
#include"Skill.h"
//�ٶ��� Į���� īŸ���� ��ȭ ���� �� ������ �ٶ��� ��Į�� ����ü�� ����
class SilphsBlade :public Skill
{
private:
	SilphsBlade();
	~SilphsBlade();

	SilphsBlade(const SilphsBlade& _Other) = delete;
	SilphsBlade(SilphsBlade&& _Other) noexcept = delete;
	SilphsBlade& operator=(const SilphsBlade& _Other) = delete;
	SilphsBlade& operator=(SilphsBlade&& _Other) noexcept = delete;
};