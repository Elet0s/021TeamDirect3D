#pragma once
#include"Skill.h"
//전방위발사
class Kunai : public Skill
{
public:
	Kunai();
	~Kunai();

	Kunai(const Kunai& _Other) = delete;
	Kunai(Kunai&& _Other) noexcept = delete;
	Kunai& operator=(const Kunai& _Other) = delete;
	Kunai& operator=(Kunai&& _Other) noexcept = delete;


	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

	CollisionReturn ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other); // 발사체 충돌
	CollisionReturn RangeToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);// 범위내 몬스터 탐색(사정거리 비례)

	std::shared_ptr<GameEngineCollision> spearRangeCol_;

	std::pair<std::shared_ptr<GameEngineTextureRenderer>, std::shared_ptr<GameEngineCollision>>projectileGroup_;
	std::vector<std::pair<std::shared_ptr<GameEngineTextureRenderer>, std::shared_ptr<GameEngineCollision>>> projectileGroupList_;//발사체 모음

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void Shoothing(float _deltaTime);//공격 대상 탐색'
	void ProjectileSort();//발사체 생성및 플레이어 위치로 정렬
	void RenderRotate();// 발사체 회전
	void RangeCheak(float _deltaTime);//발사체 사출
	void StateSet() override;//레벨에 따른 스탯 적용
	void AimSet();
	//void SerchTarget();//공격 대상 탐색'
	//void ProjectileSort();//발사체 생성및 플레이어 위치로 정렬
	//void RenderRotate();// 발사체 회전
	//void RangeCheak(float _deltaTime);//발사체 사출
	//void StateSet() override;//레벨에 따른 스탯 적용

private:
	bool Shooting_;
	bool setAim_;
	float timer_;
	float duringtime_;
	size_t consecutiveCounter_;
	float angle_;
	float resultCos_;//몬스터 좌표, 플레이어 좌표 x축 기준 각도 
	float4 referenceVector_;//플레이어 에서 몬스터로 가는 벡터 
	float4 mouseAimPos_;
	float consecutiveAngle_;
	float4 range_;
	float4 playerPos_;

	WeaponInfo spearWeaponInfo_;//무기 스탯


};