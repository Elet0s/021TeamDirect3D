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

	float resultCos_;//몬스터 좌표, 플레이어 좌표 x축 기준 각도 
	float4 referenceVector_;//플레이어 에서 몬스터로 가는 벡터 

	WeaponInfo shuriKenWeaponInfo_;//무기 스탯

	std::vector<std::shared_ptr<Monster>> monsterList_; //전체 몬스터 리스트
	std::pair<size_t, float> minHpPair_;//타겟 대상
	std::vector<std::pair<size_t, float>> targetInst_;//타겟 모음
	



};

