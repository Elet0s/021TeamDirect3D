#pragma once
#include "Monster.h"

class Red :public Monster
{
public:
	Red();
	~Red();


	Red(const Red& _Other) = delete;
	Red(Red&& _Other) noexcept = delete;
	Red& operator=(const Red& _Other) = delete;
	Red& operator=(Red&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
private:
};