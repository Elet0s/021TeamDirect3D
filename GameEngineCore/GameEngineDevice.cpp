#include "PreCompile.h"
#include "GameEngineDevice.h"
#include "GameEngineTexture.h"
#include "GameEngineRenderTarget.h" 

ID3D11Device* GameEngineDevice::device_ = nullptr;
ID3D11DeviceContext* GameEngineDevice::deviceContext_ = nullptr;
IDXGISwapChain* GameEngineDevice::swapChain_ = nullptr;
std::shared_ptr<GameEngineRenderTarget> GameEngineDevice::backBufferRenderTarget_ = nullptr;

void GameEngineDevice::Initialize()
{
	CreateDevice();
}

void GameEngineDevice::CreateDevice()
{
	if (nullptr == GameEngineWindow::GetHWND())
	{
		MsgBoxAssert("�����찡 �������� �ʾҴµ� ����̽� �ʱ�ȭ�� �Ϸ��� �߽��ϴ�..");
		return;
	}

	int iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;	//���̷�ƮX11�� ����� ���̾� �ѱ�(enable).
#endif 

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;
	//����Ϸ��� ���̷�ƮX���� ����: 11.0.
	//D3D_FEATURE_LEVEL featureLevels[3] = { D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_9_0 };
	//����� ���̷�ƮX ������ ��������� �̷��� �ʱ�ȭ�ؼ� �Ű����� pFeatureLevel�� �ּҰ��� �־��ش�.

	if (S_OK != D3D11CreateDevice(	//���̷�ƮX ����̽�, ����̽� ���ؽ�Ʈ ���� �Լ�.
		NULL,				//���� ������� ������. NULL�̸� �⺻ ����� ���.
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,	//����̹� Ÿ��: �ϵ���� == �׷���ī��. 
		NULL,				//����Ʈ���� �����Ͷ����� �ڵ�. ������ D3D_DRIVER_TYPE_SOFTWARE�� ���� �ʾҴٸ� NULL.
		iFlag,				//Ȱ��ȭ�� ��Ÿ�� ���̾�: ����� ���̾�.
		NULL, 				//����� ��ó ����(�ý��ۿ��� ��밡���� ���̷�ƮX ����)�迭�� �ּҰ�. 
		//NULL�̸� �ڵ����� �ش� �ý��ۿ��� ������ �ֽ� ������ �����Ѵ�.

		0,					//����� ��ó ���� �迭 ũ��. 
		D3D11_SDK_VERSION,	//SDK���� ����. MSDN���� �׳� ������ �϶�� �Ǿ� ����.
		&device_,			//�ʱ�ȭ�� ���̷�ƮX ����̽� �������� �ּҰ�.
		&featureLevel,		//pFeatureLevel�� �־��� ��ó ���� �� ���� ��� ������ ���� �ֽ� ������ ��ȯ�Ѵ�.
		&deviceContext_		//�ʱ�ȭ�� ���̷�ƮX ����̽� ���ؽ�Ʈ �������� �ּҰ�.
	))
	{
		MsgBoxAssert("����̽� ���� ����.");
		return;
	}

	if (featureLevel != D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0)
	{
		MsgBoxAssert("���̷�ƮX11�� �������� �ʴ� �׷��� ī���Դϴ�.");
		return;
	}

	//typedef
	//	enum D3D_DRIVER_TYPE
	//{
	//	D3D_DRIVER_TYPE_UNKNOWN = 0,								
	// ����̹� Ÿ��: �� �� ����.
	// 
	//	D3D_DRIVER_TYPE_HARDWARE = (D3D_DRIVER_TYPE_UNKNOWN + 1),	
	// ����̹� Ÿ��: �ϵ���� == �׷���ī��.
	//  
	//	D3D_DRIVER_TYPE_REFERENCE = (D3D_DRIVER_TYPE_HARDWARE + 1),	
	// ����̹� Ÿ��: ���۷���. ����~
	// 
	//	D3D_DRIVER_TYPE_NULL = (D3D_DRIVER_TYPE_REFERENCE + 1),		
	// ����̹� Ÿ��: ��(��� �� ��). ����~
	// 
	//	D3D_DRIVER_TYPE_SOFTWARE = (D3D_DRIVER_TYPE_NULL + 1),		
	// ����̹� Ÿ��: ����Ʈ����. �׷���ī�尡 �ϴ� ���� CPU�� �ϰ� �ϴ� ����Ʈ���� ����̹� ���. �ſ� ����.
	// 
	//	D3D_DRIVER_TYPE_WARP = (D3D_DRIVER_TYPE_SOFTWARE + 1)		
	// ����̹� Ÿ��: WARP(Window Advanced Rasterizing Platform). ~.���̷�Ʈx 10������ ������.
	//} 	D3D_DRIVER_TYPE;

	//��Ƽ������ �ε��� �ɼ�.
	HRESULT result = CoInitializeEx(	//COM ��ü�� ����Ϸ��� �����忡�� COM ��ü�� �ʱ�ȭ�ϰ� ���ü� ���� �����ϴ� �Լ�.
		NULL,							//����Ǿ� �ִٰ� �ϴ� ����. �׳� MSDN������ NULL ������� �Ѵ�.
		COINIT_MULTITHREADED			//????
	);

	//CoUninitialize() �Լ��� ȣ������ �ʾƵ� �ǳ�??
}

