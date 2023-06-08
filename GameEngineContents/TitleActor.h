#pragma once

class TitleActor : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleActor();
	~TitleActor();

	// delete Function
	TitleActor(const TitleActor& _Other) = delete;
	TitleActor(TitleActor&& _Other) noexcept = delete;
	TitleActor& operator=(const TitleActor& _Other) = delete;
	TitleActor& operator=(TitleActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _deltaTime);
	void End();
private:

};

