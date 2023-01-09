#pragma once
#include"Skill.h"
//주변의 범위내의 적에게 피해를 입힘 치명타발생하지않음
class Firering:public Skill
{
public:
	Firering();
	~Firering();

	Firering(const Firering& _Other) = delete;
	Firering(Firering&& _Other) noexcept = delete;
	Firering& operator=(const Firering& _Other) = delete;
	Firering& operator=(Firering&& _Other) noexcept = delete;


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
	void RotateRenderer(float _deltaTime);

	void  StateSet();
private:
	std::shared_ptr<GameEngineTextureRenderer> circleRendererA_;
	std::shared_ptr<GameEngineTextureRenderer> circleRendererB_;
	std::shared_ptr<GameEngineTextureRenderer> circleRendererC_;
	std::shared_ptr<GameEngineTextureRenderer> circleRendererD_;
	std::shared_ptr<GameEngineTextureRenderer> circleCenterRenderer_;
	std::shared_ptr<GameEngineCollision> fireringAuraCollision01_;
	std::shared_ptr<GameEngineCollision> fireringAuraCollision02_;
	std::shared_ptr<GameEngineCollision> fireringAuraCollision03_;

	WeaponInfo fireringAuraWeaponInfo_;//무기 스탯

	float atkTimer_;
	float addRadian_;
	float damege;
	float attackSpeed;
	float rangeSize;
};