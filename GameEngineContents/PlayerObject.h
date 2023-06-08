#pragma once

enum class PlayerObjectMode
{
	Idle,
	Move,
	Max,
};

// Ό³Έν :
class PlayerObject : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerObject();
	~PlayerObject();

	// delete Function
	PlayerObject(const PlayerObject& _Other) = delete;
	PlayerObject(PlayerObject&& _Other) noexcept = delete;
	PlayerObject& operator=(const PlayerObject& _Other) = delete;
	PlayerObject& operator=(PlayerObject&& _Other) noexcept = delete;

	void SetMoveDir(float4 _dir);
	
	bool IsObjectIdle()
	{
		if (mode_ == PlayerObjectMode::Idle)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
protected:

private:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

	void LevelStartEvent() override;

	float4 moveDir_;
	float4 checkPos_;
	PlayerObjectMode mode_;
	GameEngineTextureRenderer* renderer_;
	//GameEngineCollision* col_;
};

