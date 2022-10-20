#include "PreCompile.h"
#include "MetaSpriteWindow.h"

MetaSpriteWindow::MetaSpriteWindow()
	: curFrame_(0),
	renderer_(nullptr),
	curMetaFolder_(),
	curAtlasFolder_(), 
	curMetaFile_(),
	curAtlasFile_(),
	targetTexture_(nullptr)
{
}

MetaSpriteWindow::~MetaSpriteWindow()
{
}

void MetaSpriteWindow::Initialize(GameEngineLevel* _level)
{
}

void MetaSpriteWindow::OnGUI(GameEngineLevel* _level, float _deltaTime)
{
	AtlasFileButton(_level);
	MetaFileButton(_level);
}

void MetaSpriteWindow::MetaFileButton(GameEngineLevel* _level)
{
	if (nullptr == this->targetTexture_)
	{
		return;
	}

	if (true == ImGui::Button("Meta File Load") && 0 == targetTexture_->GetCutCount())
	{
		std::string path = GameEngineGUI::OpenFileDlg(
			GameEngineString::AnsiToUTF8Return("메타 파일 로드"),
			metaDir_.GetFullPath()
		);

		if (false == path.empty())
		{
			GameEngineFile loadFile = GameEngineFile(path);
			loadFile.Open(OpenMode::Read, FileMode::Text);

			std::string allText = loadFile.GetString();

			size_t  startPos = 0;

			while (true)
			{
				startPos = allText.find("rect:", startPos);
				if (std::string::npos == startPos)
				{
					break;
				}

				size_t endPos = allText.find("outLine:", startPos);
				if (std::string::npos == startPos)
				{
					break;
				}

				std::string cutDataString = allText.substr(startPos, endPos - startPos);

				int startX = 0;
				int startY = 0;
				int width = 0;
				int height = 0;

				{
					std::string FindString = "x:";
					size_t DataStartPos = cutDataString.find(FindString);
					size_t DataEndpos = cutDataString.find("\n", DataStartPos);
					std::string XString = cutDataString.substr(DataStartPos + FindString.size(), DataEndpos - DataStartPos + FindString.size());
					startX = atoi(XString.c_str());
				}

				{
					std::string FindString = "y:";
					size_t DataStartPos = cutDataString.find(FindString);
					size_t DataEndpos = cutDataString.find("\n", DataStartPos);
					std::string XString = cutDataString.substr(DataStartPos + FindString.size(), DataEndpos - DataStartPos + FindString.size());
					startY = atoi(XString.c_str());
				}

				{
					std::string FindString = "width:";
					size_t DataStartPos = cutDataString.find(FindString);
					size_t DataEndpos = cutDataString.find("\n", DataStartPos);
					std::string XString = cutDataString.substr(DataStartPos + FindString.size(), DataEndpos - DataStartPos + FindString.size());
					width = atoi(XString.c_str());
				}

				{
					std::string FindString = "height:";
					size_t DataStartPos = cutDataString.find(FindString);
					size_t DataEndpos = cutDataString.find("\n", DataStartPos);
					std::string XString = cutDataString.substr(DataStartPos + FindString.size(), DataEndpos - DataStartPos + FindString.size());
					height = atoi(XString.c_str());
				}

				std::string debugText;
				debugText += "StartX: " + std::to_string(startX) + ", ";
				debugText += "StartY: " + std::to_string(startY) + ", ";
				debugText += "Width: " + std::to_string(width) + ", ";
				debugText += "Height: " + std::to_string(height) + ". \n";

				GameEngineDebug::OutputString(debugText.c_str());

				targetTexture_->Cut(startX, static_cast<UINT>(targetTexture_->GetScale().y - startY - height), width, height);
				++startPos;
			}

			GameEngineActor* newActor = _level->CreateActor<GameEngineActor>();
			newActor->GetTransform().SetLocalPosition(-500, 0, 0);

			renderer_ = newActor->CreateComponent<GameEngineTextureRenderer>();
			renderer_->SetTexture(targetTexture_, 0);
			renderer_->SetSamplingMode_Point();
			renderer_->ScaleToCutTexture(2);
		}
	}

	if (nullptr != targetTexture_ && 0 != targetTexture_->GetCutCount())
	{
		ImGui::SliderInt(
			"Image Index",
			&curFrame_,
			0,
			static_cast<int>(targetTexture_->GetCutCount() - 1)
		);
		renderer_->SetTexture(targetTexture_, curFrame_);
		renderer_->ScaleToCutTexture(curFrame_);
	}

	if (nullptr != targetTexture_)
	{
		float4 imagePos = targetTexture_->GetScale().Half();
		imagePos.y = -imagePos.y;

		GameEngineDebug::DrawTexture(targetTexture_, imagePos);

		for (int i = 0; i < targetTexture_->GetCutCount(); i++)
		{
			float4 pos = targetTexture_->GetCutPos(i);
			float4 scale = targetTexture_->GetCutScale(i);

			pos.y = -pos.y;
			pos.x += scale.x * 0.5f;
			pos.y -= scale.y * 0.5f;

			GameEngineDebug::DrawBox(pos, scale, float4::Zero, float4(1.f, 0.f, 0.f, 0.5f));
		}
	}

	if (false == curMetaFolder_.empty())
	{
		ImGui::SameLine();
		ImGui::Text(curMetaFolder_.c_str());
	}
}

void MetaSpriteWindow::AtlasFileButton(GameEngineLevel* _level)
{
	if (true == ImGui::Button("Atlas File Load"))
	{
		std::string path = GameEngineGUI::OpenFileDlg(
			GameEngineString::AnsiToUTF8Return("아틀라스 시트 로드"),
			metaDir_.GetFullPath());

		if (false == path.empty())
		{
			targetTexture_ = GameEngineTexture::Load(path);
		}
	}

	if (false == curAtlasFolder_.empty())
	{
		ImGui::SameLine();
		ImGui::Text(targetTexture_->GetNameCopy().c_str());
	}
}
