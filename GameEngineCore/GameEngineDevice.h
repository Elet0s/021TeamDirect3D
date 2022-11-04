#pragma once

class GameEngineRenderTarget;
class GameEngineDevice
{
	//�׷���ī���� �޸𸮿� ������ ���� ���ҽ��� �����ϴµ� �ʿ��� ID3D11Device, 
	// ������ ���� ���ҽ���� ������ �۾��� ������ ID3D11DeviceContext,
	// ������������������ ��ģ ����� ����Ÿ�ٺ並 ������۸��ؼ� ȭ�鿡 ���µ� �ʿ��� IDXGISwapChain ��ü���� 
	// ����, �����ϴ� Ŭ����.

	//�������� �� ���� �����Ƿ� ����, �Լ� ��� ����ƽ���� �Ѵ�.

	friend class GameEngineCore;

private:
	GameEngineDevice() {};
	~GameEngineDevice() {};

	GameEngineDevice(const GameEngineDevice& _other) = delete;
	GameEngineDevice(GameEngineDevice&& _other) noexcept = delete;
	GameEngineDevice& operator=(const GameEngineDevice& _other) = delete;
	GameEngineDevice& operator=(const GameEngineDevice&& _other) = delete;


public:
	//����̽� �ʱ�ȭ.
	static void Initialize();

	//�ѹ��� �������� �غ��ϱ� ���� ����� ����Ÿ���� �����ϴ� �Լ�.
	static void RenderStart();	

	//��� ������ ������ ��ģ ����۸� ���� ���ۿ� ��ü�ϴ� �Լ�.
	static void RenderEnd();	

public:

	static void Destroy()
	{
		if (nullptr != swapChain_)
		{
			swapChain_->Release();
			swapChain_ = nullptr;
		}
		if (nullptr != deviceContext_)
		{
			deviceContext_->Release();
			deviceContext_ = nullptr;
		}	
		if (nullptr != device_)
		{
			device_->Release();
			device_ = nullptr;
		}
	}

	static ID3D11Device* GetDevice()
	{
		return device_;
	}

	static ID3D11DeviceContext* GetContext()
	{
		return deviceContext_;
	}

	static GameEngineRenderTarget* GetBackBuffer()
	{
		return backBufferRenderTarget_;
	}

private:
	static void CreateDevice();		
	//�������̽� ����ü ID3D11DeviceŸ�� ������ ��ü�� ID3D11DeviceContextŸ�� ������ ��ü�� �����ؼ�,
	// ���� ������� device_�� deviceContext_�� ����/�����ϴ� �Լ�. 

	static void CreateSwapChain();	
	//�������̽� ����ü IDXGISwapChainŸ�� ������ ��ü�� �����ؼ� ������� swapChain_���� ����/�����ϴ� �Լ�.

private:
	static ID3D11Device* device_;
	//���̷�ƮX ����̽�: �׷���ī�忡 �޸� ������ �Ҵ��Ϸ��� �� �� �ʿ��� ��.
	//�׷���ī���� �޸𸮿� new������ �� �� �ִ� ������ ������ �ִ�.

	static ID3D11DeviceContext* deviceContext_;	//���̷�ƮX�� ����̽� ���ؽ�Ʈ.
	//�׷���ī�忡 ������ ���� ������ ����� �� �ʿ��ϴ�. 
	//���̷�Ʈ 9���� �������� 11�� device�� deviceContext�� �и��Ǿ���.

	static IDXGISwapChain* swapChain_;	//��������ȭ�� ���� ���۸��� �ϴµ� ���Ǵ� ���̷�ƮX�� �������̽�.
	//�ʿ��� ������ ������ŭ ����� �ȴ�.
	//�ٽ� ������ ����� ����Ÿ�ٿ� �׷��� ������ ������ OS(Windows)�� ���� ����Ϳ� �����ϴ°��̴�.
	//�׷��� �ؼ� ���޵� ������ ������� OS�� �� ���μ������� �Ҵ�� �����쿡 �ش��ϴ� �ȼ��鿡 �׸��� ���̴�.

	static GameEngineRenderTarget* backBufferRenderTarget_;
	//����۷� ���̴� ����Ÿ��. ���⿡ �׷����°͸��� ������۸� ������ ���� ȭ�鿡 �׷�����.

};

