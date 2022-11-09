#include "PreCompile.h"
#include "GameEngineTexture.h"
#include "GameEngineDevice.h"
#pragma comment(lib, "DirectXTex.lib")

GameEngineTexture::GameEngineTexture()
	: texture2D_(nullptr),
	renderTargetView_(nullptr),
	shaderResourceView_(nullptr),
	depthStencilView_(nullptr),
	desc_(),
	metaData_()
{
}

GameEngineTexture::~GameEngineTexture()
{
	if (nullptr != renderTargetView_)
	{
		renderTargetView_->Release();
		renderTargetView_ = nullptr;
	}
	if (nullptr != shaderResourceView_)
	{
		shaderResourceView_->Release();
		shaderResourceView_ = nullptr;
	}
	if (nullptr != depthStencilView_)
	{
		depthStencilView_->Release();
		depthStencilView_ = nullptr;
	}

	if (nullptr != texture2D_)
	{
		texture2D_->Release();
		texture2D_ = nullptr;
	}
}

GameEngineTexture* GameEngineTexture::Create(const std::string_view& _name, ID3D11Texture2D* _texture)
{
	GameEngineTexture* newRes = CreateNamedRes(_name);
	newRes->texture2D_ = _texture;
	_texture->GetDesc(&newRes->desc_);
	return newRes;
}

GameEngineTexture* GameEngineTexture::Create(ID3D11Texture2D* _texture)
{
	GameEngineTexture* newRes = CreateUnnamedRes();
	newRes->texture2D_ = _texture;
	_texture->GetDesc(&newRes->desc_);
	return newRes;
}

GameEngineTexture* GameEngineTexture::Create(const D3D11_TEXTURE2D_DESC& _desc)
{
	GameEngineTexture* newRes = CreateUnnamedRes();
	newRes->TextureCreate(_desc);
	return newRes;
}

GameEngineTexture* GameEngineTexture::Load(const std::string_view& _path)
{
	return Load(_path, GameEnginePath::GetFileName(_path));
}

GameEngineTexture* GameEngineTexture::Load(const std::string_view& _path, const std::string_view& _name)
{
	GameEngineTexture* newRes = CreateNamedRes(_name);
	newRes->TextureLoad(_path);
	return newRes;
}

void GameEngineTexture::VSSetting(int _bindPoint)
{
	if (nullptr == this->shaderResourceView_)
	{
		MsgBoxAssert("���̴����ҽ��䰡 �����ϴ�.");
		return;
	}

	GameEngineDevice::GetContext()->VSSetShaderResources(
		_bindPoint,
		1,
		&shaderResourceView_
	);
}

void GameEngineTexture::PSSetting(int _bindPoint)
{
	if (nullptr == this->shaderResourceView_)
	{
		MsgBoxAssert("���̴����ҽ��䰡 �����ϴ�.");
		return;
	}

	GameEngineDevice::GetContext()->PSSetShaderResources(
		_bindPoint,
		1,
		&shaderResourceView_
	);
}

void GameEngineTexture::VSReset(int _bindPoint)
{
	ID3D11ShaderResourceView* emptyResourceView = nullptr;
	GameEngineDevice::GetContext()->VSSetShaderResources(
		_bindPoint,
		1,
		&emptyResourceView
	);
}

void GameEngineTexture::PSReset(int _bindPoint)
{
	ID3D11ShaderResourceView* emptyResourceView = nullptr;
	GameEngineDevice::GetContext()->PSSetShaderResources(
		_bindPoint,
		1,
		&emptyResourceView
	);
}

