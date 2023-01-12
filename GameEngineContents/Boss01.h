#pragma once
#include "Monster.h"
#include "Projectile.h"
#include"MagicCircle.h"

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

	void BossHp();

	void PatternMove(float _deltaTime);
	void Relocation();

protected:
	float idleTime_;
	float collingTime01_;
	float collingTime02_;
	float collingTime03_;
	float delay_;
	int telleportCount_;
	size_t shootingCount_;
	bool shootingEnd_;
private:

};