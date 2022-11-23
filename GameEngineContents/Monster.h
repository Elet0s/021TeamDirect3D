#pragma once
#include <GameEngineCore\CoreMinimal.h>

struct MonsterInfo
{
public:
	MonsterInfo()
		:baseSpeed_(0),
		colSpeed_(0),
		ResultSpeed_(0),
		maxHp_(0),
		hp_(0),
		atk_(0),
		giveExp_(0)
	{

	}
public:
	float baseSpeed_;
	float colSpeed_;
	float ResultSpeed_;
	float maxHp_;
	float hp_;
	float atk_;
	float giveExp_;
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
	CollisionReturn MonsterToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	CollisionReturn MonsterToPlayerCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	float mxMove_;
	float myMove_;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	void Chaseplayer(float _deltaTime);
	void SummonMon();
	bool colCheak_;
	float playerRange_;
	float mx_;
	float my_;
	float4 range_;
	std::shared_ptr<GameEngineCollision> monCollision_;
	std::shared_ptr < MonsterInfo> monsterInfo_;
	std::shared_ptr<GameEngineTextureRenderer> monRenderer_;
	std::shared_ptr<class Texture2DShadowRenderer> shadowRenderer_;
};