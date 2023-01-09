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

	void isSoulselectOn()
	{
		issoulselect_ = true;
	}

	void isSoulselectOff()
	{
		issoulselect_ = false;
	}
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
private:
	void LevelStartEvent() override;

	std::shared_ptr<class ClearUIBox> clearbox_;
	std::shared_ptr<class SoulCardSelectBox> SoulSelectbox_;
	std::shared_ptr<class Mouse> mousePointer_;
	bool issoulselect_;
};


