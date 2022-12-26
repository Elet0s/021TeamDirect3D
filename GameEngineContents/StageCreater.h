#pragma once

// Ό³Έν :
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
	bool CheckPushLevel();


	std::map<int, std::list<std::shared_ptr<class StageObject>>> stageObjects_;
};

