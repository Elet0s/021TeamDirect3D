#include "PreCompile.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineTexture.h"
#include "GameEngineDevice.h"

GameEngineRenderTarget::GameEngineRenderTarget()
	: depthTexture_(nullptr),
	depthStencilView_(nullptr),
	mergeUnit_(std::make_shared<GameEngineRenderUnit>())
{
	mergeUnit_->SetMesh("Fullrect");
	mergeUnit_->SetMaterial("TargetMerge");
}

GameEngineRenderTarget::~GameEngineRenderTarget()
{
}

std::shared_ptr<GameEngineRenderTarget> GameEngineRenderTarget::Create(const std::string_view& _name)
{
	return CreateNamedRes(_name);
}

std::shared_ptr<GameEngineRenderTarget> GameEngineRenderTarget::Create()
{
	return CreateUnnamedRes();
}

void GameEngineRenderTarget::CreateRenderTargetTexture(
	ID3D11Texture2D* _texture,
	const float4& _color
)
{
	std::shared_ptr<GameEngineTexture> newTexture = GameEngineTexture::Create(_texture);
	//_texture�� ������ newTexture�� �����Ѵ�.

	CreateRenderTargetTexture(newTexture, _color);
}

void GameEngineRenderTarget::CreateRenderTargetTexture(
	const float4& _size,
	const float4& _color
)
{
	CreateRenderTargetTexture(_size, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, _color);
}

void GameEngineRenderTarget::CreateRenderTargetTexture(
	const float4& _size,
	DXGI_FORMAT _format,
	const float4& _clearColor
)
{
	D3D11_TEXTURE2D_DESC newTextureDesc = { 0 };
	newTextureDesc.Width = _size.UIX();
	newTextureDesc.Height = _size.UIY();
	newTextureDesc.MipLevels = 1;
	newTextureDesc.ArraySize = 1;
	newTextureDesc.Format = _format;
	newTextureDesc.SampleDesc.Count = 1;
	newTextureDesc.SampleDesc.Quality = 0;
	newTextureDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	newTextureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	CreateRenderTargetTexture(newTextureDesc, _clearColor);
}

void GameEngineRenderTarget::CreateRenderTargetTexture(
	D3D11_TEXTURE2D_DESC _desc,
	const float4& _clearColor
)
{
	std::shared_ptr<GameEngineTexture> newTexture = GameEngineTexture::Create(_desc);
	CreateRenderTargetTexture(newTexture, _clearColor);
}

void GameEngineRenderTarget::CreateRenderTargetTexture(
	std::shared_ptr<GameEngineTexture> _texture,
	const float4& _clearColor
)
{
	this->renderTargets_.push_back(_texture);
	//renderTargets_�� newTexture�� �����Ѵ�.

	this->renderTargetViews_.push_back(_texture->CreateRenderTargetView());
	//newTexture���� ������ ����Ÿ�ٺ並 �����Ѵ�.

	this->shaderResourceViews_.push_back(_texture->CreateShaderResourceView());
	//newTexture���� ������ ���̴����ҽ��並 �����Ѵ�.

	this->clearColors_.push_back(_clearColor);
	//_clearColor�� �����Ѵ�.
}

std::shared_ptr<GameEngineTexture> GameEngineRenderTarget::GetRenderTargetTexture(size_t _index)
{
	if (renderTargets_.size() <= _index)
	{
		MsgBoxAssert("����Ÿ���� ������ �ʰ��� �ε����� �Է��Ͽ����ϴ�.");
		return nullptr;
	}

	return renderTargets_[_index];
}

void GameEngineRenderTarget::CreateDepthTexture(int _renderTargetIndex)
{
	D3D11_TEXTURE2D_DESC depthTextureDesc = { 0 };
	//���̽��ٽǺ� ������ �ʿ��� desc �ʱ�ȭ.

	depthTextureDesc.Width = renderTargets_[_renderTargetIndex]->GetScale().UIX();
	//���̽��ٽǺ� ���α���: _renderTargetIndex�� ����Ÿ���� ���α���.
	//�����ؼ� 0�� �ϳ��� �� ���̴�.

	depthTextureDesc.Height = renderTargets_[_renderTargetIndex]->GetScale().UIY();
	//���̽��ٽǺ� ���α���: _renderTargetIndex�� ����Ÿ���� ���α���.
	//�����ؼ� 0�� �ϳ��� �� ���̴�.

	depthTextureDesc.MipLevels = 1;
	//??

	depthTextureDesc.ArraySize = 1;
	//�ؽ�ó �迭 ũ��: 1.

	depthTextureDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
	//�ؽ�ó ����: ���� ǥ���� ����ȣ ����ȭ�� 24��Ʈ ������ ���ٽ� ǥ���� 8��Ʈ ����ȣ ����.

	depthTextureDesc.SampleDesc.Count = 1;
	//��Ƽ���ø��� ������ �ȼ��� ���� ����: 1��(���� ����).

	depthTextureDesc.SampleDesc.Quality = 0;
	//��Ƽ���ø� ǰ�� ����: 0 == ��Ƽ���ø� ����.

	depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	//�ؽ�ó ���ó: �⺻.

	depthTextureDesc.CPUAccessFlags = 0;
	//CPU�� ���� ���� ��� ����. 0: �б�/���� �Ѵ� �Ұ�. 

	depthTextureDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
	//�ؽ�ó ������: ���̽��ٽǷ� ����.

	depthTexture_ = GameEngineTexture::Create(depthTextureDesc);

	depthStencilView_ = depthTexture_->CreateDepthStencilView();
}


