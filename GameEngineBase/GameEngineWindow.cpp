#include "PreCompile.h"
#include "GameEngineWindow.h"
#include "GameEngineInput.h"
#include "GameEngineString.h"

GameEngineWindow* GameEngineWindow::inst_ = new GameEngineWindow();
//보통 포인터 싱글톤은 생성과 삭제를 원하는 타이밍에 하려고 쓰는 방식이지만,
// 여기서는 생성은 런타임 시작과 동시에 하기 때문에 시점 조절이 안된다. 삭제만 원하는 시점에 할 수 있다.

std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> GameEngineWindow::messageHandler_ = nullptr;

GameEngineWindow::GameEngineWindow()
	: windowOn_(true),
	isFocused_(true),
	instanceHandle_(nullptr),
	windowHandle_(nullptr),
	hdc_(nullptr)
{
}

GameEngineWindow::~GameEngineWindow()
{
	if (nullptr != hdc_)
	{
		ReleaseDC(windowHandle_, hdc_);
		hdc_ = nullptr;
	}

	if (nullptr != windowHandle_)
	{
		DestroyWindow(windowHandle_);
		windowHandle_ = nullptr;
	}
}

void GameEngineWindow::RegClass(HINSTANCE _hInstance)
{
	//typedef struct tagWNDCLASSEXA {
	//    UINT        cbSize;			이 구조체 크기.
	//    /* Win 3.x */
	//    UINT        style;            윈도우의 형태.
	//    WNDPROC     lpfnWndProc;      윈도우 메세지를 처리할 함수 이름.    
	//    int         cbClsExtra;       여유 공간. 거의 쓰지 않음.
	//    int         cbWndExtra;       여유 공간. 거의 쓰지 않음.
	//    HINSTANCE   hInstance;        윈도우 클래스를 사용하는 프로그램(인스턴스)의 핸들.  
	//    HICON       hIcon;            윈도우 아이콘
	//    HCURSOR     hCursor;          윈도우에서 쓸 커서 형태.
	//    HBRUSH      hbrBackground;    윈도우 배경을 칠할, 특정 색의 브러시 오브젝트 지정. +1: 백색, +2:회색
	//    LPCWSTR     lpszMenuName;     프로그램이 쓸 메뉴 지정. 사용하지 않을거라면 NULL
	//    LPCWSTR     lpszClassName;    윈도우 클래스의 이름. MyRegisterClass()를 통해 OS에 등록된 클래스이름과 다르면 실행되지 않는다.
	//    /* Win 4.0 */
	//    HICON       hIconSm;          윈도우가 최소화되면 사용할 아이콘.
	//} WNDCLASSEXA, * PWNDCLASSEXA, NEAR* NPWNDCLASSEXA, FAR* LPWNDCLASSEXA;

	WNDCLASSEXA wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = MessageProcess;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = _hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = windowClassName_.c_str();
	wcex.hIconSm = nullptr;

	if (0 == RegisterClassExA(&wcex))
	{
		MsgBoxAssert("윈도우 클래스 등록 실패.");
		return;
	}
}

void GameEngineWindow::CreateGameWindow(HINSTANCE _hInstance, const std::string& _windowTitle)
{
	if (nullptr != instanceHandle_)
	{
		MsgBoxAssert("윈도우를 2번 띄우려고 했습니다.");
		return;
	}

	windowTitle_ = _windowTitle;
	instanceHandle_ = _hInstance;
	windowClassName_ = "DefaultWindowClassName";
	RegClass(instanceHandle_);

	windowHandle_ = CreateWindowExA(//확장형 스타일을 사용할 수 있는 윈도우를 생성하고 핸들을 반환하는 함수. 
		WS_EX_LEFT,					//윈도우 스타일 확장형: 일반적인 왼쪽 정렬.
		windowClassName_.c_str(),	//윈도우클래스 이름.
		windowTitle_.c_str(),		//윈도우 타이틀 이름.
		WS_OVERLAPPEDWINDOW,		//윈도우 스타일 기본. 
		//WS_OVERLAPPEDWINDOW: 기본적인 윈도우 스타일 모음.
		//= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
		//겹친 창의?? | 제목 표시줄이 있는 | 윈도우 타이틀에 윈도우 메뉴가 있는 | 크기조정 테두리가 있는 | 최소화 버튼이 있는 | 최대화 버튼이 있는
		CW_USEDEFAULT,				//윈도우 좌상단 x좌표: 신경쓰지 않음.
		0,							//윈도우 좌상단 y좌표: 신경쓰지 않음.
		CW_USEDEFAULT,				//윈도우 가로길이: 신경쓰지 않음.
		0, 							//윈도우 세로길이: 신경쓰지 않음.
		nullptr,					//부모 윈도우의 핸들.
		nullptr,					//메뉴 핸들.
		instanceHandle_,			//인스턴스 핸들.
		nullptr						//lpParam??
	);

	if (NULL == windowHandle_)
	{
		MsgBoxAssert("윈도우 핸들 생성 실패.");
		return;
	}

	hdc_ = GetDC(windowHandle_);

	if (nullptr == hdc_)
	{
		MsgBoxAssert("디바이스컨텍스트 핸들 생성 실패.");
		return;
	}
}

