#pragma once

// Ό³Έν :
class PlayerObject;
class StageCreater : public GameEngineActor
{
public:
	// constrcuter destructer
	StageCreater();
	~StageCreater();

	// delete Function
	StageCreater(const StageCreater& _Other) = delete;
	StageCreater(StageCreater&& _Other) noexcept = delete;
	StageCreater& operator=(const StageCreater& _Other) = delete;
	StageCreater& operator=(StageCreater&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _deltaTime) override;
	CollisionReturn CheckNextLevel(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

	std::shared_ptr<class StageObject> curlevel_;
	std::shared_ptr<PlayerObject> playerObject_;
	std::map<int, std::list<std::shared_ptr<class StageObject>>> stageObjects_;
};

