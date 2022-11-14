#pragma once

class Texture2DShadowRenderer;
class ShaderTestLevel: public GameEngineLevel
{



public:

	ShaderTestLevel();
	~ShaderTestLevel();

	ShaderTestLevel(const ShaderTestLevel& _other) = delete;
	ShaderTestLevel(ShaderTestLevel&& _other) noexcept = delete;
	ShaderTestLevel& operator=(const ShaderTestLevel& _other) = delete;
	ShaderTestLevel& operator=(ShaderTestLevel&& _other) = delete;

protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;


private:
	std::shared_ptr<GameEngineActor> shaderTestActor_;
	std::shared_ptr<Texture2DShadowRenderer> shaderTestRenderer_;

};

