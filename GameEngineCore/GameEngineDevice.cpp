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
		MsgBoxAssert("윈도우가 생성되지 않았는데 디바이스 초기화를 하려고 했습니다..");
		return;
	}

	int iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;	//다이렉트X11의 디버그 레이어 켜기(enable).
#endif 

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;
	//사용하려는 다이렉트X버전 세팅: 11.0.
	//D3D_FEATURE_LEVEL featureLevels[3] = { D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_9_0 };
	//사용할 다이렉트X 버전이 여러개라면 이렇게 초기화해서 매개변수 pFeatureLevel에 주소값을 넣어준다.

	if (S_OK != D3D11CreateDevice(	//다이렉트X 디바이스, 디바이스 컨텍스트 생성 함수.
		NULL,				//비디오 어댑터의 포인터. NULL이면 기본 어댑터 사용.
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,	//드라이버 타입: 하드웨어 == 그래픽카드. 
		NULL,				//소프트웨어 래스터라이저 핸들. 위에서 D3D_DRIVER_TYPE_SOFTWARE를 넣지 않았다면 NULL.
		iFlag,				//활성화할 런타임 레이어: 디버그 레이어.
		NULL, 				//사용할 피처 레벨(시스템에서 사용가능한 다이렉트X 버전)배열의 주소값. 
		//NULL이면 자동으로 해당 시스템에서 가능한 최신 버전을 선택한다.

		0,					//사용할 피처 레벨 배열 크기. 
		D3D11_SDK_VERSION,	//SDK버전 세팅. MSDN에도 그냥 저렇게 하라고만 되어 있음.
		&device_,			//초기화할 다이렉트X 디바이스 포인터의 주소값.
		&featureLevel,		//pFeatureLevel에 넣어준 피처 레벨 중 현재 사용 가능한 가장 최신 버전을 반환한다.
		&deviceContext_		//초기화할 다이렉트X 디바이스 컨텍스트 포인터의 주소값.
	))
	{
		MsgBoxAssert("디바이스 생성 실패.");
		return;
	}

	if (featureLevel != D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0)
	{
		MsgBoxAssert("다이렉트X11을 지원하지 않는 그래픽 카드입니다.");
		return;
	}

	//typedef
	//	enum D3D_DRIVER_TYPE
	//{
	//	D3D_DRIVER_TYPE_UNKNOWN = 0,								
	// 드라이버 타입: 알 수 없음.
	// 
	//	D3D_DRIVER_TYPE_HARDWARE = (D3D_DRIVER_TYPE_UNKNOWN + 1),	
	// 드라이버 타입: 하드웨어 == 그래픽카드.
	//  
	//	D3D_DRIVER_TYPE_REFERENCE = (D3D_DRIVER_TYPE_HARDWARE + 1),	
	// 드라이버 타입: 레퍼런스. 보통~
	// 
	//	D3D_DRIVER_TYPE_NULL = (D3D_DRIVER_TYPE_REFERENCE + 1),		
	// 드라이버 타입: 널(사용 안 함). 보통~
	// 
	//	D3D_DRIVER_TYPE_SOFTWARE = (D3D_DRIVER_TYPE_NULL + 1),		
	// 드라이버 타입: 소프트웨어. 그래픽카드가 하는 일을 CPU가 하게 하는 소프트웨어 드라이버 사용. 매우 느림.
	// 
	//	D3D_DRIVER_TYPE_WARP = (D3D_DRIVER_TYPE_SOFTWARE + 1)		
	// 드라이버 타입: WARP(Window Advanced Rasterizing Platform). ~.다이렉트x 10까지만 지원됨.
	//} 	D3D_DRIVER_TYPE;

	//멀티스레드 로딩용 옵션.
	HRESULT result = CoInitializeEx(	//COM 객체를 사용하려는 스레드에서 COM 객체를 초기화하고 동시성 모델을 결정하는 함수.
		NULL,							//예약되어 있다고만 하는 변수. 그냥 MSDN에서도 NULL 넣으라고만 한다.
		COINIT_MULTITHREADED			//????
	);

	//CoUninitialize() 함수는 호출하지 않아도 되나??
}

