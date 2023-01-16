#pragma once

// Ό³Έν :
class StageClearMap : public GameEngineActor
{
public:
	// constrcuter destructer
	StageClearMap();
	~StageClearMap();

	// delete Function
	StageClearMap(const StageClearMap& _Other) = delete;
	StageClearMap(StageClearMap&& _Other) noexcept = delete;
	StageClearMap& operator=(const StageClearMap& _Other) = delete;
	StageClearMap& operator=(StageClearMap&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

private:
	const float tileSize_;

	const float4 tileCountXY_;

	const int tileCount_;

	GameEngineInstancingRenderer* mapRenderer_;
};

