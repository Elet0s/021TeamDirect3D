#pragma once
#include "GameEngineRenderTarget.h"
#include "GameEngineRenderer.h"

class GameEngineBlur : public GameEnginePostEffect
{
	//이 클래스의 존재 이유:
public:
	GameEngineBlur();
	~GameEngineBlur();

protected:
	GameEngineBlur(const GameEngineBlur& _other) = delete;
	GameEngineBlur(GameEngineBlur&& _other) noexcept = delete;

private:
	GameEngineBlur& operator=(const GameEngineBlur& _other) = delete;
	GameEngineBlur& operator=(const GameEngineBlur&& _other) = delete;


public:
	virtual void EffectInit() override;
	virtual void Effect(GameEngineRenderTarget* _renderTarget) override;


private:
	class GameEngineRenderTarget* copiedRenderTarget_;
	class GameEngineRenderUnit effectUnit_;

};

