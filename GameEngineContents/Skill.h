#pragma once
#include "GlobalContentsValue.h"
struct WeaponInfo
{
	float weaponAtk_;//무기공격력
	float weaponPassAtk_;//관통력
	float weaponAtkSpeed_;//공격속도
	float weaponSize_;//투사체크기
	float weaponDuration_;//투사체지속시간
	float weaponSpeed_;// 투사체속력
	float weaponknockback_;//넉백
};

class Skill : public GameEngineActor
{
public:
	Skill();
	virtual ~Skill();

	Skill(const Skill& _Other) = delete;
	Skill(Skill&& _Other) noexcept = delete;
	Skill& operator=(const Skill& _Other) = delete;
	Skill& operator=(Skill&& _Other) noexcept = delete;
	
public:
	virtual void Init() {};
	virtual void Effect() {};

	std::string_view GetSkillName()
	{
		return name_;
	}

	Rank GetRank()
	{
		return myRank_;
	}

	int GetCurrentlevel()
	{
		return currentlevel_;
	}

	int GetMaxLevel()
	{
		return maxLevel_;
	}

	SoulCard& GetSoulCardOrder()
	{
		return valueSoulCard_;
	}

public:
	int nowLevel_;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	SoulCard valueSoulCard_;
	std::string name_;
	std::string etc_;
	int currentlevel_;
	int maxLevel_;

	Rank myRank_;
private:
};

