#include "PreCompile.h"
#include "SoulCardUI.h"
#include "DeathAura.h"
#include "GlobalContentsValue.h"

SoulCardUI::SoulCardUI() 
	: alphaTexture_(0.7f)
	, TextColor_(float4(1.f,1.f,1.f,0.9f))
	, ColorCheck_(Appear::False)
{
}

SoulCardUI::~SoulCardUI() 
{
	delete mySkill_;
}

void SoulCardUI::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("click"))
	{
		GameEngineInput::GetInst()->CreateKey("Click", VK_LBUTTON);
	}
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

	etc_.reserve(8);

	{
		template_ = CreateComponent<GameEngineTextureRenderer>();
		template_->SetPivot(PivotMode::Bot);
		template_->SetTexture("SoulCardNormal.png");
		template_->GetTransform().SetWorldScale(float4{ 188.f,282.f,1.f });
		template_->ChangeCamera(CameraOrder::UICamera);
		template_->GetPixelData().mulColor_.a = alphaTexture_;
	}

	{
		linerenderer_ = CreateComponent<GameEngineTextureRenderer>();
		linerenderer_->SetTexture("SoulCardLine.png");
		linerenderer_->GetTransform().SetWorldScale(float4{ 110.f,16.f,1.f });
		linerenderer_->GetTransform().SetLocalMove(float4(0.f, 170.f, -1.f));
		linerenderer_->ChangeCamera(CameraOrder::UICamera);
		linerenderer_->GetPixelData().mulColor_.a = alphaTexture_;
	}


	{
		icon_ = CreateComponent<GameEngineTextureRenderer>();
		icon_->SetTexture("죽음의오라.png");
		icon_->GetTransform().SetLocalMove(float4(0.f, 228.f, -1.f));
		icon_->GetTransform().SetWorldScale(float4{ 100.f,100.f,1.f });
		icon_->ChangeCamera(CameraOrder::UICamera);
		icon_->GetPixelData().mulColor_.a = alphaTexture_;
	}

	{
		skillName_ = CreateComponent<GameEngineFontRenderer>();
		skillName_->SetPositionMode(FontPositionMode::World);
		skillName_->SetSize(18.f);
		skillName_->SetText("죽음의오라", "Free Pixel");
		skillName_->SetLeftAndRightSort(LeftAndRightSort::Center);
		skillName_->GetTransform().SetLocalMove(float4(0.f, 164.f, -10.f));
		skillName_->ChangeCamera(CameraOrder::UICamera);
		skillName_->SetColor(TextColor_);
	}

	
	
	{
		std::shared_ptr<GameEngineFontRenderer>font = CreateComponent<GameEngineFontRenderer>();
		font->SetPositionMode(FontPositionMode::World);
		font->SetSize(18.f);
		font->SetText("레벨 : ", "Free Pixel");
		font->GetTransform().SetLocalMove(float4(-84.f, 40.f, -10.f));
		font->SetColor(TextColor_);
		font->ChangeCamera(CameraOrder::UICamera);
	}

	{
		Level_ = CreateComponent<GameEngineFontRenderer>();
		Level_->SetPositionMode(FontPositionMode::World);
		Level_->SetSize(16.f);
		Level_-> GetTransform().SetLocalMove(float4(-26.f, 35.f, -10.f));
		Level_->SetText("0-> 1 / 7", "Free Pixel");
		Level_->SetColor(TextColor_);
		Level_->ChangeCamera(CameraOrder::UICamera);
	}

	{
		Rank_ = CreateComponent<GameEngineFontRenderer>();
		Rank_->SetPositionMode(FontPositionMode::World);
		Rank_->SetSize(16.f);
		Rank_->GetTransform().SetLocalMove(float4(-84.f, 20.f, -10.f));
		Rank_->SetText("더럽혀진","Free Pixel");
		Rank_->SetColor(TextColor_);
		Rank_->ChangeCamera(CameraOrder::UICamera);
	}

	{
		cardColision_ = CreateComponent<GameEngineCollision>();
		cardColision_->GetTransform().SetLocalMove(float4(0.f, 141.f));
		cardColision_->GetTransform().SetWorldScale(float4{ 188.f,282.f,1.f });
		cardColision_->SetDebugSetting(CollisionType::CT_AABB, float4::Red);
	}

	mySkill_ = new DeathAura();
}

void SoulCardUI::Update(float _deltaTime)
{
	if(true == cardColision_->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::Mouse, CollisionType::CT_AABB2D))
	{
		if (GameEngineInput::GetInst()->IsDown("Click"))
		{
			mySkill_->Effect();
			Setting();
		}
		ColorChange(Appear::True);
	}
	else
	{	
		if (ColorCheck_ == Appear::True)
		{
			ColorChange(Appear::False);
		}
	}
}

void SoulCardUI::ColorChange(Appear _Value)
{
	if (Appear::True == _Value)
	{
		alphaTexture_ = 1.f;
		TextColor_ = float4::White;
		ColorCheck_ = Appear::True;
	
	}

	if (Appear::False == _Value)
	{
		alphaTexture_ = 0.7f;
		TextColor_ = float4(1.f,1.f,1.f,0.9f);
		ColorCheck_ = Appear::False;
	}

	template_->GetPixelData().mulColor_.a = alphaTexture_;
	linerenderer_->GetPixelData().mulColor_.a = alphaTexture_;
	icon_->GetPixelData().mulColor_.a = alphaTexture_;
	skillName_->SetColor(TextColor_);
	for (size_t i = 0; i < etc_.size(); i++)
	{
		etc_[i]->SetColor(TextColor_);
	}
	Level_->SetColor(TextColor_);
	Rank_->SetColor(TextColor_);
	
}

void SoulCardUI::Setting()
{
	DeathAura Skill = DeathAura();

	
	for (size_t i = 0; i < etc_.size(); i++)
	{
		etc_[i]->Death();
	}

	etc_.clear();

	{
		mySkill_->Init();
		std::string Text = reinterpret_cast<DeathAura*>(mySkill_)->GetEtc();
		///if(스킬 레벨이 0이 아니면 )
		//  std::string Text = "범위 내 근처의 적에게 지속\n피해를 입힙니다\n치명타가 발생하지 않습니다\n0.75 -> 다음 레벨 데미지의 피해\n0.25초 다음 레벨 공격속도 마다 공격\n범위2.00m -> 다음레벨 범위";
		size_t EntryIndex = Text.find("\n");
		size_t firstIndex = 0;
		std::string Text2 = Text.substr(0, EntryIndex);
		for (size_t i = 0; i < 8; i++)
		{
			etc_.push_back(CreateComponent<GameEngineFontRenderer>());
			etc_[i]->SetPositionMode(FontPositionMode::World);
			etc_[i]->SetSize(14.f);
			Text2 = Text.substr(firstIndex, EntryIndex - firstIndex) + "";
			etc_[i]->SetText(Text2, "Free Pixel");
			etc_[i]->SetTopAndBotSort(TopAndBotSort::Top);
			etc_[i]->SetLeftAndRightSort(LeftAndRightSort::Center);
			etc_[i]->GetTransform().SetLocalMove(float4(0.f, 144.f - 16.f * i, -10.f));
			etc_[i]->ChangeCamera(CameraOrder::UICamera);
			etc_[i]->SetColor(TextColor_);
			if (Text.npos == EntryIndex)
			{
				break;
			}

			firstIndex = EntryIndex + 1;
			EntryIndex = Text.find("\n", firstIndex);
		}

	}
}