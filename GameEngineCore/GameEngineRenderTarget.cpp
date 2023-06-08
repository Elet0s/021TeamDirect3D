#include "PreCompile.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineTexture.h"
#include "GameEngineDevice.h"

GameEngineRenderTarget::GameEngineRenderTarget()
	: depthTexture_(nullptr),
	depthStencilView_(nullptr)
{
	mergeUnit_.SetMesh("Fullrect");
	mergeUnit_.SetMaterial("TargetMerge");
}

GameEngineRenderTarget::~GameEngineRenderTarget()
{
	for (GameEnginePostEffect* effect : allEffects_)
	{
		delete effect;
		effect = nullptr;
	}

	allEffects_.clear();
}

GameEngineRenderTarget* GameEngineRenderTarget::Create(const std::string_view& _name)
{
	return CreateNamedRes(_name);
}

GameEngineRenderTarget* GameEngineRenderTarget::Create()
{
	return CreateUnnamedRes();
}

void GameEngineRenderTarget::CreateRenderTargetTexture(
	ID3D11Texture2D* _texture,
	const float4& _color
)
{
	GameEngineTexture* newTexture = GameEngineTexture::Create(_texture);
	//_texture를 저장할 newTexture를 생성한다.

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
	GameEngineTexture* newTexture = GameEngineTexture::Create(_desc);
	CreateRenderTargetTexture(newTexture, _clearColor);
}

void GameEngineRenderTarget::CreateRenderTargetTexture(
	GameEngineTexture* _texture,
	const float4& _clearColor
)
{
	this->renderTargetTextures_.push_back(_texture);
	//renderTargetTextures_에 newTexture를 저장한다.

	this->renderTargetViews_.push_back(_texture->CreateRenderTargetView());
	//newTexture에서 생성한 렌더타겟뷰를 저장한다.

	this->shaderResourceViews_.push_back(_texture->CreateShaderResourceView());
	//newTexture에서 생성한 셰이더리소스뷰를 저장한다.

	this->clearColors_.push_back(_clearColor);
	//_clearColor도 저장한다.
}

GameEngineTexture* GameEngineRenderTarget::GetRenderTargetTexture(size_t _index)
{
	if (renderTargetTextures_.size() <= _index)
	{
		MsgBoxAssert("렌더타겟의 개수를 초과한 인덱스를 입력하였습니다.");
		return nullptr;
	}

	return renderTargetTextures_[_index];
}

void GameEngineRenderTarget::CreateDepthTexture(int _renderTargetIndex)
{
	D3D11_TEXTURE2D_DESC depthTextureDesc = { 0 };
	//깊이스텐실뷰 생성에 필요한 desc 초기화.

	depthTextureDesc.Width = renderTargetTextures_[_renderTargetIndex]->GetScale().UIX();
	//깊이스텐실뷰 가로길이: _renderTargetIndex번 렌더타겟의 가로길이.
	//웬만해선 0번 하나만 쓸 것이다.

	depthTextureDesc.Height = renderTargetTextures_[_renderTargetIndex]->GetScale().UIY();
	//깊이스텐실뷰 세로길이: _renderTargetIndex번 렌더타겟의 세로길이.
	//웬만해선 0번 하나만 쓸 것이다.

	depthTextureDesc.MipLevels = 1;
	//??

	depthTextureDesc.ArraySize = 1;
	//텍스처 배열 크기: 1.

	depthTextureDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
	//텍스처 형식: 깊이 표현용 무부호 정규화된 24비트 정수와 스텐실 표현용 8비트 무부호 정수.

	depthTextureDesc.SampleDesc.Count = 1;
	//멀티샘플링에 참조할 픽셀당 샘플 개수: 1개(참조 안함).

	depthTextureDesc.SampleDesc.Quality = 0;
	//멀티샘플링 품질 수준: 0 == 멀티샘플링 안함.

	depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	//텍스처 사용처: 기본.

	depthTextureDesc.CPUAccessFlags = 0;
	//CPU의 버퍼 접근 허용 여부. 0: 읽기/쓰기 둘다 불가. 

	depthTextureDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
	//텍스처 연결방식: 깊이스텐실로 연결.

	depthTexture_ = GameEngineTexture::Create(depthTextureDesc);

	depthStencilView_ = depthTexture_->CreateDepthStencilView();
}


void GameEngineRenderTarget::SetDepthTexture(GameEngineTexture* _depthTexture)
{
	depthTexture_ = _depthTexture;
	depthStencilView_ = depthTexture_->CreateDepthStencilView();
}

void GameEngineRenderTarget::Clear(bool _clearDepthStencilView /*= true*/)
{
	for (size_t i = 0; i < renderTargetViews_.size(); i++)
	{
		GameEngineDevice::GetDC()->ClearRenderTargetView(	//지정한 렌더타겟뷰를 한 색으로 채우는 함수.
			renderTargetViews_[i],		//대상 렌더타겟뷰.
			clearColors_[i].arr1D		//대상 렌더타겟뷰를 칠할 색.
		);
	}

	if (false == _clearDepthStencilView)
	{
		return;
	}

	if (nullptr != depthStencilView_)
	{
		GameEngineDevice::GetDC()->ClearDepthStencilView(	//깊이 스텐실 뷰 초기화함수.
			depthStencilView_,						//초기화 대상 깊이 스텐실 뷰.
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,//깊이버퍼 | 스텐실버퍼 초기화
			1.f,									//깊이 초기값.
			0										//스텐실 초기값.
		);
	}
}

void GameEngineRenderTarget::SetRenderTarget()
{
	if (true == renderTargetViews_.empty())
	{
		MsgBoxAssert("세팅할 렌더타겟뷰가 하나도 없습니다.");
		return;
	}

	GameEngineDevice::GetDC()->OMSetRenderTargets(		//지정한 렌더타겟뷰를 렌더링 파이프라인에 연결하는 함수.
		static_cast<UINT>(renderTargetViews_.size()),	//연결할	렌더타겟뷰 수. 0~8개 지정 가능.
		&renderTargetViews_[0],			//렌더타겟뷰 배열 주소.
		depthStencilView_
	);
}

void GameEngineRenderTarget::ResetRenderTarget()
{
	GameEngineDevice::GetDC()->OMSetRenderTargets(		//지정한 렌더타겟뷰를 렌더링 파이프라인에 연결하는 함수.
		0,
		nullptr,
		nullptr
	);
}

void GameEngineRenderTarget::Copy(GameEngineRenderTarget* _otherRenderTarget, int _index /*= 0*/)
{
	this->Clear();
	mergeUnit_.GetShaderResourceHelper().SetTexture("Tex", _otherRenderTarget->GetRenderTargetTexture(_index));
	Effect(mergeUnit_);
}

void GameEngineRenderTarget::Merge(GameEngineRenderTarget* _otherRenderTarget, int _index /*= 0*/)
{
	mergeUnit_.GetShaderResourceHelper().SetTexture("Tex", _otherRenderTarget->GetRenderTargetTexture(_index));
	Effect(mergeUnit_);
}

void GameEngineRenderTarget::Effect(GameEngineRenderUnit& _renderUnit)
{
	this->SetRenderTarget();
	_renderUnit.Render(GameEngineTime::GetInst().GetDeltaTime());
}

void GameEngineRenderTarget::EffectProcess()
{
	for (GameEnginePostEffect* effect : allEffects_)
	{
		if (true == effect->IsUpdate())
		{
			effect->Effect(this);
		}
	}
}
