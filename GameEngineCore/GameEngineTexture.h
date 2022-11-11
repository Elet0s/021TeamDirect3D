#pragma once
#include "GameEngineRes.h"
#include <DirectXTex.h>

struct PixelColor
{
	union
	{
		struct
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		};

		unsigned int color_;
	};

	PixelColor() : color_(0)
	{
	}
};

class GameEngineTexture : public GameEngineRes<GameEngineTexture>
{
	//ID3D11Texture2D* ���·� �Ҵ�� �ؽ��Ŀ� �ű⼭ �Ļ��� ���� ���긮�ҽ������ ����, �����ϱ� ���� Ŭ����.
	//�ڱ� �ؽ��Ŀ� ����� ���ҽ����'��' �����ϴ� Ŭ����.
	//������ ���������ο� ���ҽ������ �����ϴ°� �ش� ���ҽ��� Ŭ�������� �Ѵ�.

	//���ҽ�: ������ �������� ���Ǵ� ��� �Ǽ� �迭 �����͸� ���Ѵ�. ũ�� �ؽ��Ŀ� ���� �ΰ����� ����������.
	//DirectX���� ���ҽ��� Direct3D ������ ���������ο��� ����� �� �ִ� �׷���ī�� �� �޸� �����̴�.

	//���ҽ���: ������ ����ȯ�� ���� �ؽ��Ŀ��� �Ļ��� ���ҽ����� ������ ���������ο� ������ �� �ִ� ���·� ���� ��.


	friend class GameEngineFolderTexture;
	//GameEngineDepthStencilTexture�� �� ������??

	friend class GameEngineDepthStencilTexture;
	//GameEngineDepthStencilTexture�� �� ������??

public:
	GameEngineTexture();
	~GameEngineTexture();
private:

	GameEngineTexture(const GameEngineTexture& _other) = delete;
	GameEngineTexture(GameEngineTexture&& _other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _other) = delete;
	GameEngineTexture& operator=(const GameEngineTexture&& _other) = delete;


public:

	static std::shared_ptr<GameEngineTexture> Create(const std::string_view& _name, ID3D11Texture2D* _texture);
	static std::shared_ptr<GameEngineTexture> Create(ID3D11Texture2D* _texture);
	static std::shared_ptr<GameEngineTexture> Create(const D3D11_TEXTURE2D_DESC& _desc);

	static std::shared_ptr<GameEngineTexture> Load(const std::string_view& _path);
	static std::shared_ptr<GameEngineTexture> Load(const std::string_view& _path, const std::string_view& _name);

	void VSSetting(int _bindPoint);
	void PSSetting(int _bindPoint);

	void VSReset(int _bindPoint);
	void PSReset(int _bindPoint);

	ID3D11RenderTargetView* CreateRenderTargetView();
	ID3D11ShaderResourceView* CreateShaderResourceView();
	ID3D11DepthStencilView* CreateDepthStencilView();

	//������ �ؽ�ó�� ���� x���, ���� y������� ���� ����.
	static void Cut(const std::string_view& _textureName, int _x, int _y);

	//���ϴ� ���� ������ �ȼ���ǥ�� ũ�⸦ UV������ ��ȯ �� ����.
	void Cut(UINT _startX, UINT _startY, UINT _sizeX, UINT _sizeY);

	float4 GetPixelToFloat4(int _x, int _y);	//float4�� �Ǽ� Ư���� ������ ���� �߻� ���ɼ� ����.
	PixelColor GetPixelToPixelColor(int _x, int _y);	//unsigned int ���·� �޾Ƽ� ������ ���� ����.

public:
	float4 GetFrameData(int _index)
	{
		if (true == this->cutData_.empty())
		{
			MsgBoxAssertString(this->GetNameCopy() + ": ���� �ڸ��� ���� �ؽ����Դϴ�.");
			return float4();
		}

		if (cutData_.size() <= _index)
		{
			MsgBoxAssertString(this->GetNameCopy() + ": ������ ������ �Ѿ���ϴ�.");
			return float4();
		}

		return cutData_[_index];
	}

	float4 GetScale()
	{
		//(metadata_.width), (metadata_.height)�̰ž��� 0,0�Ǽ� �ؽ��� ������ ������ ��
		return float4(static_cast<float>(desc_.Width),
			static_cast<float>(desc_.Height));
	}

	size_t GetCutCount()
	{
		return cutData_.size();
	}

	float4 GetCutScale(int _index)
	{
		return float4(cutData_[_index].sizeX * static_cast<float>(desc_.Width),
			cutData_[_index].sizeY * static_cast<float>(desc_.Height));
	}

	float4 GetCutPos(int _index)
	{
		return float4(cutData_[_index].posX * static_cast<float>(desc_.Width),
			cutData_[_index].posY * static_cast<float>(desc_.Height));
	}

private:
	void TextureLoad(const std::string_view& _path);
	//������ ��ο��� �ؽ�ó�� �ҷ����� �Լ�.���̴����ҽ��� ���� �������� ���ԵǾ� ����.

	void TextureCreate(const D3D11_TEXTURE2D_DESC& _desc);	//ID3D11Texture2D* �� �ؽ�ó ���� �Լ�. 
	void Cut(int _x, int _y);

private:
	ID3D11Texture2D* texture2D_;
	//�ȼ��� ���� ������ �� 2���� �迭�� ����� �׷���ī�� �� �޸� ������ �����ϴ� �������̽� ID3D11Texture2D* Ÿ�� �������.


	ID3D11RenderTargetView* renderTargetView_;
	//����Ÿ������ ���� �׷���ī�� �� �޸� ���� ������ �������̽� ID3D11RenderTargetView*Ÿ�� �������.
	//����Ÿ��: ������ ������������ ���� ��ģ ������μ��� ���� 2���� �迭�� �޴µ� ���Ǵ� �׷��� ī�� �� �޸� ����.

	ID3D11ShaderResourceView* shaderResourceView_;	//���̴����ҽ���.
	//
	//���̴����ҽ���: 

	ID3D11DepthStencilView* depthStencilView_;	//���̽��ٽǺ�.
	//
	//���̽��ٽǺ�:

	D3D11_TEXTURE2D_DESC desc_;	//�ؽ�ó ������ ����.


	DirectX::ScratchImage scratchImage_;//DirectXTex�� �ҷ��� �ؽ�ó
	DirectX::TexMetadata metaData_;		//DirectXTex�� �ҷ��� �ؽ�ó�� ���� ������.

	std::vector<float4> cutData_;	//������ �ִϸ��̼� ���� �� �ʿ��� ��Ʋ���ؽ�ó ���� ����.

};

