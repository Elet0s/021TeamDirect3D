#pragma once
#include "Monster.h"

class GoblinLivesey :public Monster
{
public:
	GoblinLivesey();
	~GoblinLivesey();


	GoblinLivesey(const GoblinLivesey& _Other) = delete;
	GoblinLivesey(GoblinLivesey&& _Other) noexcept = delete;
	GoblinLivesey& operator=(const GoblinLivesey& _Other) = delete;
	GoblinLivesey& operator=(GoblinLivesey&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
private:
	void HpCheak();
};