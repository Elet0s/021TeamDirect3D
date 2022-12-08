#pragma once
#include"Skill.h"
//자신의 양옆에 바람 칼날을 소환
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