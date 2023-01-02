#pragma once

// Ό³Έν :
class RoadObject : public GameEngineActor
{
public:
	// constrcuter destructer
	RoadObject();
	~RoadObject();

	// delete Function
	RoadObject(const RoadObject& _Other) = delete;
	RoadObject(RoadObject&& _Other) noexcept = delete;
	RoadObject& operator=(const RoadObject& _Other) = delete;
	RoadObject& operator=(RoadObject&& _Other) noexcept = delete;

	std::shared_ptr<GameEngineTextureRenderer> GetRenderer()
	{
		return renderer_;
	}


	std::shared_ptr<GameEngineCollision> GetCol()
	{
		return col_;
	}
protected:

private:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;


	std::shared_ptr<GameEngineTextureRenderer> renderer_;
	std::shared_ptr<GameEngineCollision> col_;
};

