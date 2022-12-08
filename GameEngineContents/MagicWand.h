#pragma once
#include "Skill.h"
//가장 가까운 적에게 고정되는 마법 투사체를 발사
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