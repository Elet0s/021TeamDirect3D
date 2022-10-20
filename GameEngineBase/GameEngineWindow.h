#pragma once
#include "GameEngineMath.h"
#include "GameEngineDebug.h"


class GameEngineWindow
{
	static GameEngineWindow* inst_;
	//�������� �� �ϰ� ������ �������� �̱����� ����� ����: ������ ���� ������ �� ������� �����ϱ� ���ؼ�. 
	//������ �� ��쿡�� ���������� ��Ÿ�� �����Ҷ��� �����Ǿ� �ְ� ���� ������ ������ �� �ִ�.

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
		//�̱��� ����'��' ���ϴ� Ÿ�ֿ̹� �Ѵ�.
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
	//ImGUI�� �޼��� �ڵ鷯 �Լ��� std::function���� ����.

	static LRESULT CALLBACK MessageProcess(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

};

