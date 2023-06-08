#pragma once
#include"Skill.h"

//범위내에서 제일 가까운 적 소수를 공격
class Monster;
class Katana :public Skill
{
public:
	Katana();
	~Katana();

	Katana(const Katana& _Other) = delete;
	Katana(Katana&& _Other) noexcept = delete;
	Katana& operator=(const Katana& _Other) = delete;
	Katana& operator=(Katana&& _Other) noexcept = delete;

	//void Init() override;
	//void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void SearchTarget();	
	void StateSet() override;

private:
	void Attack();

private:

	WeaponInfo katanaWeaponInfo_;//무기 스탯
	float squaredWeaponRange_;
	size_t targetLimitation_;
	float attackInterval_;
	
	std::list<Monster*> monstersInRange_;	//범위 내 몇몇 몬스터.
	//std::pair<size_t, float> minHpPair_;//타겟 대상
	//std::vector<std::pair<size_t, float>> targetInst_;//타겟 모음



	GameEngineTextureRenderer* katanaRenderer_[4];

};