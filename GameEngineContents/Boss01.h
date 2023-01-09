#pragma once
#include "Monster.h"

class Boss01 :public Monster
{
public:
	Boss01();
	~Boss01();


	Boss01(const Boss01& _Other) = delete;
	Boss01(Boss01&& _Other) noexcept = delete;
	Boss01& operator=(const Boss01& _Other) = delete;
	Boss01& operator=(Boss01&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
private:
	void HpCheak();
};