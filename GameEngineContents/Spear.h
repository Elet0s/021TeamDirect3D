#pragma once
#include"Skill.h"

//����ü ���ص� �������� �߻�
class Spear : public Skill
{
public:
	Spear();
	~Spear();

	Spear(const Spear& _Other) = delete;
	Spear(Spear&& _Other) noexcept = delete;
	Spear& operator=(const Spear& _Other) = delete;
	Spear& operator=(Spear&& _Other) noexcept = delete;
public:
	std::shared_ptr<GameEngineCollision> Collision_;

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
	void Left(float _deltaTime);

private:
	float damege_;
	float attackSpeed_;
	float rangeSize_;
	float4 referenceVector_;//���غ��� - �������� ���� ������ �°� ȸ��������� 
	std::shared_ptr<GameEngineTextureRenderer> spearRenderer_;
	std::shared_ptr<GameEngineCollision> spearCol_;
};