#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TimeActor : public GameEngineActor
{
public:
	// constrcuter destructer
	TimeActor();
	~TimeActor();

	// delete Function
	TimeActor(const TimeActor& _Other) = delete;
	TimeActor(TimeActor&& _Other) noexcept = delete;
	TimeActor& operator=(const TimeActor& _Other) = delete;
	TimeActor& operator=(TimeActor&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override {};
	void SetTimer(std::string& _Text);

	std::shared_ptr<GameEngineFontRenderer> TimeRenderer_;
	std::shared_ptr<GameEngineTextureRenderer> UIRenderer_;
	std::string TimeString;


};