void GameEngineWindow::ShowGameWindow()
{
	if (nullptr == windowHandle_)
	{
		MsgBoxAssert("윈도우 핸들이 없습니다.");
		return;
	}

	ShowWindow(windowHandle_, SW_SHOW);
	// #define SW_SHOWMAXIMIZED    3
	UpdateWindow(windowHandle_);
}

void GameEngineWindow::MessageLoop(
	std::function<void()> _init,
	std::function<void()> _loop,
	std::function<void()> _end
)
{
	if (nullptr != _init)
	{
		_init();
	}

	MSG msg = { 0 };

	//윈도우 내부에서는 보이지 않지만
	//std::list<MSG> MessageQueue;
	//메세지를 처리했다면 MessageQueue.clear();

	//메세지 큐(Message Queue): 
	// 여러 프로세스들 사이에서의 데이터 송수신 방식으로, 프로세스들간에 직접적으로 데이터를 주고받는것이 아니라
	// 메세지라는 형태로 변환해서 특정 대기열에 삽입하면 삽입된 순서대로 수신대상인 프로세스들이 받아 
	// 처리할 수 있게 한다. 여기서 메세지들이 삽입되는 대기열을 메세지 큐라고 하고, 메세지 큐 중심으로 구성된 시스템을 
	// 메세지 지향 미들웨어(Meesage Oriented Middleware: MOM)라고 한다.
	// 우체국을 통한 우편물 송수신 시스템과 유사하다.
	
	//메세지 큐의 장점: 
	//비동기(Asynchronous): 메세지를 직접 전달하지 않고 큐(Queue)에 넣어 수신, 처리될때까지 저장되어 있기 때문에 나중에 처리할 수 있다.  
	//비동조(Decoupling): 송신자-메세지 큐-수신자 간 분리가 가능하다.
	//탄력성(Resilience): 몇몇 수신자가 메세지 처리를 지연하거나 실패해도 전체에는 영향을 주지 않는다. 
	//과잉(Redundancy): 메세지 처리에 실패한 경우에도 메세지는 여전히 큐에 남아 있으므로 얼마든지 재실행 가능하다. 
	//보장성(Guarantees): 수신, 처리된 메세지는 사라지므로 언제든지 작업이 처리되었는지 확인할 수 있다.
	//확장성(Scalable): N:1:N으로 다수의 프로세스들이 메세지 큐를 통해서 메세지를 주고받을 수 있다.


	//이 while이 1초에 60번 돌면 60프레임이다.

	while (windowOn_)
	{
		if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (nullptr != _loop)
		{
			_loop();
		}
	}

	//프로그램을 끄면 가장 먼저 도달하는 곳.
	if (nullptr != _end)
	{
		_end();
	}

}

void GameEngineWindow::SetWindowScaleAndPosition(const float4& _position, const float4& _scale)
{
	RECT Rc = { 0, 0, _scale.IX(), _scale.IY() };

	windowScale_ = _scale;

	AdjustWindowRect(
		&Rc,					//
		WS_OVERLAPPEDWINDOW,	//
		FALSE					//
	);

	SetWindowPos(
		windowHandle_,		//
		nullptr,			//
		_position.IX(),		//
		_position.IY(),		//
		Rc.right - Rc.left,	//
		Rc.bottom - Rc.top,	//
		SWP_NOZORDER		//
	);
}

void GameEngineWindow::Off()
{
	windowOn_ = false;
}

LRESULT GameEngineWindow::MessageProcess(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	if (nullptr != messageHandler_)
	{
		if (0 != messageHandler_(_hWnd, _message, _wParam, _lParam))
			//ImGUI의 메세지 핸들러 함수에게 윈도우 메세지를 넘긴다.
		{
			return true;
		}
	}

	switch (_message)
	{
	case WM_DESTROY:
	case WM_CLOSE:
	{
		GameEngineWindow::GetInst().Off();
		break;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(_hWnd, &ps);
		EndPaint(_hWnd, &ps);
		break;
	}

	case WM_SETFOCUS:
	{
		inst_->isFocused_ = true;
		break;
	}

	case WM_KILLFOCUS:
	{
		inst_->isFocused_ = false;
		break;
	}

	case WM_MOUSEHWHEEL:
	{
		GameEngineInput::GetInst().SetWheelValue(static_cast<int>HIWORD(_wParam));
		break;
	}

	default:
		return DefWindowProc(_hWnd, _message, _wParam, _lParam);
	}

	return 0;
}