ID3D11RenderTargetView* GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr != renderTargetView_)
	{
		return renderTargetView_;
		//�̹� ����Ÿ�ٺ䰡 �����Ǿ� �ִٸ� �ٽ� �������� �ʰ� �����Ǿ� �ִ°��� ��ȯ�Ѵ�.
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateRenderTargetView(	//����Ÿ�ٺ並 �����ϴ� �Լ�.
		texture2D_,	//����Ÿ�ٺ䰡 �����Ǵµ� �ʿ��� ���ҽ�.
		NULL,	 //����Ÿ�ٺ並 ������ �� �ʿ��� ��������. 
		&renderTargetView_	//������� ���� ����Ÿ�ٺ� �������̽� �������� �ּ�. 
	))
	{
		MsgBoxAssert("����Ÿ�ٺ� ���� ����.");
		return nullptr;
	}

	return renderTargetView_;
}

ID3D11ShaderResourceView* GameEngineTexture::CreateShaderResourceView()
{
	if (nullptr != shaderResourceView_)
	{
		return shaderResourceView_;
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateShaderResourceView(
		texture2D_,
		nullptr,
		&shaderResourceView_
	))
	{
		MsgBoxAssert("���̴����ҽ��� ���� ����.");
		return nullptr;
	}

	return shaderResourceView_;
}

ID3D11DepthStencilView* GameEngineTexture::CreateDepthStencilView()
{
	if (nullptr != depthStencilView_)
	{
		return depthStencilView_;
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateDepthStencilView(
		texture2D_,
		nullptr,
		&depthStencilView_
	))
	{
		MsgBoxAssert("���� ���ٽ� ���� ���� ����.");
		return nullptr;
	}

	return depthStencilView_;
}

void GameEngineTexture::Cut(const std::string_view& _textureName, int _x, int _y)
{
	GameEngineTexture* findTexture = GameEngineTexture::Find(_textureName);
	if (nullptr == findTexture)
	{
		MsgBoxAssertString(std::string(_textureName) + ": �׷� �̸��� �ؽ��İ� �������� �ʽ��ϴ�.");
		return;
	}
	else
	{
		findTexture->Cut(_x, _y);
	}
}

void GameEngineTexture::Cut(UINT _startX, UINT _startY, UINT _sizeX, UINT _sizeY)
{
	float4 frameData;
	frameData.posX = _startX / this->GetScale().x;
	frameData.posY = _startY / this->GetScale().y;
	frameData.sizeX = _sizeX / this->GetScale().x;
	frameData.sizeY = _sizeY / this->GetScale().y;
	cutData_.push_back(frameData);
}

