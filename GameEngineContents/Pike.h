#pragma once
#include"Skill.h"
//투사체 조준된 방향으로 발사
class Pike : public Skill
{
public:
	Pike();
	~Pike();

	Pike(const Pike& _Other) = delete;
	Pike(Pike&& _Other) noexcept = delete;
	Pike& operator=(const Pike& _Other) = delete;
	Pike& operator=(Pike&& _Other) noexcept = delete;


	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}


	GameEngineCollision* spearRangeCol_;

	std::pair<GameEngineTextureRenderer*, GameEngineCollision*>projectileGroup_;
	std::vector<std::pair<GameEngineTextureRenderer*, GameEngineCollision*>> projectileGroupList_;//발사체 모음

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void Shoothing(float _deltaTime);//사출패턴
	void StateSet() override;//레벨에 따른 스탯 적용
	void AimSet();//마우스 켜줌

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

	float4 range_;
	float4 playerPos_;

	WeaponInfo pikeWeaponInfo_;//무기 스탯


};