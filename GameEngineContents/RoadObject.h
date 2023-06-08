#pragma once

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

	GameEngineTextureRenderer* GetRenderer()
	{
		return renderer_;
	}


	GameEngineCollision* GetCol()
	{
		return col_;
	}
protected:

private:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;


	GameEngineTextureRenderer* renderer_;
	GameEngineCollision* col_;
};

