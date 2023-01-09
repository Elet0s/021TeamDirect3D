#pragma once
#include "Monster.h"

class NormalSkeleton :public Monster
{
public:
	NormalSkeleton();
	~NormalSkeleton();


	NormalSkeleton(const NormalSkeleton& _Other) = delete;
	NormalSkeleton(NormalSkeleton&& _Other) noexcept = delete;
	NormalSkeleton& operator=(const NormalSkeleton& _Other) = delete;
	NormalSkeleton& operator=(NormalSkeleton&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
private:
	void HpCheak();
};