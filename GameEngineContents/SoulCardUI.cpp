#include "PreCompile.h"
#include "SoulCardUI.h"
#include "ShopLevel.h"
#include "Player.h"
#include "ClearLevel.h"
#include "Shuriken.h"
#include "TestLevel.h"
#include "Mouse.h"
#include "DeathAura.h"
#include "GlobalContentsValue.h"

SoulCardUI::SoulCardUI() 
	: alphaTexture_(0.7f)
	, TextColor_(float4(1.f,1.f,1.f,0.9f))
	, RankColor_(float4::White)
	, ColorCheck_(Appear::False)
{
}

SoulCardUI::~SoulCardUI() 
{
	
}

void SoulCardUI::Start()
{
	std::vector <std::vector<std::shared_ptr <Skill>>> SkillList = Player::GetPlayerInst()->GetSkillManager()->GetSkillList();
	mySkill_ = SkillList[0][0];

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
		template_->GetTransform().SetWorldScale(float4{ 188.f,282.f,1.f });
		template_->GetTransform().SetLocalMove(float4(0.f, 0.f, 0.f));
		template_->ChangeCamera(CameraOrder::UICamera);
		template_->GetPixelData().mulColor_.a = alphaTexture_;
	}

	{
		linerenderer_ = CreateComponent<GameEngineTextureRenderer>();
		linerenderer_->SetTexture("SoulCardLine.png");
		linerenderer_->GetTransform().SetWorldScale(float4{ 110.f,16.f,1.f });
		linerenderer_->GetTransform().SetLocalMove(float4(0.f, 170.f, -10.f));
		linerenderer_->ChangeCamera(CameraOrder::UICamera);
		linerenderer_->GetPixelData().mulColor_.a = alphaTexture_;
	}


	{
		icon_ = CreateComponent<GameEngineTextureRenderer>();
		icon_->GetTransform().SetLocalMove(float4(0.f, 228.f, -10.f));
		icon_->GetTransform().SetWorldScale(float4{ 100.f,100.f,1.f });
		icon_->ChangeCamera(CameraOrder::UICamera);
		icon_->GetPixelData().mulColor_.a = alphaTexture_;
	}

	{
		skillName_ = CreateComponent<GameEngineFontRenderer>();
		skillName_->SetPositionMode(FontPositionMode::World);
		skillName_->SetSize(18.f);
		skillName_->SetText(mySkill_->GetSkillName(), "Free Pixel");
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
		Level_->SetText(std::to_string(mySkill_->GetCurrentlevel()) + "-> " + std::to_string(mySkill_->GetCurrentlevel() + 1) + "/ " + std::to_string(mySkill_->GetMaxLevel()));
		Level_->SetColor(TextColor_);
		Level_->ChangeCamera(CameraOrder::UICamera);
	}

	{
		Rank_ = CreateComponent<GameEngineFontRenderer>();
		Rank_->SetPositionMode(FontPositionMode::World);
		Rank_->SetText("일반", "Free Pixel");
		Rank_->SetSize(16.f);
		Rank_->GetTransform().SetLocalMove(float4(-84.f, 20.f, -10.f));
		Rank_->SetColor(RankColor_);
		Rank_->ChangeCamera(CameraOrder::UICamera);
	}

	{
		cardColision_ = CreateComponent<GameEngineCollision>();
		cardColision_->GetTransform().SetLocalMove(float4(0.f, 141.f));
		cardColision_->GetTransform().SetWorldScale(float4{ 188.f,282.f,1.f });
		cardColision_->SetDebugSetting(CollisionType::CT_AABB, float4::Red);
	}

	
}

