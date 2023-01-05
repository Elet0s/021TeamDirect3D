#pragma once
#include "GlobalContentsValue.h"
struct WeaponInfo
{
	float weaponAtk_;//������ݷ�
	float weaponAtkSpeed_;//���ݼӵ�
	size_t weaponPassAtk_;//�����
	size_t weaponPassNum_;//����Ƚ��
	float weaponSize_;//����üũ��
	float weaponDuration_;//����ü���ӽð�
	float weaponSpeed_;// ����ü�ӵ� 
	float weaponknockback_;//�˹�
	size_t weponConsecutiveAtkNum_;//����ü ���Ӱ���Ƚ��(�� ���� �ֱ⿡ ��� ��������)
	size_t weaponProjectileNum_; //����ü�߰�����(�ѹ��� ������ �߻�ü Ƚ��)
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
		weaponPassNum_(0)
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
	int nowLevel_;
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
	int currentlevel_;
	int maxLevel_;

	Rank myRank_;
private:
};

