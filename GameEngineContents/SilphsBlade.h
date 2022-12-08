#pragma once
#include"Skill.h"
//바람의 칼날과 카타나의 진화 적을 벨 때마다 바람으 ㅣ칼날 투사체를 생성
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