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

GameEngineMaterial* GameEngineMaterial::Create(const std::string& _renderingPipeLineName)
{
	return CreateNamedRes(_renderingPipeLineName);
}

GameEngineMaterial* GameEngineMaterial::Create()
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

void GameEngineMaterial::SetVertexShader(const std::string& _name)
{
	this->vertexShader_ = GameEngineVertexShader::Find(_name);

	if (nullptr == vertexShader_)
	{
		MsgBoxAssertString(_name + ": �׷� �̸��� ���ؽ����̴��� �������� �ʽ��ϴ�.");
		return;
	}
}

void GameEngineMaterial::SetVertexShader(GameEngineVertexShader* _vertexShader)
{
	this->vertexShader_ = _vertexShader;

	if (nullptr == vertexShader_)
	{
		MsgBoxAssert("���ؽ����̴��� �������� �ʽ��ϴ�.");
		return;
	}
}

void GameEngineMaterial::SetRasterizer(const std::string& _name)
{
	this->rasterizer_ = GameEngineRasterizer::Find(_name);

	if (nullptr == rasterizer_)
	{
		MsgBoxAssertString(_name + ": �׷� �̸��� �����Ͷ������� �������� �ʽ��ϴ�.");
		return;
	}
}

void GameEngineMaterial::SetPixelShader(const std::string& _name)
{
	this->pixelShader_ = GameEnginePixelShader::Find(_name);

	if (nullptr == pixelShader_)
	{
		MsgBoxAssertString(_name + ": �׷� �̸��� �ȼ����̴��� �������� �ʽ��ϴ�.");
		return;
	}
}

void GameEngineMaterial::SetDepthStencil_OutputMerger(const std::string& _name)
{
	this->depthStencil_ = GameEngineDepthStencil::Find(_name);

	if (nullptr == depthStencil_)
	{
		MsgBoxAssertString(_name + ": �׷� �̸��� ���̽��ٽ��� �������� �ʽ��ϴ�.");
		return;
	}
}

void GameEngineMaterial::SetBlend_OutputMerger(const std::string& _name)
{
	this->blend_ = GameEngineBlend::Find(_name);

	if (nullptr == blend_)
	{
		MsgBoxAssertString(_name + ": �׷� �̸��� ���尡 �������� �ʽ��ϴ�.");
		return;
	}
}

void GameEngineMaterial::RenderInstancing(
	int _renderingCount,
	GameEngineInstancingBuffer* _instancingBuffer
)
{
	InputAssembler1_InstancingBufferSetting(_instancingBuffer);
	VertexShaderSetting();
	RasterizerSetting();
	PixelShaderSetting();
	OutputMerger_BlendSetting();
	OutputMerger_DepthStencilSetting();

	//��� ������ ���ҽ� ������ ���� �Ŀ� �������� �Ѵ�.
	this->InstancingDraw(_renderingCount);
}

void GameEngineMaterial::Copy(GameEngineMaterial* _original)
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

void GameEngineMaterial::InputAssembler1_InstancingBufferSetting(GameEngineInstancingBuffer* _instancingBuffer)
{
	//// �׷��ȸ��ҽ��� Setting�̶�� �Լ��� �����Ѵٸ�
	//// �װ� �������� �� �������� ������ ������������ ���ư��� �ȴٴ� ���� �˴ϴ�.
	//this->inputLayout_->Setting();
	//// ���ؽ� ���۴� �����Ұ� ����.

	//ID3D11Buffer* arrBuffer[2] = { this->vertexBuffer_->GetBuffer(), _instancingBuffer->GetBuffer() };
	//unsigned int arrVertexSize[2] = { this->vertexBuffer_->GetVertexSize(), _instancingBuffer->GetDataSize() };
	//unsigned int arrOffset[2] = { 0, 0 };

	//GameEngineDevice::GetContext()->IASetVertexBuffers(
	//	0,				// ���ؽ� ���۸� ���������ͷ� �������������� ������ �ε���
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
	//[in] IndexCountPerInstance ���� : UINT
	//�� �ν��Ͻ��� ���� �ε��� ���ۿ��� ���� �ε��� ���Դϴ�.

	//[in] InstanceCount ���� : UINT
	//�׸� �ν��Ͻ� ���Դϴ�.

	//[in] StartIndexLocation
	//���� : UINT GPU�� �ε��� ���ۿ��� ���� ù ��° �ε����� ��ġ�Դϴ�.

	//[in] BaseVertexLocation ���� : ����
	//���� ���ۿ��� ������ �б� ���� �� �ε����� �߰��� ���Դϴ�.

	//[in] StartInstanceLocation ���� : UINT
	//���� ���ۿ��� �ν��Ͻ��� �����͸� �б� ���� �� �ε����� �߰��� ���Դϴ�.

	// �׳� 4�� ����.
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
