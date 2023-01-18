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
	//�� Ŭ������ ���� ����: ���̴��� ���̴����ҽ�, �����Ͷ������� ����, ���̽��ٽ��� ������ 
	// ������ ������ �����ϴ� Ŭ����.

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

	static GameEngineMaterial* Create(const std::string_view& _materialName);
	static GameEngineMaterial* Create();
	static void AllShaderReset();

public:
	//���� �غ� �Լ���.

	void SetVertexShader(const std::string_view& _name);
	void SetVertexShader(GameEngineVertexShader* _vertexShader);

	void SetRasterizer(const std::string_view& _name);
	void SetPixelShader(const std::string_view& _name);
	void SetBlend_OutputMerger(const std::string_view& _name);
	void SetDepthStencil_OutputMerger(const std::string_view& _name);
	void Copy(GameEngineMaterial* _original);

	void Set();
	void SettingInstancing();
	void SettingInstancing2();
public:

	inline GameEngineVertexShader* GetVertexShader()
	{
		return this->vertexShader_;
	}
	inline GameEnginePixelShader* GetPixelShader()
	{
		return this->pixelShader_;
	}

private:
	//���� �Լ���.
	//���������� ���� ������ �״��� �߿����� �ʴ�. DrawIndexed() �Լ� ȣ�� ���������� ��� ������ ���������� �ȴ�.

	void VertexShaderSetting();
	void Inst_VertexShaderSetting();
	void RasterizerSetting();
	void PixelShaderSetting();
	void Inst_PixelShaderSetting();
	void OutputMerger_DepthStencilSetting();
	void OutputMerger_BlendSetting();


private:
	GameEngineVertexShader* vertexShader_;

	GameEngineRasterizer* rasterizer_;

	GameEnginePixelShader* pixelShader_;

	GameEngineDepthStencil* depthStencil_;

	GameEngineBlend* blend_;

};

