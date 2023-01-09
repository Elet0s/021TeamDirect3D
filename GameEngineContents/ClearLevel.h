#pragma once

// Ό³Έν :
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

	std::shared_ptr<class Mouse> GetMousePointer()
	{
		return mousePointer_;
	}
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
private:
	std::shared_ptr<class Mouse> mousePointer_;
	void LevelStartEvent() override;
	void LevelEndEvent() override;
	std::shared_ptr<class ClearUIBox> clearbox_;
	

};


