#pragma once
#include "Skill.h"
//�ڽ��� �߽����� �����ϴ� ������ü�� ��ȯ
class ThunderStaf:public Skill
{
public:
	ThunderStaf();
	~ThunderStaf();

	ThunderStaf(const ThunderStaf& _Other) = delete;
	ThunderStaf(ThunderStaf&& _Other) noexcept = delete;
	ThunderStaf& operator=(const ThunderStaf& _Other) = delete;
	ThunderStaf& operator=(ThunderStaf&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

	CollisionReturn ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
};