#pragma once
#include "GlobalContentsValue.h"
struct WeaponInfo
{
	float weaponAtk_;//������ݷ�
	float weaponPassAtk_;//�����
	float weaponAtkSpeed_;//���ݼӵ�
	float weaponSize_;//����üũ��
	float weaponDuration_;//����ü���ӽð�
	float weaponSpeed_;// ����ü�ӷ�
	float weaponknockback_;//�˹�
	float weaponAddAtk_;
	WeaponInfo()
		:weaponAtk_(0),
		weaponPassAtk_(0),
		weaponAtkSpeed_(0),
		weaponSize_(0),
		weaponDuration_(0),
		weaponSpeed_(0),
		weaponknockback_(0),
		weaponAddAtk_(0)
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

