#pragma once
#include"Skill.h"

//���� ��ȥ�� īŸ���� ��ȭ īŸ�� ������ ���� ���ظ� ����
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