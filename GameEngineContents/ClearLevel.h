#pragma once

class ClearLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	ClearLevel();
	~ClearLevel();

	// delete Function
	ClearLevel(const ClearLevel& _Other) = delete;
	ClearLevel(ClearLevel&& _Other) noexcept = delete;
	ClearLevel& operator=(const ClearLevel& _Other) = delete;
	ClearLevel& operator=(ClearLevel&& _Other) noexcept = delete;

	class Mouse* GetMousePointer()
	{
		return mousePointer_;
	}

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
private:
	class Mouse* mousePointer_;
	void LevelStartEvent() override;
	void LevelEndEvent() override;
	class ClearUIBox* clearbox_;
	class StageUI* stageui_;

};


