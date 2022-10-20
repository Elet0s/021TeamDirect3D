#pragma once

class GameEngineCamera;
class LoginUI: public GameEngineActor
{
	GameEngineTextureRenderer* uiRenderer_;


public:

	LoginUI();
	~LoginUI();

	LoginUI(const LoginUI& _other) = delete;
	LoginUI(LoginUI&& _other) noexcept = delete;
	LoginUI& operator=(const LoginUI& _other) = delete;
	LoginUI& operator=(LoginUI&& _other) = delete;

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;

private:
	void OnEvent() override;
};

