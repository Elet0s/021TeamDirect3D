#pragma once
#include"Skill.h"
#include"Mouse.h"
// 자신의 주변으로 쿠나이를 던집니다.
class Kunai:public Skill
{
private:
	Kunai();
	~Kunai();

	Kunai(const Kunai& _Other) = delete;
	Kunai(Kunai&& _Other) noexcept = delete;
	Kunai& operator=(const Kunai& _Other) = delete;
	Kunai& operator=(Kunai&& _Other) noexcept = delete;
public:

	std::string& GetEtc()
	{
		return etc_;
	}

	CollisionReturn ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other); // 발사체 충돌
	CollisionReturn RangeToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);// 범위내 몬스터 탐색(사정거리 비례)

	std::shared_ptr<GameEngineCollision> crossbowRangeCol_;

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void SerchTarget();//공격 대상 탐색'
	void ProjectileSort();//발사체 생성및 플레이어 위치로 정렬
	void RenderRotate();// 발사체 회전
	void RangeCheak(float _deltaTime);//발사체 사출
	void StateSet() override;//레벨에 따른 스탯 적용

private:

	float resultCos_;//몬스터 좌표, 플레이어 좌표 x축 기준 각도 
	float4 referenceVector_;//플레이어 에서 몬스터로 가는 벡터 

	WeaponInfo crossbowWeaponInfo_;//무기 스탯

	std::vector<std::shared_ptr<ProjectileGroup>> projectileGroupList_;

};