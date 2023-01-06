#pragma once

// Ό³Έν :
class SoulCardUI;
class SoulCardSelectBox : public GameEngineActor
{
public:
	// constrcuter destructer
	SoulCardSelectBox();
	~SoulCardSelectBox();

	// delete Function
	SoulCardSelectBox(const SoulCardSelectBox& _Other) = delete;
	SoulCardSelectBox(SoulCardSelectBox&& _Other) noexcept = delete;
	SoulCardSelectBox& operator=(const SoulCardSelectBox& _Other) = delete;
	SoulCardSelectBox& operator=(SoulCardSelectBox&& _Other) noexcept = delete;
	
protected:

private:
	std::shared_ptr<SoulCardUI> Cards[3];
	

	void Start() override;
	void Update(float _deltaTime) override;
	void End() override {};
};

