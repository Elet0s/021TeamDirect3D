#include "PreCompile.h"
#include "MapEditorWindow.h"
#include "TileMapActor.h"
#include "TileMapRenderer.h"

MapEditorWindow::MapEditorWindow() : tileMap_(nullptr), scale_{ 30, 30 }, selectTile_(-1)
{
}

MapEditorWindow::~MapEditorWindow()
{
}

void MapEditorWindow::Initialize(GameEngineLevel* _level)
{
    if (false == GameEngineInput::GetInst()->IsKey("TileSet"))
    {
        GameEngineInput::GetInst()->CreateKey("TileSet", VK_LBUTTON);
    }
}

void MapEditorWindow::OnGUI(GameEngineLevel* _level, float _deltaTime)
{
    // ImGui::PushID
    if (true == ImGui::Button("FolderTextureLoad"))
    {
        GameEngineDirectory Dir;
        Dir.MoveParentToExistChildDirectory("ContentsResources");
        Dir.MoveToChild("ContentsResources");
        Dir.MoveToChild("Texture");
        Dir.MoveToChild("Map");



        std::string path 
            = GameEngineGUI::OpenFolderDlg(GameEngineString::AnsiToUTF8Return("폴더 텍스처 로드"), Dir.GetFullPath());

        if (false == path.empty())
        {
            selectFolderTexture_ = GameEnginePath::GetFileName(path);

            GameEngineFolderTexture::Load(path.c_str());
        }
    }

    if (false == selectFolderTexture_.empty())
    {
        ImGui::SameLine();
        ImGui::Text(selectFolderTexture_.c_str());
        ImGui::InputInt2("Scale", scale_);

        if (true == ImGui::Button("Create a Map"))
        {
           //this->tileMap_->tileRenderer_->CreateIsometricTileMap(scale_[0], scale_[1], { 64, 32 }, selectFolderTexture_, 32);
        }


        std::string selectIndex = "Select Index = ";
        int x = 0;
        int y = 0;
        //;this->tileMap_->tileRenderer_->GetTileIndex(_level->GetMainCamera()->GetMouseWorldPosition(), x, y);

        selectIndex += std::to_string(x);
        selectIndex += " " + std::to_string(y);

        ImGui::Text(selectIndex.c_str());
    }

    std::shared_ptr<GameEngineFolderTexture> selectFolderTexture = GameEngineFolderTexture::Find(selectFolderTexture_);

    if (nullptr != selectFolderTexture)
    {
        ImGui::BeginChildFrame(ImGui::GetID("TileSelect"), { 90 * 5, 500 });

        for (size_t i = 0; i < selectFolderTexture->GetTextureCount(); i++)
        {
            std::shared_ptr<GameEngineTexture> tileImage = selectFolderTexture->GetTexture(i);
            if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(tileImage->CreateShaderResourceView()), { 64, 32 }))
            {
                selectTile_ = i;
            }

            if (0 != (i + 1) % 5)
            {
                ImGui::SameLine();
            }
        }
        ImGui::EndChildFrame();
    }

    if (true == GameEngineInput::GetInst()->IsDown("TileSet")
        && nullptr != selectFolderTexture
        && -1 != selectTile_
        && selectTile_ < selectFolderTexture->GetTextureCount())
    {

        //float4 mousePos = _level->GetMainCamera()->GetMouseWorldPosition();

        //tileMap_->tileRenderer_->SetTileIndex(mousePos, selectTile_);
    }
}