void GameEngineDevice::CreateSwapChain()
{
	float4 screenSize = GameEngineWindow::GetScale();

	DXGI_SWAP_CHAIN_DESC scInfo = { 0 };

	scInfo.BufferDesc.Width = screenSize.UIX();		//ȭ�� ���α���.
	scInfo.BufferDesc.Height = screenSize.UIY();		//ȭ�� ���α���.

	scInfo.BufferDesc.RefreshRate.Denominator = 1;	//�ֻ��� �и� == �����ð�: 1��.
	scInfo.BufferDesc.RefreshRate.Numerator = 60;	//�ֻ��� ���� == �����ð��� ȭ�� ���� Ƚ��: 60��.

	scInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//���÷��� ����. 
	//DXGI_FORMAT_R8G8B8A8_UNORM: 8����Ʈ�� 0~1�� ����ȣ ����ȭ�� �������� RGBA�� ���� ��������� ���.

	scInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//��ĵ���� ����(���ο� ȭ���� �׸��� � �ȼ� ������� ���� �ٲ����� ���� ����): ������� ����.
	//���ʿ� � ������� �ϵ� �ʹ� ���� ���� ���� �����Ƿ� �ǹ� ����.

	scInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	//�̹��� ũ�� ���� ���: ������� ����.

	scInfo.SampleDesc.Count = 1;	//��Ƽ���ø��� ������ �ȼ��� ���� ����: 1��(���� ����).
	scInfo.SampleDesc.Quality = 0;	//��Ƽ���ø� ǰ�� ����: 0 == ��Ƽ���ø� ����.
	//����ü�ο��� ���� ���Ҹ� �����ϰ�, ���ø��� �ʿ��ϴٸ� ����ۿ� �ؾ� �ϹǷ� ����ü�� ������ ������ �� �ƹ� �ǹ� ����. 

	scInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	//����ü���� ���� ���� ��� ���: ȭ�鿡 ����� ����Ÿ������ | ���̴��� ��ģ ������� �޴� �뵵��.

	scInfo.OutputWindow = GameEngineWindow::GetHWND();
	//������ ����Ÿ���� ����� �������� �ڵ�.

	scInfo.BufferCount = 2;		//����ü���� ���� ���� �� ����� ���� ����: ���� ���ۿ� ����� 2��.

	scInfo.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	//����� ��ȯ���: ������� �̹����� �ø� ������� ���� ���ۿ� �����ϰ�, ������� ���� �̹����� ������.

	// enum DXGI_SWAP_EFFECT
	//{
	//		DXGI_SWAP_EFFECT_DISCARD = 0,			������� �̹����� bitblt������� ���� ���ۿ� �����ϰ�, ������� ���� �̹����� ������.
	//		DXGI_SWAP_EFFECT_SEQUENTIAL = 1,		������� �̹����� bitblt������� ���� ���ۿ� �����ϰ�, ������� ���� �̹����� �����.
	//		DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL = 3,	����۸� �ø� ������� ���� ���ۿ� ��ü�ϰ�, ���� ���۰� ������ �ִ� �̹����� �����.
	//		DXGI_SWAP_EFFECT_FLIP_DISCARD = 4		����۸� �ø� ������� ���� ���ۿ� ��ü�ϰ�, ���� ���۰� ������ �ִ� �̹����� ������.
	//}		DXGI_SWAP_EFFECT;
	//	������ �����ϴ� bitblt��ĺ��� �ϵ���������� ���� ���۸� ��ü�ϴ� �ø� ����� �� ȿ�����̸�, 
	//	DirectX12���ʹ� �ø� ��ĸ� ���δٰ� �Ѵ�.


	scInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	//DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH: 
	//��üȭ��/â��� ��ȯ�� ����� �ػ󵵰� �׿� �´� �ػ󵵷� �ڵ� ����.

	scInfo.Windowed = true;		//true: â���, false : ��üȭ��.



	//ID3D11Device != IDXGIDevice.

	IDXGIDevice* pDevice = nullptr;
	//�׳� DXGI �������̽� ������ �� ID3D11Device* �� ������ ���� ���� ������ �� �־ ����� ��.


	//���÷��� �����(������ ������ ����Ϳ� �׸��� ���. �밳�� �׷���ī��)�� ����� �߻�ȭ�� COM ��ü�� ����� �������̽� ������.
	IDXGIAdapter* pAdapter = nullptr;

	//����Ϳ� �׷����� ȭ�� ���� ���� ����� ���� COM ��ü�� ����� �������̽� ������.
	IDXGIFactory* pFactory = nullptr;
	//�� ���丮�� CreateSwapChain() �Լ��� ������ �ִ�.


	//GUID(Globally Unique IDentifier): �ü���� ���� �������� ���μ������� �����ϱ� ���� ���ϴ�, 
	// ���� �Ϻ��ϰ� �ߺ����� ���� 8-4-4-4-12�ڸ� ��. COM ���α׷����� �ٽ� ��Ҷ�� �Ѵ�.
	// �Ϻ��� ������ ���� �� ���� Ư���� ���� Ȯ���� �ߺ��Ǵ� ���� �����⵵ �Ѵٰ� �Ѵ�.

	//__uuidof(): �� ���μ����鸶���� ���̷�Ʈ �������̽����� �����ϱ� ���� ������ �ִ� 
	// UUID(Universally Unique IDentifier, ���� ���� �ĺ���. GUID�� �����з�. code first ���̱׷��̼� �� ���Ƿ� ��������)
	// ���� �������� ������.

	device_->QueryInterface(				//�־��� UUID�� �ش��ϴ�, COM ��ü�� ����� �������̽��� ��û�ؼ� �޾ƿ��� �Լ�.
		__uuidof(IDXGIDevice), 				//�� ���μ����� �ʿ�� �ϴ� �������̽��� UUID.
		reinterpret_cast<void**>(&pDevice)	//��û�� �������̽��� ���� IDXGIDevice* Ÿ�� ����.
	);
	if (nullptr == pDevice)
	{
		MsgBoxAssert("����̽� ���� ����.");
		return;
	}

	pDevice->GetParent(						//pDevice�� �θ� COM ��ü�� �������̽��� IDXGIAdapter�� �������� �Լ�.
		__uuidof(IDXGIAdapter),				//�� ���μ����� �ʿ�� �ϴ� �θ� COM ��ü�� �������̽��� GUID.
		reinterpret_cast<void**>(&pAdapter)	//��û�� �������̽��� ���� IDXGIAdapter* Ÿ�� ����.
	);
	if (nullptr == pAdapter)
	{
		MsgBoxAssert("����� ���� ����.");
		return;
	}
	//GetAdapter(&pAdapter)�� �ƴ϶� GetParent() �Լ��� ����� �������̽��� �������� ������?? ����̽��� ����� �������̽����� �ʿ��ؼ�??
	// ->�׳� ����ü�� ���� ������ �� �ϳ��� ���̴�. �ٸ� ������� �����ص� ���� ����.



	pAdapter->GetParent(						//pAdapter�� �θ� COM ��ü�� �������̽��� IDXGIFactory�� �������� �Լ�.
		__uuidof(IDXGIFactory),					//�� ���μ����� �ʿ�� �ϴ� �θ� COM ��ü�� �������̽��� GUID.
		reinterpret_cast<void**>(&pFactory)		//��û�� �������̽��� ���� IDXGIFactory* Ÿ�� ����.
	);
	if (nullptr == pFactory)
	{
		MsgBoxAssert("���丮 ���� ����.");
		return;
	}

	//CreateDXGIFactory()�� �ƴ϶� GetParent() �Լ��� ���丮 �������̽��� �������� ������??
	// ->�׳� ����ü�� ���� ������ �� �ϳ��� ���̴�. �ٸ� ������� �����ص� ���� ����.

	if (S_OK != pFactory->CreateSwapChain(	//����ü�� ���� �Լ�.
		device_,		//����ü���� ���鶧 �ʿ��� ����̽��� ������. NULL�̸� �ȵȴ�.
		&scInfo,		//����ü�� ������ �ʿ��� ������ ����� DXGI_SWAP_CHAIN_DESC����ü�� ������. ���� NULL�̸� �ȵȴ�.
		&swapChain_		//�����ؼ� ��ȯ�� ����ü�� ������ ������.
	))
	{
		MsgBoxAssert("swapchain_ ���� ����.");
		return;
	}

	//����ü���� �����ϱ� ���ؼ��� ���� �������̹Ƿ� ����ü���� ����� �� �� �ٷ� �����Ѵ�.
	pFactory->Release();
	pAdapter->Release();
	pDevice->Release();

	//���̷�Ʈ�� �����ϴ� �������̽��� �����͵��� ���۷��� ī���� ����ε�,
	//ComPtr���� ����Ŭ������ ���� �ʴ´ٸ� ���� ���� Release()�� ȣ������� �Ѵ�.
	//ComPtr Ŭ������ COM ��ü�� ���� smart pointer�� �� �� ������, 
	//�� Ŭ������ ���� �����ڰ� ���� Release()�� ȣ���� �ʿ䰡 ����.
	//COM ��ü�� ���� ������ ���� ����, Windows ��Ÿ�� ���̺귯��(WRL)�� Microsoft::WRL::Comptr �̶�� 
	//Ŭ������ �����Ѵ�(wrl.h ��������� ��Ŭ��� �ؾ� ��밡���ϴ�).

	//�ξ�� ������: �� ���� �޸� ������ ���� ���� �����Ͱ� ������ ������ �� ��,
	// ���� �Ҵ��� ������ ���۷��� Ƚ���� ������Ű��, ������ ������ ���۷��� ī��Ʈ�� ���ҽ��Ѽ� 
	// ���۷��� ī��Ʈ�� 0�� �� ���� ��¥ �޸� ������ �ؼ� 
	// ��۸� �����Ͱ� ���� ���ɼ��� ���ִ� ����� �������̴�.

	ID3D11Texture2D* backBufferTexture = nullptr;	//ȭ�鿡 ���������� �������� �ؽ���.
	if (S_OK != swapChain_->GetBuffer(	//����ü���� ����۵� �� �ϳ��� ������ �� �ְ� ���ִ� �Լ�.
		0,								//0�� ���ۿ� ����.
		__uuidof(ID3D11Texture2D),					//���۸� �����ϱ� ���� �������̽��� GUID.
		reinterpret_cast<void**>(&backBufferTexture)//���� ������� ID3D11Texture2D �������̽��� ������.
	))
	{
		MsgBoxAssert("������� �ؽ��ĸ� ������ �� �����߽��ϴ�.");
		return;
	}

	backBufferRenderTarget_ = GameEngineRenderTarget::Create("BackBuffer RenderTarget");
	//����� �뵵�� �� �� ���� ����Ÿ�� ����.

	backBufferRenderTarget_->CreateRenderTargetTexture(backBufferTexture, float4::Blue);
	//����ü�ο��� �޾ƿ� ����� �ؽ�ó�� ����Ÿ�ٺ並 �����.

	backBufferRenderTarget_->CreateDepthTexture(0);
	//���̽��ٽǺ並 ����µ� ����� �ؽ�ó�� �����Ѵ�.
}

