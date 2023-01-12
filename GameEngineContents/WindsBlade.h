#pragma once
#include"Skill.h"
//�ڽ��� �翷�� �ٶ� Į���� ��ȯ
class WindsBlade :public Skill
{
public:
	WindsBlade();
	~WindsBlade();

	WindsBlade(const WindsBlade& _Other) = delete;
	WindsBlade(WindsBlade&& _Other) noexcept = delete;
	WindsBlade& operator=(const WindsBlade& _Other) = delete;
	WindsBlade& operator=(WindsBlade&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}


protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	void Shoothing(float _deltaTime);//��������
	void StateSet() override;//������ ���� ���� ����

private:
	WeaponInfo WindsBladeWeaponInfo_;//���� ����
	bool RLSwitch_;
	float timer_;
};