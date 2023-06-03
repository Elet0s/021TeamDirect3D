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

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

	CollisionReturn ShurikenToMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other); // 발사체 충돌

public:
	std::pair<GameEngineTextureRenderer*, GameEngineCollision*>projectileGroup_;
	std::vector<std::pair<GameEngineTextureRenderer*, GameEngineCollision*>> projectileGroupList01_;//발사체 모음
	std::vector<std::pair<GameEngineTextureRenderer*, GameEngineCollision*>> projectileGroupList02_;
	std::vector<std::pair<GameEngineTextureRenderer*, GameEngineCollision*>> projectileGroupList03_;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void SerchTarget();//공격 대상 탐색'
	void ProjectileSort();//발사체 생성및 플레이어 위치로 정렬
	void RenderRotate( );// 발사체 회전
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
	float targerSerchTimer03_;

	size_t targetSerchCounter_;//타겟검사한 몬스터 수 매 업데이트 갱신

	std::vector<size_t> passNum_; //각 투사체 관통정보

	float resultCos_;//몬스터 좌표, 플레이어 좌표 x축 기준 각도 
	float4 referenceVector_;//플레이어 에서 몬스터로 가는 벡터 

	WeaponInfo shuriKenWeaponInfo_;//무기 스탯

	std::vector<Monster*> monsterList_; //전체 몬스터 리스트

	std::pair<size_t, float> minHpPair_;//타겟

	std::vector<std::pair<size_t, float>> targetInst01_;//타겟 묶음
	std::vector<std::pair<size_t, float>> targetInst02_;
	std::vector<std::pair<size_t, float>> targetInst03_;

	std::vector<float4> referenceVectorList01_;//방향 모음
	std::vector<float4> referenceVectorList02_;
	std::vector<float4> referenceVectorList03_;


};

