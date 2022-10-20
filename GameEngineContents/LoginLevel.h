#pragma once


class LoginLevel: public GameEngineLevel
{



public:

	LoginLevel();
	~LoginLevel();

	LoginLevel(const LoginLevel& _other) = delete;
	LoginLevel(LoginLevel&& _other) noexcept = delete;
	LoginLevel& operator=(const LoginLevel& _other) = delete;
	LoginLevel& operator=(LoginLevel&& _other) = delete;

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

private:
	void LevelStartEvent() override;

};

