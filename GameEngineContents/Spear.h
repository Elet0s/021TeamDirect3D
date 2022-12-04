#pragma once
#include"Skill.h"

class Spear : public Skill
{
public:
	Spear();
	~Spear();

	Spear(const Spear& _Other) = delete;
	Spear(Spear&& _Other) noexcept = delete;
	Spear& operator=(const Spear& _Other) = delete;
	Spear& operator=(Spear&& _Other) noexcept = delete;
public:
	std::shared_ptr<GameEngineCollision> Collision_;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

protected:


private:
	float damege;
	float attackSpeed;
	float rangeSize;
	std::shared_ptr<GameEngineTextureRenderer> spearRenderer_;
};