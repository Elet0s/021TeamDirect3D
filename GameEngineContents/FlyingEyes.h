#pragma once
#include "Monster.h"

class FlyingEyes :public Monster
{
public:
	FlyingEyes();
	~FlyingEyes();


	FlyingEyes(const FlyingEyes& _Other) = delete;
	FlyingEyes(FlyingEyes&& _Other) noexcept = delete;
	FlyingEyes& operator=(const FlyingEyes& _Other) = delete;
	FlyingEyes& operator=(FlyingEyes&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
private:
};