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
	{
		template_ = CreateComponent<GameEngineTextureRenderer>();
		template_->SetPivot(PivotMode::Bot);
		template_->SetTexture("SoulCardCommon.png");
		template_->ScaleToTexture();
	}

	{
		std::shared_ptr<GameEngineTextureRenderer> linerenderer = CreateComponent<GameEngineTextureRenderer>();
		linerenderer->SetTexture("SoulCardLine.png");
		linerenderer->GetTransform().SetWorldScale(float4{ 160.f,16.f,1.f });
		linerenderer->GetTransform().SetLocalMove(float4(0.f, 164.f));
	}


	{
		icon_ = CreateComponent<GameEngineTextureRenderer>();
		icon_->GetTransform().SetLocalMove(float4(0.f, 236.f));
		icon_->GetTransform().SetWorldScale(float4{ 128.f,128.f,1.f });
	}
}

void SoulCardUI::Update(float _deltaTime)
{
}

