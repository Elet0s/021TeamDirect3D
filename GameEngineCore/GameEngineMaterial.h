#pragma once
#include "GameEngineRes.h"

class GameEngineInputLayout;
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineIndexBuffer;
class GameEngineRasterizer;
class GameEnginePixelShader;
class GameEngineDepthStencil;
class GameEngineBlend;
class GameEngineMaterial : public GameEngineRes<GameEngineMaterial>
{
	//이 클래스의 존재 이유: 셰이더와 셰이더리소스, 래스터라이저와 블렌드, 깊이스텐실을 가지고 
	// 렌더링 과정에 관여하는 클래스.

public:
	GameEngineMaterial();
	~GameEngineMaterial();

protected:
	GameEngineMaterial(const GameEngineMaterial& _other) = delete;
	GameEngineMaterial(GameEngineMaterial&& _other) noexcept = delete;

private:
	GameEngineMaterial& operator=(const GameEngineMaterial& _other) = delete;
	GameEngineMaterial& operator=(const GameEngineMaterial&& _other) = delete;


public:

	static std::shared_ptr<GameEngineMaterial> Create(const std::string_view& _materialName);
	static std::shared_ptr<GameEngineMaterial> Create();
	static void AllShaderReset();

public:
	//세팅 준비 함수들.

	void SetVertexShader(const std::string_view& _name);
	void SetVertexShader(std::shared_ptr<GameEngineVertexShader> _vertexShader);

	void SetRasterizer(const std::string_view& _name);
	void SetPixelShader(const std::string_view& _name);
	void SetBlend_OutputMerger(const std::string_view& _name);
	void SetDepthStencil_OutputMerger(const std::string_view& _name);
	void SettingInstancing();
	void Copy(std::shared_ptr<GameEngineMaterial> _original);

	void Setting();
public:

	inline std::shared_ptr<GameEngineVertexShader> GetVertexShader()
	{
		return this->vertexShader_;
	}
	inline std::shared_ptr<GameEnginePixelShader> GetPixelShader()
	{
		return this->pixelShader_;
	}

private:
	//세팅 함수들.
	//실질적으로 세팅 순서는 그다지 중요하지 않다. DrawIndexed() 함수 호출 이전까지만 모든 세팅이 끝나있으면 된다.

	void VertexShaderSetting();
	void Inst_VertexShaderSetting();
	void RasterizerSetting();
	void PixelShaderSetting();
	void OutputMerger_DepthStencilSetting();
	void OutputMerger_BlendSetting();


private:
	std::shared_ptr<GameEngineVertexShader> vertexShader_;

	std::shared_ptr<GameEngineRasterizer> rasterizer_;

	std::shared_ptr<GameEnginePixelShader> pixelShader_;

	std::shared_ptr<GameEngineDepthStencil> depthStencil_;

	std::shared_ptr<GameEngineBlend> blend_;

};

