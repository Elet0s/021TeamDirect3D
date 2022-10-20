#pragma once
#include "GameEngineTextureRenderer.h"

class GameEngineUIRenderer: public GameEngineTextureRenderer
{
	//UI만 그리는 렌더러.
public:
	GameEngineUIRenderer();
	~GameEngineUIRenderer();

protected:
	GameEngineUIRenderer(const GameEngineUIRenderer& _other) = delete;
	GameEngineUIRenderer(GameEngineUIRenderer&& _other) noexcept = delete;

private:
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer& _other) = delete;
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer&& _other) = delete;


protected:
	void Start() override;



private:

};

