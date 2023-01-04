#pragma once

class Mouse;
class ShaderTestLevel: public GameEngineLevel
{

public:

	ShaderTestLevel();
	~ShaderTestLevel();

	ShaderTestLevel(const ShaderTestLevel& _other) = delete;
	ShaderTestLevel(ShaderTestLevel&& _other) noexcept = delete;
	ShaderTestLevel& operator=(const ShaderTestLevel& _other) = delete;
	ShaderTestLevel& operator=(ShaderTestLevel&& _other) = delete;

public:


public:
	std::shared_ptr<Mouse> GetMouse()
	{
		return shaderTestActor_;
	}


protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;


private:
	std::shared_ptr<Mouse> shaderTestActor_;
	//std::shared_ptr<GameEngineTextureRenderer> shaderTestRenderer_;
	//std::vector<RenderOption> testRenderOptionVector_;
	//std::shared_ptr<GameEngineLighting> testLighting_;
};

