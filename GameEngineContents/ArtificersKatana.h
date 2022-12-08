#pragma once
#include"Skill.h"

//불의 영혼과 카타나의 진화 카타나 공격이 범위 피해를 임힘
class ArtificersKatana :public Skill
{
private:
	ArtificersKatana();
	~ArtificersKatana();

	ArtificersKatana(const ArtificersKatana& _Other) = delete;
	ArtificersKatana(ArtificersKatana&& _Other) noexcept = delete;
	ArtificersKatana& operator=(const ArtificersKatana& _Other) = delete;
	ArtificersKatana& operator=(ArtificersKatana&& _Other) noexcept = delete;
};