void GameEngineDevice::RenderStart()
{
	backBufferRenderTarget_->Clear();
	//����ۿ� �����ִ� ���� �ȼ��������� ���� �� ������ ��� �����.

	backBufferRenderTarget_->Setting();
	//�ٽ� ������ ���������ο� ������ ������ �� �غ� �Ѵ�.
}

void GameEngineDevice::RenderEnd()
{
	HRESULT presentResult = swapChain_->Present(	//����۸� ���� ���۷� ��ü�ϴ� �Լ�.
		0,	//����ȭ ���� ����. 0: ��������ȭ ���� ��� ����۸� ��ü�ؼ� ȭ�鿡 ����. 
		//1~4: n��° ������ ���� ���� ����۸� ȭ�鿡 ����.
		0	//��� �ΰ� �ɼ�. 0: �ΰ��ɼ� ���� ���� ���ۺ��� ����Ѵ�.
	);
	if (presentResult == DXGI_ERROR_DEVICE_REMOVED ||	//DXGI_ERROR_DEVICE_REMOVED: GPU�� ���������� ���ŵǾ��ų� ���׷��̵� ���� ��. 
		presentResult == DXGI_ERROR_DEVICE_RESET	//DXGI_ERROR_DEVICE_RESET: ����̽� ������ ���� ������ �־���.
		)
	{
		MsgBoxAssert("������۸� ����.");
		return;
	}
	//if (S_OK != presemtResult)
	//{
	//	MsgBoxAssert("������۸� ����.");
	//	return;
	//}
	// �����찡 �ּ�ȭ�Ǿ��ų� �ٸ� �����쿡 ���Ȱų� �ϴ� ������ ������� ������ ���¿� ���� �������� ������ �߿���
	// S_OK�� �ƴ� DXGI_STATUS_OCCLUDED, DXGI_STATUS_CLIPPED ������ ����� ���� �� �ֱ� ������
	// ���������̼� ����� S_OK�� ����ϸ� ������ ���� �� �ִ�.
}
