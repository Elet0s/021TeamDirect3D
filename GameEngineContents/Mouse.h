#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineBase/GameEngineWindow.h>

class GameEngineTextureRenderer;
class TileMapRenderer;
class Mouse : public GameEngineActor
{
public:
	Mouse();
	~Mouse();


	Mouse(const Mouse& _Other) = delete;
	Mouse(Mouse&& _Other) noexcept = delete;
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;
public:
	std::shared_ptr<GameEngineTextureRenderer> mouseRenderer;
	GameEngineLevel* mouseLevel;
	std::shared_ptr<GameEngineCollision> mouseCollision_;

	inline void GetCurPos()
	{
		POINT Pos_;
		GetCursorPos(&Pos_);
		ScreenToClient(GameEngineWindow::GetHWND(), &Pos_);
		mousePosition.x = static_cast<float>(Pos_.x);
		mousePosition.y = static_cast<float>(Pos_.y);
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
private:
	float4 mousePosition;// 핸재 Window상의 마우스 위치
};