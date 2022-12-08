#pragma once
#include "Skill.h"
// 무작의 적에게 차례대로 공격하고 경로에 있는 다른 모든 적을 공격함 추가 투사체로 개수가 증가하지 않음
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