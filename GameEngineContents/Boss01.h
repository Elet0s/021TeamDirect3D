#pragma once
#include "Monster.h"
#include "Projectile.h"

class Boss01 :public Monster
{
	static std::vector<std::shared_ptr<Projectile>> monsterProjectile_;
public:
	Boss01();
	~Boss01();

	Boss01(const Boss01& _Other) = delete;
	Boss01(Boss01&& _Other) noexcept = delete;
	Boss01& operator=(const Boss01& _Other) = delete;
	Boss01& operator=(Boss01&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void PatternMove(float _deltaTime);
protected:

	
private:
	BossPattern bossPattern_;
};