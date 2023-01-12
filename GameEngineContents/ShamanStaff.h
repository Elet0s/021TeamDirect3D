#pragma once
#include"Skill.h"
//많은 발사체를 발사
class ShamanStaff:public Skill
{
public:
	ShamanStaff();
	~ShamanStaff();

	ShamanStaff(const ShamanStaff& _Other) = delete;
	ShamanStaff(ShamanStaff&& _Other) noexcept = delete;
	ShamanStaff& operator=(const ShamanStaff& _Other) = delete;
	ShamanStaff& operator=(ShamanStaff&& _Other) noexcept = delete;

	void Init() override;
	void Effect() override;

	std::string& GetEtc()
	{
		return etc_;
	}

	CollisionReturn ProjectileToMonsterCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
};