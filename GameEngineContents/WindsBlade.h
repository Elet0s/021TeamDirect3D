#pragma once
#include"Skill.h"
//자신의 양옆에 바람 칼날을 소환
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
	void Shoothing(float _deltaTime);//사출패턴
	void StateSet() override;//레벨에 따른 스탯 적용
	void LevelEndEvent() override;
private:
	WeaponInfo WindsBladeWeaponInfo_;//무기 스탯
	bool RLSwitch_;
	float timer_;

	bool updateStart_;
	float delayTime_;
	size_t count_;
	size_t windPum_;
};