#pragma once
#include <GameEngineCore\CoreMinimal.h>

struct MonsterInfo
{
public:
	MonsterInfo()
		:
		speed_(100.0f),
		maxHp_(100),
		hp_(100),
		atk_(10)
	{

	}
public:
	float speed_;
	float maxHp_;
	float hp_;
	float atk_;
};
class GameEngineRandom;
class Monster: public GameEngineActor
{

public:
	Monster();
	~Monster();

	Monster(const Monster& _other) = delete;
	Monster(Monster&& _other) noexcept = delete;
	Monster& operator=(const Monster& _other) = delete;
	Monster& operator=(Monster&& _other) = delete;
public:

	MonsterInfo& GetMonsterInfo()
	{
		return *CastThis<Monster>()->monsterInfo_;
	}

	float mxMove_;
	float myMove_;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	void Chaseplayer(float _deltaTime);
	void SummonMon();

	std::shared_ptr < MonsterInfo> monsterInfo_;
	std::shared_ptr<GameEngineTextureRenderer> monRenderer_;
	std::shared_ptr<GameEngineCollision> monCollision_;
	std::shared_ptr<class Texture2DShadowRenderer> shadowRenderer_;
};