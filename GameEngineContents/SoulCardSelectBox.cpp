#include "PreCompile.h"
#include "SoulCardSelectBox.h"
#include "SoulCardUI.h"


SoulCardSelectBox::SoulCardSelectBox() 
{
}

SoulCardSelectBox::~SoulCardSelectBox() 
{
}


void SoulCardSelectBox::Start()
{
	if (nullptr == GameEngineTexture::Find("SoulCardNormal.png"))
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

	std::shared_ptr<GameEngineTextureRenderer> Box = CreateComponent<GameEngineTextureRenderer>();
	Box->SetTexture("SoulCardSelectTemplate - 복사본.png");
	Box->ScaleToTexture();
	//Box->GetPixelData().mulColor_.a = 0.7f;

	{
		Cards[0] = GetLevel()->CreateActor<SoulCardUI>();
		Cards[0]->GetTransform().SetLocalMove(float4(-200.f, -200.f));
		Cards[0]->Setting();

		Cards[1] = GetLevel()->CreateActor<SoulCardUI>();
		Cards[1]->GetTransform().SetLocalMove(float4(10.f, -200.f));
		Cards[1]->Setting();

		Cards[2] = GetLevel()->CreateActor<SoulCardUI>();
		Cards[2]->GetTransform().SetLocalMove(float4(220.f, -200.f));
		Cards[2]->Setting();
	}
	

	{
		std::shared_ptr<GameEngineFontRenderer> Font0 = CreateComponent<GameEngineFontRenderer>();
		Font0->SetTextPosition(float4(640.f, 120.f));
		Font0->SetLeftAndRightSort(LeftAndRightSort::Center);
		Font0->SetSize(40.f);
		Font0->SetText("영혼이 강해지고 있습니다!");

		std::shared_ptr<GameEngineFontRenderer> Font1 = CreateComponent<GameEngineFontRenderer>();
		Font1->SetTextPosition(float4(640.f, 160.f));
		Font1->SetLeftAndRightSort(LeftAndRightSort::Center);
		Font1->SetSize(36.f);
		Font1->SetText("소울카드를 선택하세요");
	}
}

void SoulCardSelectBox::Update(float _deltaTime)
{

}
