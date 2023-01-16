#pragma once

// Ό³Έν :
class TreeObject : public GameEngineActor
{
public:
	// constrcuter destructer
	TreeObject();
	~TreeObject();

	// delete Function
	TreeObject(const TreeObject& _Other) = delete;
	TreeObject(TreeObject&& _Other) noexcept = delete;
	TreeObject& operator=(const TreeObject& _Other) = delete;
	TreeObject& operator=(TreeObject&& _Other) noexcept = delete;


	GameEngineTextureRenderer* GetRenderer()
	{
		return renderer_;
	}


	GameEngineCollision* GetCheckCol()
	{
		return checkCol_;
	}
protected:

private:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;


	GameEngineTextureRenderer* renderer_;
	GameEngineCollision* col_;
	GameEngineCollision* checkCol_;
};

