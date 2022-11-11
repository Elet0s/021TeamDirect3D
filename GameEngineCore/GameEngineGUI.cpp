#include "PreCompile.h"
#include "GameEngineGUI.h"
#include "GameEngineDevice.h"
#include "portable-file-dialogs.h"

//Forward declare message handler from imgui_impl_win32.cpp
//->imgui_impl_win32.cpp에 있는 메세지 핸들러의 전방선언.
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void GameEngineGUIWindow::Begin()
{
    std::string guiWindowName = GameEngineString::AnsiToUTF8Return(this->GetNameCopy());

    ImGui::Begin(guiWindowName.c_str(), &IsUpdateRef());
}

void GameEngineGUIWindow::End()
{
    ImGui::End();
}

void GameEngineGUIWindow::Start()
{
}

void GameEngineGUIWindow::Update(float _deltaTime)
{
}


std::list<std::shared_ptr<GameEngineGUIWindow>> GameEngineGUI::guiWindows_;

GameEngineGUI::GameEngineGUI()
{
}

GameEngineGUI::~GameEngineGUI()
{
}

void GameEngineGUI::Render(GameEngineLevel* _level, float _deltaTime)
{
    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();  //<-ImGUI 렌더링 시작 함수??



    for (std::shared_ptr<GameEngineGUIWindow> guiWindow : guiWindows_)
    {
        if (true == guiWindow->IsUpdate())
        {
            guiWindow->Begin();         //필요한 ImGUI관련 렌더링 정보는 이 아래로.
            guiWindow->OnGUI(_level, _deltaTime);
            guiWindow->End();       //필요한 ImGUI관련 렌더링 정보는 이 위로.
        }
    }


    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    // Rendering
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

std::string GameEngineGUI::OpenFileDlg(const std::string& _title, const std::string& _startPath)
{
    pfd::open_file dlg = pfd::open_file(_title, _startPath, { "All Files", "*" }, pfd::opt::force_path);
    dlg.kill();
    if (false == dlg.result().empty())
    {
        return dlg.result()[0];
    }
    else
    {
        return "";
    }
}

std::string GameEngineGUI::OpenFolderDlg(const std::string& _title, const std::string& _startPath)
{
    pfd::select_folder dlg = pfd::select_folder(_title, _startPath, pfd::opt::force_path);
    dlg.kill();
    return dlg.result();
}

void GameEngineGUI::Initialize()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;
    //io.ConfigViewportsNoDefaultParent = true;
    //io.ConfigDockingAlwaysTabBar = true;
    //io.ConfigDockingTransparentPayload = true;
    //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T WORK AS EXPECTED. DON'T USE IN USER APP!
    //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; // FIXME-DPI: Experimental.

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    GameEngineDirectory fontDir;
    fontDir.MoveParentToExistChildDirectory("GameEngineResources");
    fontDir.MoveToChild("GameEngineResources");
    fontDir.MoveToChild("Fonts");
    io.Fonts->AddFontFromFileTTF(
        fontDir.PlusFilePath("malgun.ttf").c_str(),
        18.0f,
        NULL,
        io.Fonts->GetGlyphRangesKorean()
    );

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(GameEngineWindow::GetHWND());
    ImGui_ImplDX11_Init(GameEngineDevice::GetDevice(), GameEngineDevice::GetContext());

    GameEngineWindow::GetInst()->SetMessageHandler(ImGui_ImplWin32_WndProcHandler);

}

void GameEngineGUI::Destroy()
{
    //for (GameEngineGUIWindow* guiWindow : guiWindows_)
    //{
    //    if (nullptr != guiWindow)
    //    {
    //        delete guiWindow;
    //        guiWindow = nullptr;
    //    }
    //}

    guiWindows_.clear();

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}