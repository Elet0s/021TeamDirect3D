#pragma once
#include"Skill.h"
//매직위습과 공허의 영혼의 진화 이제 추가투사체 개수가 증가함
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