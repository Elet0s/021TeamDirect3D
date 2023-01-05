#pragma once

class TestActor : public GameEngineActor
{
public:
	TestActor();
	~TestActor();

	TestActor(const TestActor& _Other) = delete;
	TestActor(TestActor&& _Other) noexcept = delete;
	TestActor& operator=(const TestActor& _Other) = delete;
	TestActor& operator=(TestActor&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
private:
	std::shared_ptr<GameEngineCollision> mouseCollision01_;
	std::shared_ptr<GameEngineCollision> mouseCollision02_;
	std::shared_ptr<GameEngineCollision> mouseCollision03_;

	bool A;
};