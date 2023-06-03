#pragma once
#include"Skill.h"
#include"Monster.h"
//가장 가까운 적에게 발사
class Bow :public Skill
{
public:
	Bow();
	~Bow();

	Bow(const Bow& _Other) = delete;
	Bow(Bow&& _Other) noexcept = delete;
	Bow& operator=(const Bow& _Other) = delete;
	Bow& operator=(Bow&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

	CollisionReturn ProjectileToMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other); // 발사체 충돌
public:
	std::pair<GameEngineTextureRenderer*, GameEngineCollision*>projectileGroup_;
	std::vector<std::pair<GameEngineTextureRenderer*, GameEngineCollision*>> projectileGroupList02_;
	std::vector<std::pair<GameEngineTextureRenderer*, GameEngineCollision*>> projectileGroupList01_;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void SerchTarget();//공격 대상 탐색'
	void ProjectileSort();//발사체 생성및 플레이어 위치로 정렬
	void RenderRotate();// 발사체 회전
	void RangeCheak(float _deltaTime);//발사체 사출
	void StateSet() override;//레벨에 따른 스탯 적용
	void ColCheak();//콜리전 체크
	void TarGetInitialization();//타겟초기화
	void TimerUpdater(float _deltaTime);//타이머 업데이트

private:
	bool firstSerchCheak_;
	bool istarget_;//타겟이 있으면 true

	float targerSerchTimer_;
	float targerSerchTimer01_;//타겟 검사 주기=공격속도
	float targerSerchTimer02_;

	std::vector<size_t> passNum_;

	size_t targetSerchCounter_;//타겟검사한 몬스터 수 매 업데이트 갱신

	float resultCos_;//몬스터 좌표, 플레이어 좌표 x축 기준 각도 
	float4 referenceVector_;//플레이어 에서 몬스터로 가는 벡터 

	WeaponInfo bowWeaponInfo_;//무기 스탯

	std::vector<Monster*> monsterList_; //전체 몬스터 리스트

	std::pair<size_t, float> minHpPair_;//타겟 대상

	std::vector<std::pair<size_t, float>> targetInst01_;//타겟 묶음
	std::vector<std::pair<size_t, float>> targetInst02_;

	std::vector<float4> referenceVectorList01_;//방향 모음
	std::vector<float4> referenceVectorList02_;
};