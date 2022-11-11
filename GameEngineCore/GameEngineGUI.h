#pragma once
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "GameEngineUpdateObject.h"

class GameEngineGUIWindow
	: public GameEngineNameObject,
	public GameEngineUpdateObject,
	public std::enable_shared_from_this<GameEngineGUIWindow>
{
	//�� Ŭ������ ���� ������??

	friend class GameEngineGUI;


	void Begin();
	void End();

	void Start() override;
	void Update(float _deltaTime) override;


protected:
	virtual void Initialize(class GameEngineLevel* _level) = 0;
	virtual void OnGUI(class GameEngineLevel* _level, float _deltaTime) = 0;
};

class GameEngineGUI
{
	//ImGui ���� �� ���� Ŭ����.

	friend class GameEngineCore;
	//Destroy()�Լ��� ���� GameEngineCoreŬ���������� ���� �ϱ� ���ؼ� private�� ���� friend�� �Ǵ�.


public:
	GameEngineGUI();
	~GameEngineGUI();

protected:
	GameEngineGUI(const GameEngineGUI& _other) = delete;
	GameEngineGUI(GameEngineGUI&& _other) noexcept = delete;

private:
	GameEngineGUI& operator=(const GameEngineGUI& _other) = delete;
	GameEngineGUI& operator=(const GameEngineGUI&& _other) = delete;

public:
	static void Render(class GameEngineLevel* _level, float _deltaTime);
	static std::string OpenFileDlg(const std::string& _title, const std::string& _startPath);
	static std::string OpenFolderDlg(const std::string& _title, const std::string& _startPath);

public:
	template<typename GUIWindowType>
	static std::shared_ptr<GUIWindowType> CreateGUIWindow(const std::string& _name, GameEngineLevel* _level)
	{
		std::shared_ptr<GUIWindowType> newWindow = std::make_shared<GUIWindowType>();
		GameEngineGUIWindow* initWindow = newWindow.get();	//
		initWindow->SetName(_name);
		initWindow->Initialize(_level);
		guiWindows_.push_back(newWindow);
		return newWindow;
	}

protected:
	static void Initialize();
	static void Destroy();

private:
	static std::list<std::shared_ptr<GameEngineGUIWindow>> guiWindows_;

};

