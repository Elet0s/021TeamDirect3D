#pragma once
#include "Skill.h"
//���� ����� ������ �����Ǵ� ���� ����ü�� �߻�
class MagicWand :public Skill
{
private:
	MagicWand();
	~MagicWand();

	MagicWand(const MagicWand& _Other) = delete;
	MagicWand(MagicWand&& _Other) noexcept = delete;
	MagicWand& operator=(const MagicWand& _Other) = delete;
	MagicWand& operator=(MagicWand&& _Other) noexcept = delete;
};