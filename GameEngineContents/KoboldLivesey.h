#pragma once
#include "Monster.h"

class KoboldLivesey :public Monster
{
public:
	KoboldLivesey();
	~KoboldLivesey();


	KoboldLivesey(const KoboldLivesey& _Other) = delete;
	KoboldLivesey(KoboldLivesey&& _Other) noexcept = delete;
	KoboldLivesey& operator=(const KoboldLivesey& _Other) = delete;
	KoboldLivesey& operator=(KoboldLivesey&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
private:
};