float4 GameEngineTexture::GetPixelToFloat4(int _x, int _y)
{
	PixelColor color = GetPixelToPixelColor(_x, _y);

	return float4(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
}

PixelColor GameEngineTexture::GetPixelToPixelColor(int _x, int _y)
{
	if (0 > _x)
	{
		return PixelColor();
	}

	if (0 > _y)
	{
		return PixelColor();
	}

	if (scratchImage_.GetMetadata().width <= _x)
	{
		return PixelColor();
	}

	if (scratchImage_.GetMetadata().height <= _y)
	{
		return PixelColor();
	}

	DXGI_FORMAT format = scratchImage_.GetMetadata().format;
	//������ ���� �̻��ϴٸ� ���⼭ ���� Ȯ��.

	uint8_t* color = scratchImage_.GetImages()->pixels;

	PixelColor returnColor;


	switch (format)
	{
		//case DXGI_FORMAT_R32G32B32A32_TYPELESS:
		//	break;
		//case DXGI_FORMAT_R32G32B32A32_FLOAT:
		//	break;
		//case DXGI_FORMAT_R32G32B32A32_UINT:
		//	break;
		//case DXGI_FORMAT_R32G32B32A32_SINT:
		//	break;
		//case DXGI_FORMAT_R32G32B32_TYPELESS:
		//	break;
		//case DXGI_FORMAT_R32G32B32_FLOAT:
		//	break;
		//case DXGI_FORMAT_R32G32B32_UINT:
		//	break;
		//case DXGI_FORMAT_R32G32B32_SINT:
		//	break;
		//case DXGI_FORMAT_R16G16B16A16_TYPELESS:
		//	break;
		//case DXGI_FORMAT_R16G16B16A16_FLOAT:
		//	break;
		//case DXGI_FORMAT_R16G16B16A16_UNORM:
		//	break;
		//case DXGI_FORMAT_R16G16B16A16_UINT:
		//	break;
		//case DXGI_FORMAT_R16G16B16A16_SNORM:
		//	break;
		//case DXGI_FORMAT_R16G16B16A16_SINT:
		//	break;
		//case DXGI_FORMAT_R32G32_TYPELESS:
		//	break;
		//case DXGI_FORMAT_R32G32_FLOAT:
		//	break;
		//case DXGI_FORMAT_R32G32_UINT:
		//	break;
		//case DXGI_FORMAT_R32G32_SINT:
		//	break;
		//case DXGI_FORMAT_R32G8X24_TYPELESS:
		//	break;
		//case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
		//	break;
		//case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
		//	break;
		//case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
		//	break;
		//case DXGI_FORMAT_R10G10B10A2_TYPELESS:
		//	break;
		//case DXGI_FORMAT_R10G10B10A2_UNORM:
		//	break;
		//case DXGI_FORMAT_R10G10B10A2_UINT:
		//	break;
		//case DXGI_FORMAT_R11G11B10_FLOAT:
		//	break;
		//case DXGI_FORMAT_R8G8B8A8_TYPELESS:
		//	break;

	case DXGI_FORMAT_R8G8B8A8_UNORM:
	{
		size_t index = _y * scratchImage_.GetMetadata().width + _x;
		color = color + (index * 4);

		returnColor.r = color[0];
		returnColor.g = color[1];
		returnColor.b = color[2];
		returnColor.a = color[3];
		break;
	}

	//case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	//	break;
	//case DXGI_FORMAT_R8G8B8A8_UINT:
	//	break;
	//case DXGI_FORMAT_R8G8B8A8_SNORM:
	//	break;
	//case DXGI_FORMAT_R8G8B8A8_SINT:
	//	break;
	//case DXGI_FORMAT_R16G16_TYPELESS:
	//	break;
	//case DXGI_FORMAT_R16G16_FLOAT:
	//	break;
	//case DXGI_FORMAT_R16G16_UNORM:
	//	break;
	//case DXGI_FORMAT_R16G16_UINT:
	//	break;
	//case DXGI_FORMAT_R16G16_SNORM:
	//	break;
	//case DXGI_FORMAT_R16G16_SINT:
	//	break;
	//case DXGI_FORMAT_R32_TYPELESS:
	//	break;
	//case DXGI_FORMAT_D32_FLOAT:
	//	break;
	//case DXGI_FORMAT_R32_FLOAT:
	//	break;
	//case DXGI_FORMAT_R32_UINT:
	//	break;
	//case DXGI_FORMAT_R32_SINT:
	//	break;
	//case DXGI_FORMAT_R24G8_TYPELESS:
	//	break;
	//case DXGI_FORMAT_D24_UNORM_S8_UINT:
	//	break;
	//case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
	//	break;
	//case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
	//	break;
	//case DXGI_FORMAT_R8G8_TYPELESS:
	//	break;
	//case DXGI_FORMAT_R8G8_UNORM:
	//	break;
	//case DXGI_FORMAT_R8G8_UINT:
	//	break;
	//case DXGI_FORMAT_R8G8_SNORM:
	//	break;
	//case DXGI_FORMAT_R8G8_SINT:
	//	break;
	//case DXGI_FORMAT_R16_TYPELESS:
	//	break;
	//case DXGI_FORMAT_R16_FLOAT:
	//	break;
	//case DXGI_FORMAT_D16_UNORM:
	//	break;
	//case DXGI_FORMAT_R16_UNORM:
	//	break;
	//case DXGI_FORMAT_R16_UINT:
	//	break;
	//case DXGI_FORMAT_R16_SNORM:
	//	break;
	//case DXGI_FORMAT_R16_SINT:
	//	break;
	//case DXGI_FORMAT_R8_TYPELESS:
	//	break;
	//case DXGI_FORMAT_R8_UNORM:
	//	break;
	//case DXGI_FORMAT_R8_UINT:
	//	break;
	//case DXGI_FORMAT_R8_SNORM:
	//	break;
	//case DXGI_FORMAT_R8_SINT:
	//	break;
	//case DXGI_FORMAT_A8_UNORM:
	//	break;
	//case DXGI_FORMAT_R1_UNORM:
	//	break;
	//case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
	//	break;
	//case DXGI_FORMAT_R8G8_B8G8_UNORM:
	//	break;
	//case DXGI_FORMAT_G8R8_G8B8_UNORM:
	//	break;
	//case DXGI_FORMAT_BC1_TYPELESS:
	//	break;
	//case DXGI_FORMAT_BC1_UNORM:
	//	break;
	//case DXGI_FORMAT_BC1_UNORM_SRGB:
	//	break;
	//case DXGI_FORMAT_BC2_TYPELESS:
	//	break;
	//case DXGI_FORMAT_BC2_UNORM:
	//	break;
	//case DXGI_FORMAT_BC2_UNORM_SRGB:
	//	break;
	//case DXGI_FORMAT_BC3_TYPELESS:
	//	break;
	//case DXGI_FORMAT_BC3_UNORM:
	//	break;
	//case DXGI_FORMAT_BC3_UNORM_SRGB:
	//	break;
	//case DXGI_FORMAT_BC4_TYPELESS:
	//	break;
	//case DXGI_FORMAT_BC4_UNORM:
	//	break;
	//case DXGI_FORMAT_BC4_SNORM:
	//	break;
	//case DXGI_FORMAT_BC5_TYPELESS:
	//	break;
	//case DXGI_FORMAT_BC5_UNORM:
	//	break;
	//case DXGI_FORMAT_BC5_SNORM:
	//	break;
	//case DXGI_FORMAT_B5G6R5_UNORM:
	//	break;
	//case DXGI_FORMAT_B5G5R5A1_UNORM:
	//	break;
	case DXGI_FORMAT_B8G8R8A8_UNORM:
	{
		size_t index = _y * scratchImage_.GetMetadata().width + _x;
		color = color + (index * 4);

		returnColor.r = color[2];
		returnColor.g = color[1];
		returnColor.b = color[0];
		returnColor.a = color[3];

		break;
	}
	//case DXGI_FORMAT_B8G8R8X8_UNORM:
	//	break;
	//case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
	//	break;
	//case DXGI_FORMAT_B8G8R8A8_TYPELESS:
	//	break;
	//case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	//	break;
	//case DXGI_FORMAT_B8G8R8X8_TYPELESS:
	//	break;
	//case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
	//	break;
	//case DXGI_FORMAT_BC6H_TYPELESS:
	//	break;
	//case DXGI_FORMAT_BC6H_UF16:
	//	break;
	//case DXGI_FORMAT_BC6H_SF16:
	//	break;
	//case DXGI_FORMAT_BC7_TYPELESS:
	//	break;
	//case DXGI_FORMAT_BC7_UNORM:
	//	break;
	//case DXGI_FORMAT_BC7_UNORM_SRGB:
	//	break;
	//case DXGI_FORMAT_AYUV:
	//	break;
	//case DXGI_FORMAT_Y410:
	//	break;
	//case DXGI_FORMAT_Y416:
	//	break;
	//case DXGI_FORMAT_NV12:
	//	break;
	//case DXGI_FORMAT_P010:
	//	break;
	//case DXGI_FORMAT_P016:
	//	break;
	//case DXGI_FORMAT_420_OPAQUE:
	//	break;
	//case DXGI_FORMAT_YUY2:
	//	break;
	//case DXGI_FORMAT_Y210:
	//	break;
	//case DXGI_FORMAT_Y216:
	//	break;
	//case DXGI_FORMAT_NV11:
	//	break;
	//case DXGI_FORMAT_AI44:
	//	break;
	//case DXGI_FORMAT_IA44:
	//	break;
	//case DXGI_FORMAT_P8:
	//	break;
	//case DXGI_FORMAT_A8P8:
	//	break;
	//case DXGI_FORMAT_B4G4R4A4_UNORM:
	//	break;
	//case DXGI_FORMAT_P208:
	//	break;
	//case DXGI_FORMAT_V208:
	//	break;
	//case DXGI_FORMAT_V408:
	//	break;
	//case DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE:
	//	break;
	//case DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE:
	//	break;
	//case DXGI_FORMAT_FORCE_UINT:
	//	break;

	default:
		MsgBoxAssert("�غ���� ���� �����Դϴ�.");
		break;
	}



	return returnColor;
}

void GameEngineTexture::TextureLoad(const std::string_view& _path)
{
	std::string uppercaseExtension = GameEngineString::ToUpperReturn(GameEnginePath::GetExtension(_path));

	std::wstring unicodePath = GameEngineString::AnsiToUnicodeReturn(_path);


	if (uppercaseExtension == ".TGA")
	{
		if (S_OK != DirectX::LoadFromTGAFile(
			unicodePath.c_str(),
			DirectX::TGA_FLAGS_NONE,
			&metaData_,
			scratchImage_
		))
		{
			MsgBoxAssertString(std::string(_path) + ": �ؽ��� �ε� ����.");
			return;
		}
	}
	else if (uppercaseExtension == ".DDS")
	{
		MsgBoxAssert("DDS: ���� ó�� �غ���� ���� �̹��� �����Դϴ�.");
		return;
	}
	else if (uppercaseExtension == ".PNG")
	{
		if (S_OK != DirectX::LoadFromWICFile(//
			unicodePath.c_str(),				  //
			DirectX::WIC_FLAGS_NONE,			  //
			&metaData_,							  //
			scratchImage_						  //
		))
		{
			MsgBoxAssertString(std::string(_path) + ": �ؽ��� �ε� ����.");
			return;
		}
	}


	//GameEngineDevice::GetDevice()->CreateShaderResourceView(); ������� ����.
	//��� �� ���� DirectXTex�� ���̴����ҽ��� �����Լ� ���.

	if (S_OK != DirectX::CreateShaderResourceView(//
		GameEngineDevice::GetDevice(),			  //
		scratchImage_.GetImages(),				  //
		scratchImage_.GetImageCount(),			  //
		scratchImage_.GetMetadata(),			  //
		&shaderResourceView_					  //
	))
	{
		MsgBoxAssertString(std::string(_path) + ": ���̴� ���ҽ� ���� ����.");
		return;
	}

	desc_.Width = static_cast<UINT>(metaData_.width);
	desc_.Height = static_cast<UINT>(metaData_.height);
}

void GameEngineTexture::TextureCreate(const D3D11_TEXTURE2D_DESC& _desc)
{
	desc_ = _desc;

	if (S_OK != GameEngineDevice::GetDevice()->CreateTexture2D(
		&desc_,	//�ؽ�ó2D ������ ����.
		nullptr,			//�ؽ�ó ������ �ʿ��� �ʱⵥ����.
		&texture2D_			//������ �ؽ�ó�� ���� ID3D11Texture2D �������̽� ������.
	))
	{
		MsgBoxAssert("�ؽ�ó ���� ����.");
		return;
	}

}

void GameEngineTexture::Cut(int _x, int _y)
{
	float sizeX = 1.f / _x;
	float sizeY = 1.f / _y;

	float4 cuttingStart = float4::Zero;

	for (int y = 0; y < _y; y++)
	{
		for (int x = 0; x < _x; x++)
		{
			float4 frameData;
			frameData.posX = cuttingStart.x;
			frameData.posY = cuttingStart.y;
			frameData.sizeX = sizeX;
			frameData.sizeY = sizeY;
			cutData_.push_back(frameData);

			cuttingStart.x += sizeX;
		}

		cuttingStart.x = 0.f;
		cuttingStart.y += sizeY;
	}


}
