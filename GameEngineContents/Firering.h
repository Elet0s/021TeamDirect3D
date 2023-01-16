#pragma once
#include"Skill.h"
//�ֺ��� �������� ������ ���ظ� ���� ġ��Ÿ�߻���������
class Firering:public Skill
{
public:
	Firering();
	~Firering();

	Firering(const Firering& _Other) = delete;
	Firering(Firering&& _Other) noexcept = delete;
	Firering& operator=(const Firering& _Other) = delete;
	Firering& operator=(Firering&& _Other) noexcept = delete;


	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

	CollisionReturn FireringToMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	void RotateRenderer(float _deltaTime);

	void  StateSet();
private:
	GameEngineTextureRenderer* circleRendererA_;
	GameEngineTextureRenderer* circleRendererB_;
	GameEngineTextureRenderer* circleRendererC_;
	GameEngineTextureRenderer* circleRendererD_;
	GameEngineTextureRenderer* circleCenterRenderer_;
	GameEngineCollision* fireringAuraCollision01_;
	GameEngineCollision* fireringAuraCollision02_;
	GameEngineCollision* fireringAuraCollision03_;

	WeaponInfo fireringAuraWeaponInfo_;//���� ����

	float atkTimer_;
	float addRadian_;
	float damege;
	float attackSpeed;
	float rangeSize;
};