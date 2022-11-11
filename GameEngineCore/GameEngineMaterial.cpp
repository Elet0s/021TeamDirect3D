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

void GameEngineMaterial::SetBlend_OutputMerger(const std::string_view& _name)
{
	this->blend_ = GameEngineBlend::Find(_name);

	if (nullptr == blend_)
	{
		MsgBoxAssertString(std::string(_name) + ": 그런 이름의 블렌드가 존재하지 않습니다.");
		return;
	}
}

void GameEngineMaterial::RenderInstancing(
	int _renderingCount,
	std::shared_ptr<GameEngineInstancingBuffer> _instancingBuffer
)
{
	InputAssembler1_InstancingBufferSetting(_instancingBuffer);
	VertexShaderSetting();
	RasterizerSetting();
	PixelShaderSetting();
	OutputMerger_BlendSetting();
	OutputMerger_DepthStencilSetting();

	//모든 렌더링 리소스 세팅이 끝난 후에 렌더링을 한다.
	this->InstancingDraw(_renderingCount);
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

void GameEngineMaterial::InputAssembler1_InstancingBufferSetting(std::shared_ptr<GameEngineInstancingBuffer> _instancingBuffer)
{
	//// 그래픽리소스에 Setting이라는 함수가 존재한다면
	//// 그건 이제부터 그 설정으로 랜더링 파이프라인이 돌아가게 된다는 뜻이 됩니다.
	//this->inputLayout_->Setting();
	//// 버텍스 버퍼는 세팅할게 없다.

	//ID3D11Buffer* arrBuffer[2] = { this->vertexBuffer_->GetBuffer(), _instancingBuffer->GetBuffer() };
	//unsigned int arrVertexSize[2] = { this->vertexBuffer_->GetVertexSize(), _instancingBuffer->GetDataSize() };
	//unsigned int arrOffset[2] = { 0, 0 };

	//GameEngineDevice::GetContext()->IASetVertexBuffers(
	//	0,				// 버텍스 버퍼를 이중포인터로 세팅해줬을대의 사용시작 인덱스
	//	2,
	//	arrBuffer,
	//	arrVertexSize,
	//	arrOffset
	//);
}

void GameEngineMaterial::VertexShaderSetting()
{
	this->vertexShader_->Setting();
}

void GameEngineMaterial::RasterizerSetting()
{
	this->rasterizer_->Setting();
}

void GameEngineMaterial::PixelShaderSetting()
{
	this->pixelShader_->Setting();
}

void GameEngineMaterial::OutputMerger_BlendSetting()
{
	this->blend_->Setting();
}

void GameEngineMaterial::OutputMerger_DepthStencilSetting()
{
	this->depthStencil_->Setting();
}

void GameEngineMaterial::InstancingDraw(int _renderingCount)
{
	//[in] IndexCountPerInstance 유형 : UINT
	//각 인스턴스에 대해 인덱스 버퍼에서 읽은 인덱스 수입니다.

	//[in] InstanceCount 유형 : UINT
	//그릴 인스턴스 수입니다.

	//[in] StartIndexLocation
	//유형 : UINT GPU가 인덱스 버퍼에서 읽은 첫 번째 인덱스의 위치입니다.

	//[in] BaseVertexLocation 유형 : 지능
	//정점 버퍼에서 정점을 읽기 전에 각 인덱스에 추가된 값입니다.

	//[in] StartInstanceLocation 유형 : UINT
	//정점 버퍼에서 인스턴스별 데이터를 읽기 전에 각 인덱스에 추가된 값입니다.

	// 그냥 4가 들어간다.
	//GameEngineDevice::GetContext()->DrawIndexedInstanced(
	//	this->indexBuffer_->GetIndexCount(),
	//	_renderingCount,
	//	0,
	//	0,
	//	0
	//);
}

void GameEngineMaterial::InstancingDataCollect()
{
}