void SoulCardUI::Update(float _deltaTime)
{



	if (GetLevel<TestLevel>() == nullptr && GetLevel<ShopLevel>() == nullptr)
	{
		if (true == GetLevel<ClearLevel>()->GetMousePointer()->IsPointing(template_->GetTransformData().worldWorldMatrix_, float4(0.f, 0.5f, 0.f, 0.f), true))
		{
			if (GameEngineInput::GetInst()->IsUp("Click"))
			{
				mySkill_->IsOnOff();
				mySkill_->Effect();
				Death();
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
	else if (GetLevel<ClearLevel>() == nullptr && GetLevel<ShopLevel>() == nullptr)
	{
		if (true == GetLevel<TestLevel>()->GetMousePointer()->IsPointing(template_->GetTransformData().worldWorldMatrix_, float4(0.f, 0.5f, 0.f, 0.f), true))
		{
			if (GameEngineInput::GetInst()->IsUp("Click"))
			{
				mySkill_->IsOnOff();
				mySkill_->Effect();
				Death();
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
	else if (GetLevel<TestLevel>() == nullptr && GetLevel<ClearLevel>() == nullptr)
	{
		if (true == GetLevel<ShopLevel>()->GetMousePointer()->IsPointing(template_->GetTransformData().worldWorldMatrix_, float4(0.f, 0.5f, 0.f, 0.f), true))
		{
			if (GameEngineInput::GetInst()->IsUp("Click"))
			{
				mySkill_->IsOnOff();
				mySkill_->Effect();
				Death();
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
	
}

void SoulCardUI::ColorChange(Appear _Value)
{
	if (Appear::True == _Value)
	{
		alphaTexture_ = 1.f;
		TextColor_.a = 1.0f;
		RankColor_.a = 1.0f;
		ColorCheck_ = Appear::True;
	
	}

	if (Appear::False == _Value)
	{
		alphaTexture_ = 0.7f;
		TextColor_.a = 0.9f;
		RankColor_.a = 0.9f;
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
	Rank_->SetColor(RankColor_);
	
}

void SoulCardUI::Setting()
{
	//CardDraw();
	std::vector <std::vector<std::shared_ptr <Skill>>> SkillList = Player::GetPlayerInst()->GetSkillManager()->GetSkillList();
	mySkill_  = SkillList[5][11];
	
	for (size_t i = 0; i < etc_.size(); i++)
	{
		etc_[i]->Death();
	}

	etc_.clear();
	{
		skillName_->SetText(mySkill_->GetSkillName(), "Free Pixel");
		icon_->SetTexture(mySkill_->GetName().data() + std::string(".png"));
	}
	{
		switch (mySkill_->GetRank())
		{
			case Rank::Spotted:
				template_->SetTexture("SoulCardSpotted.png");
				Rank_->SetText("더럽혀진", "Free Pixel");
				Rank_->SetColor(float4::White);
				RankColor_ = float4::White;
				break;
			case Rank::Normal:
				template_->SetTexture("SoulCardNormal.png");
				Rank_->SetText("일반", "Free Pixel");
				Rank_->SetColor(float4::White);
				RankColor_ = float4::White;
				break;
			case Rank::UnCommon:
				template_->SetTexture("SoulCardUnCommon.png");
				Rank_->SetText("언커먼", "Free Pixel");
				Rank_->SetColor(float4(0.f, 1.f, 0.f));
				RankColor_ = float4(0.f, 1.f, 0.f);
				break;
			case Rank::Rare:
				template_->SetTexture("SoulCardRare.png");
				Rank_->SetText("레어", "Free Pixel");
				Rank_->SetColor(float4(0.f, 0.f, 1.f));
				RankColor_ = float4(0.f, 0.f, 1.f);
				break;
			case Rank::Epic:
				template_->SetTexture("SoulCardEpic.png");
				Rank_->SetText("에픽", "Free Pixel");
				Rank_->SetColor(float4(1.0f, 0.0f, 1.f));
				RankColor_ = float4(1.0f, 0.0f, 1.f);
				break;
			default:
				break;
		}
	}

	{
		mySkill_->Init();
		Level_->SetText(std::to_string(mySkill_->GetCurrentlevel()) + "-> " + std::to_string(mySkill_->GetCurrentlevel() + 1) + "/ " + std::to_string(mySkill_->GetMaxLevel()), "Free Pixel");
		std::string Text = reinterpret_cast<DeathAura*>(mySkill_.get())->GetEtc();
		size_t EntryIndex = Text.find("\n");
		size_t firstIndex = 0;
		std::string Text2 = Text.substr(0, EntryIndex);
		for (size_t i = 0; i < 8; i++)
		{
			etc_.push_back(CreateComponent<GameEngineFontRenderer>());
			etc_[i]->SetPositionMode(FontPositionMode::World);
			etc_[i]->SetSize(14.f);
			Text2 = Text.substr(firstIndex, EntryIndex - firstIndex) + "";
			etc_[i]->SetText(Text2);
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

void SoulCardUI::CardDraw()
{
	if (mySkill_ != nullptr)
	{
		mySkill_->IsOnOff();
	}

	std::vector <std::vector<std::shared_ptr <Skill>>> SkillList = Player::GetPlayerInst()->GetSkillManager()->GetSkillList();
	int RankRandom = 0;
	int IndexRandom = 0;
	int Randomnum = GameEngineRandom::mainRandom_.RandomInt(1, 100);

	if (Randomnum <= 30)
	{
		RankRandom = 0;
	}

	else if (Randomnum <= 50)
	{
		RankRandom = 1;
	}
	else if (Randomnum <= 70)
	{
		RankRandom = 2;
	}

	else if (Randomnum <= 85)
	{
		RankRandom = 3;
	}

	else if (Randomnum <= 95)
	{
		RankRandom = 4;
	}

	else if (Randomnum <= 100)
	{
		RankRandom = 4;
	}

	IndexRandom = GameEngineRandom::mainRandom_.RandomInt(0, static_cast<int>(SkillList[RankRandom].size() - 1));


	mySkill_ = SkillList[RankRandom][IndexRandom];

	while (mySkill_->GetCurrentlevel() == mySkill_->GetMaxLevel() || true == mySkill_->GetIsOn())
	{
		std::vector <std::vector<std::shared_ptr <Skill>>> SkillList = Player::GetPlayerInst()->GetSkillManager()->GetSkillList();
		int RankRandom = 0;
		int IndexRandom = 0;
		int Randomnum = GameEngineRandom::mainRandom_.RandomInt(1, 100);

		if (Randomnum <= 30)
		{
			RankRandom = 0;
		}

		else if (Randomnum <= 50)
		{
			RankRandom = 1;
		}
		else if (Randomnum <= 70)
		{
			RankRandom = 2;
		}

		else if (Randomnum <= 85)
		{
			RankRandom = 3;
		}

		else if (Randomnum <= 95)
		{
			RankRandom = 4;
		}

		else if (Randomnum <= 100)
		{
			RankRandom = 4;
		}

		IndexRandom = GameEngineRandom::mainRandom_.RandomInt(0, static_cast<int>(SkillList[RankRandom].size() - 1));


		mySkill_ = SkillList[RankRandom][IndexRandom];
	}

	mySkill_->IsOnOn();
}


void SoulCardUI::CardRelease()
{
	if (mySkill_ != nullptr)
	{
		mySkill_->IsOnOff();
	}
}