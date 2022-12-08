#pragma once
#include "Skill.h"
//자신을 중심으로 공전하는 번개구체를 소환
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