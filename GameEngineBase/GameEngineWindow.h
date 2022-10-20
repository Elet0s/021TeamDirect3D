#pragma once
#include "GameEngineMath.h"
#include "GameEngineDebug.h"


class GameEngineWindow
{
	static GameEngineWindow* inst_;
	//값형으로 안 하고 포인터 형식으로 싱글턴을 만드는 이유: 생성과 제거 시점을 내 마음대로 통제하기 위해서. 
	//하지만 이 경우에는 생성시점은 런타임 시작할때로 고정되어 있고 삭제 시점만 통제할 수 있다.

private:
	GameEngineWindow();
	~GameEngineWindow();

	GameEngineWindow(const GameEngineWindow& _other) = delete;
	GameEngineWindow(GameEngineWindow&& _other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _other) = delete;


public:
	void RegClass(HINSTANCE _hInstance);
	void CreateGameWindow(HINSTANCE _hInstance, const std::string& _windowTitle);
	void ShowGameWindow();
	void MessageLoop(
		std::function<void()> _init,
		std::function<void()> _loop,
		std::function<void()> _end);
	void SetWindowScaleAndPosition(const float4& _pos, const float4& _scale);
	void Off();

public:
	static GameEngineWindow* GetInst()
	{
		return inst_;	
	}

	static void Destroy()
	{
		//싱글톤 삭제'만' 원하는 타이밍에 한다.
		if (nullptr != inst_)
		{
			delete inst_;
			inst_ = nullptr;
		}
	}

	static HDC GetHDC() 
	{
		return inst_->hdc_;
	}

	static HWND GetHWND() 
	{
		return inst_->windowHandle_;
	}

	static float4 GetScale() 
	{
		return inst_->windowScale_;
	}

	void SetMessageHandler(
		const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _messageHandler)
	{
		messageHandler_ = _messageHandler;
	}


private:
	bool windowOn_;

	HINSTANCE instanceHandle_;
	HWND windowHandle_;
	HDC hdc_;
	std::string windowClassName_;
	std::string windowTitle_;
	float4 windowScale_;

	static std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> messageHandler_;
	//ImGUI의 메세지 핸들러 함수를 std::function으로 저장.

	static LRESULT CALLBACK MessageProcess(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

};

