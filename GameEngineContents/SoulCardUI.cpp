#include "PreCompile.h"
#include "SoulCardUI.h"

SoulCardUI::SoulCardUI() 
{
}

SoulCardUI::~SoulCardUI() 
{
}

void SoulCardUI::Start()
{
	if (nullptr == GameEngineTexture::Find("SoulCardCommon.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("UI");
		Dir.MoveToChild("SoulCardUI");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFiles();
		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());

		}
	}

	etc_.resize(8);

	{
		template_ = CreateComponent<GameEngineTextureRenderer>();
		template_->SetPivot(PivotMode::Bot);
		template_->SetTexture("SoulCardNormal.png");
		template_->GetTransform().SetWorldScale(float4{ 188.f,282.f,1.f });
		template_->ChangeCamera(CameraOrder::UICamera);
		template_->GetPixelData().mulColor_.a = 0.7f;
	}

	{
		linerenderer_ = CreateComponent<GameEngineTextureRenderer>();
		linerenderer_->SetTexture("SoulCardLine.png");
		linerenderer_->GetTransform().SetWorldScale(float4{ 110.f,16.f,1.f });
		linerenderer_->GetTransform().SetLocalMove(float4(0.f, 170.f, -1.f));
		linerenderer_->ChangeCamera(CameraOrder::UICamera);
		linerenderer_->GetPixelData().mulColor_.a = 0.7f;
	}


	{
		icon_ = CreateComponent<GameEngineTextureRenderer>();
		icon_->SetTexture("죽음의오라.png");
		icon_->GetTransform().SetLocalMove(float4(0.f, 228.f, -1.f));
		icon_->GetTransform().SetWorldScale(float4{ 100.f,100.f,1.f });
		icon_->ChangeCamera(CameraOrder::UICamera);
		icon_->GetPixelData().mulColor_.a = 0.7f;
	}

	{
		skillName_ = CreateComponent<GameEngineFontRenderer>();
		skillName_->SetPositionMode(FontPositionMode::World);
		skillName_->SetSize(18.f);
		skillName_->SetText("죽음의오라", "Free Pixel");
		skillName_->SetLeftAndRightSort(LeftAndRightSort::Center);
		skillName_->GetTransform().SetLocalMove(float4(0.f, 164.f, -10.f));
		skillName_->ChangeCamera(CameraOrder::UICamera);
		skillName_->SetColor(float4(1.f,1.f,1.f, 0.8f));
	}

	
	{
		std::string Text = "1.13 -> 1.58 의 피해\n1.00초->0.60초 마다 공격\n투사체 2->3 개 ";
		size_t EntryIndex = Text.find("\n");
		size_t firstIndex = 0;
		std::string Text2 = Text.substr(0, EntryIndex);
		for (size_t i = 0; i < etc_.size(); i++)
		{
			etc_[i] = CreateComponent<GameEngineFontRenderer>();
			etc_[i]->SetPositionMode(FontPositionMode::World);
			etc_[i]->SetSize(14.f);
			Text2 = Text.substr(firstIndex, EntryIndex - firstIndex) + "";
			etc_[i]->SetText(Text2, "Free Pixel");
			etc_[i]->SetTopAndBotSort(TopAndBotSort::Top);
			etc_[i]->SetLeftAndRightSort(LeftAndRightSort::Center);
			etc_[i]->GetTransform().SetLocalMove(float4(0.f, 144.f - 16.f * i, -10.f));
			etc_[i]->ChangeCamera(CameraOrder::UICamera);
			etc_[i]->SetColor(float4(1.f, 1.f, 1.f, 0.8f));

			if (Text.npos ==EntryIndex)
			{	
				break;
			}

			firstIndex = EntryIndex + 1;
			EntryIndex = Text.find("\n", firstIndex);
		}
		
	}
	{
		std::shared_ptr<GameEngineFontRenderer>font = CreateComponent<GameEngineFontRenderer>();
		font->SetPositionMode(FontPositionMode::World);
		font->SetSize(18.f);
		font->SetText("레벨 : ", "Free Pixel");
		font->GetTransform().SetLocalMove(float4(-84.f, 40.f, -10.f));
		font->SetColor(float4(1.f, 1.f, 1.f, 0.9f));
		font->ChangeCamera(CameraOrder::UICamera);
	}

	{
		Level_ = CreateComponent<GameEngineFontRenderer>();
		Level_->SetPositionMode(FontPositionMode::World);
		Level_->SetSize(14.f);
		Level_-> GetTransform().SetLocalMove(float4(-26.f, 35.f, -10.f));
		Level_->SetText("0-> 1 / 7");
		Level_->SetColor(float4(1.f, 1.f, 1.f, 0.9f));
	}

	{
		Rank_ = CreateComponent<GameEngineFontRenderer>();
		Rank_->SetPositionMode(FontPositionMode::World);
		Rank_->SetSize(16.f);
		Rank_->GetTransform().SetLocalMove(float4(-84.f, 20.f, -10.f));
		Rank_->SetText("더럽혀진");
		Rank_->SetColor(float4(1.f, 1.f, 1.f, 0.9f));
	}
}

void SoulCardUI::Update(float _deltaTime)
{
}

