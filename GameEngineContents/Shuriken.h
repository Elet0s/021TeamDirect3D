#pragma once
#include"Skill.h"
#include"Monster.h"
//���� ���� ü���� ���� �����ϴ� �ټ��� �������� ��ô
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
	CollisionReturn RangeToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

public:
	std::shared_ptr<GameEngineTextureRenderer>  shuriKenRenderer_;
	std::shared_ptr<GameEngineCollision>  shuriKenCol_;
	std::shared_ptr<GameEngineCollision>  shuriKenRangeCol_;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	void SerchTarget();
	void RenderRotate( );
	void RangeCheak(float _deltaTime);
	void StateSet() override;

private:
	float resultCos_;
	float4 referenceVector_;//���غ��� - �������� ���� ������ �°� ȸ��������� 

	WeaponInfo shuriKenWeaponInfo_;
	std::vector<std::shared_ptr<Monster>> monsterList_;
	std::pair<size_t, float> minHpPair_;
	std::vector<std::pair<size_t, float>> targetInst_;


};
