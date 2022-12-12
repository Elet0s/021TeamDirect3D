#pragma once
#include"Skill.h"
#include"Monster.h"
//가장 낮은 체력의 적을 공격하는 다수의 수리검을 투척
class Shuriken :public Skill
{
public:
	Shuriken();
	~Shuriken();

	Shuriken(const Shuriken& _Other) = delete;
	Shuriken(Shuriken&& _Other) noexcept = delete;
	Shuriken& operator=(const Shuriken& _Other) = delete;
	Shuriken& operator=(Shuriken&& _Other) noexcept = delete;
public:

	std::string& GetEtc()
	{
		return etc_;
	}

	CollisionReturn ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	void renderRotate(float _deltaTime);
	void RangeCheak(float _deltaTime);
	void StateSet() override;

private:
	float4 referenceVector_;//기준벡터 - 랜더러를 던질 각도에 맞게 회전해줘야함 
	std::shared_ptr<GameEngineTextureRenderer>  shuriKenRenderer_;
	std::shared_ptr<GameEngineCollision>  shuriKenCol_;
	WeaponInfo shuriKenWeaponInfo_;
	std::vector<std::shared_ptr<Monster>> monsterList_;
	std::pair<size_t, float> minHpPair_;

};

