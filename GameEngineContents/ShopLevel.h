#pragma once

// Ό³Έν :
class ShopLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	ShopLevel();
	~ShopLevel();

	// delete Function
	ShopLevel(const ShopLevel& _Other) = delete;
	ShopLevel(ShopLevel&& _Other) noexcept = delete;
	ShopLevel& operator=(const ShopLevel& _Other) = delete;
	ShopLevel& operator=(ShopLevel&& _Other) noexcept = delete;

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
	std::shared_ptr<class ShopUIBox> shopUIBox_;
	std::shared_ptr<class StageUI> stageui_;
};

