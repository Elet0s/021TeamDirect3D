#pragma once
#include "Skill.h"
//�ڽ��� �߽����� �����ϴ� ������ü�� ��ȯ
class ThunderStaf:public Skill
{
private:
	ThunderStaf();
	~ThunderStaf();

	ThunderStaf(const ThunderStaf& _Other) = delete;
	ThunderStaf(ThunderStaf&& _Other) noexcept = delete;
	ThunderStaf& operator=(const ThunderStaf& _Other) = delete;
	ThunderStaf& operator=(ThunderStaf&& _Other) noexcept = delete;
};