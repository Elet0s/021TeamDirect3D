#pragma once
#include "Skill.h"
//자신의 주변으로 적을 관통하고 돌아오는 검을 던짐
class Swordrang:public Skill
{
public:
	Swordrang();
	~Swordrang();

	Swordrang(const Swordrang& _Other) = delete;
	Swordrang(Swordrang&& _Other) noexcept = delete;
	Swordrang& operator=(const Swordrang& _Other) = delete;
	Swordrang& operator=(Swordrang&& _Other) noexcept = delete;

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
	void StateSet();
private:
	WeaponInfo SwordrangWeaponInfo_;
};