#pragma once
#include "GlobalContentsValue.h"


struct WeaponInfo
{
	float weaponAtk_;//무기공격력
	float weaponAtkSpeed_;//공격속도
	size_t weaponPassAtk_;//관통력
	size_t weaponPassNum_;//관통횟수
	float weaponSize_;//투사체크기
	float weaponDuration_;//투사체지속시간
	float weaponSpeed_;// 투사체속도 
	float weaponRange_;// 무기 범위
	float weaponknockback_;//넉백
	size_t weponConsecutiveAtkNum_;//투사체 연속공격횟수(한 공격 주기에 몇번 던지는지)
	size_t weaponProjectileNum_; //투사체추가갯수(한번에 던지는 발사체 횟수)
	WeaponInfo()
		:weaponAtk_(0), 
		weaponPassAtk_(0),
		weaponAtkSpeed_(0),
		weaponSize_(0),
		weaponDuration_(0),
		weaponSpeed_(0),
		weaponknockback_(0),
		weaponProjectileNum_(0),
		weponConsecutiveAtkNum_(0),
		weaponPassNum_(0),
		weaponRange_(0)
	{
	}
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

	void IsOnOff()
	{
		isOn_ = false;
	}

	void IsOnOn()
	{
		isOn_ = true;
	}

	bool GetIsOn()
	{
		return isOn_;
	}
public:
	int currentlevel_;
	bool Shooting;
protected:
	virtual void  StateSet() ;
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	bool isOn_;
	SoulCard valueSoulCard_;
	std::string name_;
	std::string etc_;
	int maxLevel_;

	Rank myRank_;
private:
};

