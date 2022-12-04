#include "PreCompile.h"
#include "GameEngineMaterial.h"
#include "GameEngineDevice.h"
#include "GameEngineInputLayout.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineInstancingBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineDepthStencil.h"
#include "GameEngineBlend.h"


GameEngineMaterial::GameEngineMaterial()
	: vertexShader_(nullptr),
	rasterizer_(nullptr),
	pixelShader_(nullptr),
	depthStencil_(nullptr),
	blend_(nullptr)
{

}

GameEngineMaterial::~GameEngineMaterial()
{
}

std::shared_ptr<GameEngineMaterial> GameEngineMaterial::Create(const std::string_view& _materialName)
{
	return CreateNamedRes(_materialName);
}

std::shared_ptr<GameEngineMaterial> GameEngineMaterial::Create()
{
	return CreateUnnamedRes();
}

void GameEngineMaterial::AllShaderReset()
{
	GameEngineDevice::GetContext()->VSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->HSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->DSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->GSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->PSSetShader(nullptr, nullptr, 0);
}

void GameEngineMaterial::SetVertexShader(const std::string_view& _name)
{
	this->vertexShader_ = GameEngineVertexShader::Find(_name);

	if (nullptr == vertexShader_)
	{
		MsgBoxAssertString(std::string(_name) + ": 그런 이름의 버텍스셰이더가 존재하지 않습니다.");
		return;
	}
}

void GameEngineMaterial::SetVertexShader(std::shared_ptr<GameEngineVertexShader> _vertexShader)
{
	this->vertexShader_ = _vertexShader;

	if (nullptr == vertexShader_)
	{
		MsgBoxAssert("버텍스셰이더가 존재하지 않습니다.");
		return;
	}
}

void GameEngineMaterial::SetRasterizer(const std::string_view& _name)
{
	this->rasterizer_ = GameEngineRasterizer::Find(_name);

	if (nullptr == rasterizer_)
	{
		MsgBoxAssertString(std::string(_name) + ": 그런 이름의 래스터라이저가 존재하지 않습니다.");
		return;
	}
}

void GameEngineMaterial::SetPixelShader(const std::string_view& _name)
{
	this->pixelShader_ = GameEnginePixelShader::Find(_name);

	if (nullptr == pixelShader_)
	{
		MsgBoxAssertString(std::string(_name) + ": 그런 이름의 픽셀셰이더가 존재하지 않습니다.");
		return;
	}
}

void GameEngineMaterial::SetDepthStencil_OutputMerger(const std::string_view& _name)
{
	this->depthStencil_ = GameEngineDepthStencil::Find(_name);

	if (nullptr == depthStencil_)
	{
		MsgBoxAssertString(std::string(_name) + ": 그런 이름의 깊이스텐실이 존재하지 않습니다.");
		return;
	}
}

void GameEngineMaterial::SettingInstancing()
{
	Inst_VertexShaderSetting();
	RasterizerSetting();
	PixelShaderSetting();
	OutputMerger_DepthStencilSetting();
	OutputMerger_BlendSetting();
}

void GameEngineMaterial::SettingInstancing2()
{
	Inst_VertexShaderSetting();
	RasterizerSetting();
	Inst_PixelShaderSetting();
	OutputMerger_DepthStencilSetting();
	OutputMerger_BlendSetting();
}

void GameEngineMaterial::SetBlend_OutputMerger(const std::string_view& _name)
{
	this->blend_ = GameEngineBlend::Find(_name);

	if (nullptr == blend_)
	{
		MsgBoxAssertString(std::string(_name) + ": 그런 이름의 블렌드가 존재하지 않습니다.");
		return;
	}
}

void GameEngineMaterial::Copy(std::shared_ptr<GameEngineMaterial> _original)
{
	this->vertexShader_ = _original->vertexShader_;
	this->rasterizer_ = _original->rasterizer_;
	this->pixelShader_ = _original->pixelShader_;
	this->depthStencil_ = _original->depthStencil_;
	this->blend_ = _original->blend_;
}

void GameEngineMaterial::Setting()
{
	VertexShaderSetting();
	RasterizerSetting();
	PixelShaderSetting();
	OutputMerger_DepthStencilSetting();
	OutputMerger_BlendSetting();
}

void GameEngineMaterial::VertexShaderSetting()
{
	this->vertexShader_->Setting();
}

void GameEngineMaterial::Inst_VertexShaderSetting()
{
	this->vertexShader_->GetInst_VertexShader()->Setting();
}

void GameEngineMaterial::RasterizerSetting()
{
	this->rasterizer_->Setting();
}

void GameEngineMaterial::PixelShaderSetting()
{
	this->pixelShader_->Setting();
}

void GameEngineMaterial::Inst_PixelShaderSetting()
{
	this->pixelShader_->GetInst_PixelShader()->Setting();
}

void GameEngineMaterial::OutputMerger_BlendSetting()
{
	this->blend_->Setting();
}

void GameEngineMaterial::OutputMerger_DepthStencilSetting()
{
	this->depthStencil_->Setting();
}