void GameEngineDevice::CreateSwapChain()
{
	float4 screenSize = GameEngineWindow::GetScale();

	DXGI_SWAP_CHAIN_DESC scInfo = { 0 };

	scInfo.BufferDesc.Width = screenSize.UIX();		//화면 가로길이.
	scInfo.BufferDesc.Height = screenSize.UIY();		//화면 세로길이.

	scInfo.BufferDesc.RefreshRate.Denominator = 1;	//주사율 분모 == 단위시간: 1초.
	scInfo.BufferDesc.RefreshRate.Numerator = 60;	//주사율 분자 == 단위시간당 화면 갱신 횟수: 60번.

	scInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//디스플레이 포맷. 
	//DXGI_FORMAT_R8G8B8A8_UNORM: 8바이트의 0~1로 무부호 정규화된 정수값을 RGBA순 색상값 저장용으로 사용.

	scInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//스캔라인 순서(새로운 화면을 그릴때 어떤 픽셀 순서대로 색을 바꿀지에 대한 정보): 명시하지 않음.
	//애초에 어떤 방식으로 하든 너무 빨라서 느낄 수도 없으므로 의미 없다.

	scInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	//이미지 크기 조정 방식: 명시하지 않음.

	scInfo.SampleDesc.Count = 1;	//멀티샘플링에 참조할 픽셀당 샘플 개수: 1개(참조 안함).
	scInfo.SampleDesc.Quality = 0;	//멀티샘플링 품질 수준: 0 == 멀티샘플링 안함.
	//스왑체인에선 버퍼 스왑만 설정하고, 샘플링이 필요하다면 백버퍼에 해야 하므로 스왑체인 설정을 만지는 건 아무 의미 없다. 

	scInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	//스왑체인이 가진 버퍼 사용 방식: 화면에 출력할 렌더타겟으로 | 셰이더를 거친 결과물을 받는 용도로.

	scInfo.OutputWindow = GameEngineWindow::GetHWND();
	//지정한 렌더타겟을 출력할 윈도우의 핸들.

	scInfo.BufferCount = 2;		//스왑체인이 가진 버퍼 중 사용할 버퍼 개수: 전면 버퍼와 백버퍼 2개.

	scInfo.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	//백버퍼 전환방식: 백버퍼의 이미지를 플립 방식으로 전면 버퍼에 복사하고, 백버퍼의 기존 이미지는 버린다.

	// enum DXGI_SWAP_EFFECT
	//{
	//		DXGI_SWAP_EFFECT_DISCARD = 0,			백버퍼의 이미지를 bitblt방식으로 전면 버퍼에 복사하고, 백버퍼의 기존 이미지는 버린다.
	//		DXGI_SWAP_EFFECT_SEQUENTIAL = 1,		백버퍼의 이미지를 bitblt방식으로 전면 버퍼에 복사하고, 백버퍼의 기존 이미지는 남긴다.
	//		DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL = 3,	백버퍼를 플립 방식으로 전면 버퍼와 교체하고, 전면 버퍼가 가지고 있던 이미지는 남긴다.
	//		DXGI_SWAP_EFFECT_FLIP_DISCARD = 4		백버퍼를 플립 방식으로 전면 버퍼와 교체하고, 전면 버퍼가 가지고 있던 이미지는 버린다.
	//}		DXGI_SWAP_EFFECT;
	//	일일히 복사하는 bitblt방식보다 하드웨어적으로 전후 버퍼를 교체하는 플립 방식이 더 효율적이며, 
	//	DirectX12부터는 플립 방식만 쓰인다고 한다.


	scInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	//DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH: 
	//전체화면/창모드 전환시 모니터 해상도가 그에 맞는 해상도로 자동 조정.

	scInfo.Windowed = true;		//true: 창모드, false : 전체화면.



	//ID3D11Device != IDXGIDevice.

	IDXGIDevice* pDevice = nullptr;
	//그냥 DXGI 인터페이스 포인터 중 ID3D11Device* 가 있을때 가장 먼저 가져올 수 있어서 사용한 것.


	//디스플레이 어댑터(렌더링 정보를 모니터에 그리는 장비. 대개는 그래픽카드)의 기능을 추상화한 COM 객체와 연결된 인터페이스 포인터.
	IDXGIAdapter* pAdapter = nullptr;

	//모니터에 그려지는 화면 갱신 관련 기능을 가진 COM 객체와 연결된 인터페이스 포인터.
	IDXGIFactory* pFactory = nullptr;
	//이 팩토리가 CreateSwapChain() 함수를 가지고 있다.


	//GUID(Globally Unique IDentifier): 운영체제가 현재 실행중인 프로세스들을 구분하기 위해 정하는, 
	// 거의 완벽하게 중복되지 않을 8-4-4-4-12자리 값. COM 프로그래밍의 핵심 요소라고 한다.
	// 완벽한 난수를 만들 수 없는 특성상 낮은 확률로 중복되는 값이 나오기도 한다고 한다.

	//__uuidof(): 각 프로세스들마다의 다이렉트 인터페이스들을 구분하기 위해 가지고 있는 
	// UUID(Universally Unique IDentifier, 범용 고유 식별자. GUID의 하위분류. code first 마이그레이션 때 임의로 정해진다)
	// 값을 가져오는 연산자.

	device_->QueryInterface(				//주어진 UUID에 해당하는, COM 객체와 연결된 인터페이스를 요청해서 받아오는 함수.
		__uuidof(IDXGIDevice), 				//이 프로세스가 필요로 하는 인터페이스의 UUID.
		reinterpret_cast<void**>(&pDevice)	//요청한 인터페이스를 받을 IDXGIDevice* 타입 변수.
	);
	if (nullptr == pDevice)
	{
		MsgBoxAssert("디바이스 추출 실패.");
		return;
	}

	pDevice->GetParent(						//pDevice의 부모 COM 객체의 인터페이스인 IDXGIAdapter를 가져오는 함수.
		__uuidof(IDXGIAdapter),				//이 프로세스가 필요로 하는 부모 COM 객체의 인터페이스의 GUID.
		reinterpret_cast<void**>(&pAdapter)	//요청한 인터페이스를 받을 IDXGIAdapter* 타입 변수.
	);
	if (nullptr == pAdapter)
	{
		MsgBoxAssert("어댑터 추출 실패.");
		return;
	}
	//GetAdapter(&pAdapter)가 아니라 GetParent() 함수로 어댑터 인터페이스를 가져오는 이유는?? 디바이스와 연결된 인터페이스들이 필요해서??
	// ->그냥 스왑체인 생성 절차들 중 하나일 뿐이다. 다른 방식으로 생성해도 문제 없다.



	pAdapter->GetParent(						//pAdapter의 부모 COM 객체의 인터페이스인 IDXGIFactory를 가져오는 함수.
		__uuidof(IDXGIFactory),					//이 프로세스가 필요로 하는 부모 COM 객체의 인터페이스의 GUID.
		reinterpret_cast<void**>(&pFactory)		//요청한 인터페이스를 받을 IDXGIFactory* 타입 변수.
	);
	if (nullptr == pFactory)
	{
		MsgBoxAssert("팩토리 추출 실패.");
		return;
	}

	//CreateDXGIFactory()가 아니라 GetParent() 함수로 팩토리 인터페이스를 가져오는 이유는??
	// ->그냥 스왑체인 생성 절차들 중 하나일 뿐이다. 다른 방식으로 생성해도 문제 없다.

	if (S_OK != pFactory->CreateSwapChain(	//스왑체인 생성 함수.
		device_,		//스왑체인을 만들때 필요한 디바이스의 포인터. NULL이면 안된다.
		&scInfo,		//스왑체인 생성시 필요한 명세서가 저장된 DXGI_SWAP_CHAIN_DESC구조체의 포인터. 역시 NULL이면 안된다.
		&swapChain_		//생성해서 반환할 스왑체인 변수의 포인터.
	))
	{
		MsgBoxAssert("swapchain_ 생성 실패.");
		return;
	}

	//스왑체인을 생성하기 위해서만 만든 변수들이므로 스왑체인을 만들고 난 후 바로 정리한다.
	pFactory->Release();
	pAdapter->Release();
	pDevice->Release();

	//다이렉트가 제공하는 인터페이스의 포인터들은 레퍼런스 카운팅 방식인데,
	//ComPtr같은 보조클래스를 쓰지 않는다면 내가 직접 Release()를 호출해줘야 한다.
	//ComPtr 클래스는 COM 객체를 위한 smart pointer라 할 수 있으며, 
	//이 클래스를 쓰면 개발자가 직접 Release()를 호출할 필요가 없다.
	//COM 객체의 수명 관리를 돕기 위해, Windows 런타임 라이브러리(WRL)은 Microsoft::WRL::Comptr 이라는 
	//클래스를 제공한다(wrl.h 헤더파일을 인클루드 해야 사용가능하다).

	//셰어드 포인터: 한 개의 메모리 영역을 여러 개의 포인터가 나누어 가져야 할 때,
	// 새로 할당할 때마다 레퍼런스 횟수를 증가시키고, 해제할 때마다 레퍼런스 카운트를 감소시켜서 
	// 레퍼런스 카운트가 0이 될 때만 진짜 메모리 해제를 해서 
	// 댕글링 포인터가 생길 가능성을 없애는 방식의 포인터이다.

	ID3D11Texture2D* backBufferTexture = nullptr;	//화면에 최종적으로 내보내는 텍스쳐.
	if (S_OK != swapChain_->GetBuffer(	//스왑체인의 백버퍼들 중 하나에 접근할 수 있게 해주는 함수.
		0,								//0번 버퍼에 접근.
		__uuidof(ID3D11Texture2D),					//버퍼를 조종하기 위한 인터페이스의 GUID.
		reinterpret_cast<void**>(&backBufferTexture)//얻어올 백버퍼의 ID3D11Texture2D 인터페이스의 포인터.
	))
	{
		MsgBoxAssert("백버퍼의 텍스쳐를 얻어오는 데 실패했습니다.");
		return;
	}

	backBufferRenderTarget_ = GameEngineRenderTarget::Create("BackBuffer RenderTarget");
	//백버퍼 용도로 쓸 빈 깡통 렌더타겟 생성.

	backBufferRenderTarget_->CreateRenderTargetTexture(backBufferTexture, float4::Blue);
	//스왑체인에서 받아온 백버퍼 텍스처로 렌더타겟뷰를 만든다.

	backBufferRenderTarget_->CreateDepthTexture(0);
	//깊이스텐실뷰를 만드는데 사용할 텍스처를 생성한다.
}

