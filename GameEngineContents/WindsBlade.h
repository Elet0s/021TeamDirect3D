#pragma once
#include"Skill.h"
//�ڽ��� �翷�� �ٶ� Į���� ��ȯ
class WindsBlade :public Skill
{
private:
	WindsBlade();
	~WindsBlade();

	WindsBlade(const WindsBlade& _Other) = delete;
	WindsBlade(WindsBlade&& _Other) noexcept = delete;
	WindsBlade& operator=(const WindsBlade& _Other) = delete;
	WindsBlade& operator=(WindsBlade&& _Other) noexcept = delete;
};