void GameEngineRenderTarget::SetDepthTexture(std::shared_ptr<GameEngineTexture> _depthTexture)
{
	depthTexture_ = _depthTexture;
	depthStencilView_ = depthTexture_->CreateDepthStencilView();
}

void GameEngineRenderTarget::Clear(bool _clearDepthStencilView /*= true*/)
{
	for (size_t i = 0; i < renderTargetViews_.size(); i++)
	{
		GameEngineDevice::GetDC()->ClearRenderTargetView(	//������ ����Ÿ�ٺ並 �� ������ ä��� �Լ�.
			renderTargetViews_[i],		//��� ����Ÿ�ٺ�.
			clearColors_[i].arr1D		//��� ����Ÿ�ٺ並 ĥ�� ��.
		);
	}

	if (false == _clearDepthStencilView)
	{
		return;
	}

	if (nullptr != depthStencilView_)
	{
		GameEngineDevice::GetDC()->ClearDepthStencilView(	//���� ���ٽ� �� �ʱ�ȭ�Լ�.
			depthStencilView_,						//�ʱ�ȭ ��� ���� ���ٽ� ��.
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,//���̹��� | ���ٽǹ��� �ʱ�ȭ
			1.f,									//���� �ʱⰪ.
			0										//���ٽ� �ʱⰪ.
		);
	}
}

void GameEngineRenderTarget::SetRenderTarget()
{
	if (true == renderTargetViews_.empty())
	{
		MsgBoxAssert("������ ����Ÿ�ٺ䰡 �ϳ��� �����ϴ�.");
		return;
	}

	GameEngineDevice::GetDC()->OMSetRenderTargets(		//������ ����Ÿ�ٺ並 ������ ���������ο� �����ϴ� �Լ�.
		static_cast<UINT>(renderTargetViews_.size()),	//������	����Ÿ�ٺ� ��. 0~8�� ���� ����.
		&renderTargetViews_[0],			//����Ÿ�ٺ� �迭 �ּ�.
		depthStencilView_
	);
}

void GameEngineRenderTarget::ResetRenderTarget()
{
	GameEngineDevice::GetDC()->OMSetRenderTargets(		//������ ����Ÿ�ٺ並 ������ ���������ο� �����ϴ� �Լ�.
		0,
		nullptr,
		nullptr
	);
}

void GameEngineRenderTarget::Copy(std::shared_ptr<GameEngineRenderTarget> _otherRenderTarget, int _index /*= 0*/)
{
	this->Clear();
	mergeUnit_->GetShaderResourceHelper().SetTexture("Tex", _otherRenderTarget->GetRenderTargetTexture(_index));
	Effect(mergeUnit_);
}

void GameEngineRenderTarget::Merge(std::shared_ptr<GameEngineRenderTarget> _otherRenderTarget, int _index /*= 0*/)
{
	mergeUnit_->GetShaderResourceHelper().SetTexture("Tex", _otherRenderTarget->GetRenderTargetTexture(_index));
	Effect(mergeUnit_);
}

void GameEngineRenderTarget::Effect(std::shared_ptr<GameEngineRenderUnit> _renderUnit)
{
	this->SetRenderTarget();
	_renderUnit->Render(GameEngineTime::GetDeltaTime());
}

void GameEngineRenderTarget::EffectProcess()
{
	for (std::shared_ptr<GameEnginePostEffect>& effect : allEffects_)
	{
		if (true == effect->IsUpdate())
		{
			effect->Effect(std::dynamic_pointer_cast<GameEngineRenderTarget>(shared_from_this()));
		}
	}
}
