#pragma once

class Mouse;
class FieldRenderingActor;
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
	//std::shared_ptr<Mouse> GetMouse()
	//{
	//	return shaderTestActor_;
	//}


protected:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	void LevelStartEvent() override;

private:
	//Mouse* shaderTestActor_;
	FieldRenderingActor* shaderTestActor_;
	GameEngineLighting* lighting_;

	D3D11_TEXTURE2D_DESC testTextureDesc_;
	GameEngineTexture* testTexture_;
	D3D11_UNORDERED_ACCESS_VIEW_DESC testUAVDesc_;
};

