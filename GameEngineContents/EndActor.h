#pragma once

class EndActor : public GameEngineActor
{
public:
	// constrcuter destructer
	EndActor();
	~EndActor();

	// delete Function
	EndActor(const EndActor& _Other) = delete;
	EndActor(EndActor&& _Other) noexcept = delete;
	EndActor& operator=(const EndActor& _Other) = delete;
	EndActor& operator=(EndActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _deltaTime);
	void End();
private:

};