void GameEngineDevice::RenderStart()
{
	backBufferRenderTarget_->Clear();
	//백버퍼에 남아있던 이전 픽셀정보들은 전부 한 색으로 덮어서 지운다.

	backBufferRenderTarget_->Setting();
	//다시 렌더링 파이프라인에 연결해 렌더링 할 준비를 한다.
}

void GameEngineDevice::RenderEnd()
{
	HRESULT presentResult = swapChain_->Present(	//백버퍼를 전면 버퍼로 교체하는 함수.
		0,	//동기화 지연 간격. 0: 수직동기화 없이 즉시 백버퍼를 교체해서 화면에 띄운다. 
		//1~4: n번째 프레임 공백 이후 백버퍼를 화면에 띄운다.
		0	//출력 부가 옵션. 0: 부가옵션 없이 현재 버퍼부터 출력한다.
	);
	if (presentResult == DXGI_ERROR_DEVICE_REMOVED ||	//DXGI_ERROR_DEVICE_REMOVED: GPU가 물리적으로 제거되었거나 업그레이드 진행 중. 
		presentResult == DXGI_ERROR_DEVICE_RESET	//DXGI_ERROR_DEVICE_RESET: 디바이스 생성에 뭔가 문제가 있었음.
		)
	{
		MsgBoxAssert("더블버퍼링 실패.");
		return;
	}
	//if (S_OK != presemtResult)
	//{
	//	MsgBoxAssert("더블버퍼링 실패.");
	//	return;
	//}
	// 윈도우가 최소화되었거나 다른 윈도우에 가렸거나 하는 식으로 윈도우와 렌더링 상태에 따라서 정상적인 렌더링 중에도
	// S_OK가 아닌 DXGI_STATUS_OCCLUDED, DXGI_STATUS_CLIPPED 따위의 결과가 나올 수 있기 때문에
	// 프레젠테이션 결과로 S_OK만 허용하면 문제가 생길 수 있다.
}
