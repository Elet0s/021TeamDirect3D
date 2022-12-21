#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineBase/GameEngineWindow.h>

class GameEngineTextureRenderer;
class TileMapRenderer;
class Mouse : public GameEngineActor
{
	static std::shared_ptr<Mouse> mainMouse_;


public:
	Mouse();
	~Mouse();


	Mouse(const Mouse& _Other) = delete;
	Mouse(Mouse&& _Other) noexcept = delete;
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;
public:

	static void CreateMouse(GameEngineLevel* _thisLeve);

	std::shared_ptr<GameEngineTextureRenderer> mouseRenderer;
	std::shared_ptr<GameEngineCollision> mouseCollision_;

	inline void GetCurPos()
	{
		POINT Pos_;
		GetCursorPos(&Pos_);
		mousePositionToClient_.x =(GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().x);
		mousePositionToClient_.y =(GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().y);
		ScreenToClient(GameEngineWindow::GetHWND(), &Pos_);
		mousePositionToWindow_.x = static_cast<float>(Pos_.x);
		mousePositionToWindow_.y = static_cast<float>(Pos_.y);
	}

	static std::shared_ptr<Mouse> GetMouseInfo()
	{
		return mainMouse_;
	}

 inline float4  IsCurPosToWindow()
	{
		return mousePositionToWindow_;
	}

 inline float4  IsCurPosToClient()
 {
	 return mousePositionToClient_;
 }
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
private:
	float4 mousePositionToWindow_;// 현재 Window상의 마우스 위치
	float4 mousePositionToClient_;//클라이언트상의 마우스 위치
};