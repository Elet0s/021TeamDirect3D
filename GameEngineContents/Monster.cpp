#include "PreCompile.h"
#include "Monster.h"
#include "GlobalContentsValue.h"
#include "Player.h"

Monster::Monster()
	:speed_(0)
	, MXmove_(0)	
	, MYmove_(0)
	,collision_()
	,monsterrenderer_()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
	if (nullptr == GameEngineTexture::Find("BlackEyes.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistChildDirectory("ContentsResources");
		Dir.MoveToChild("ContentsResources");
		Dir.MoveToChild("Monster");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFiles();
		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());

		}
		///////////////�ؽ�ó�ε�///////////////

		GameEngineTexture::Cut("BlackEyes.png", 6, 1);
		///////////////�ؽ�ó cut///////////////
	}

	monsterrenderer_ = CreateComponent<GameEngineTextureRenderer>();
	
	monsterrenderer_->GetTransform().SetLocalScale(100, 100, 100);
	monsterrenderer_->GetTransform().SetLocalPosition(0, 0, -100);
	monsterrenderer_->CreateFrameAnimation_CutTexture("BlackEyes", FrameAnimation_Desc("BlackEyes.png", 0, 5, 0.2f));
	monsterrenderer_->ChangeFrameAnimation("BlackEyes");

	GetTransform().SetWorldPosition(static_cast<float>(GameEngineRandom::mainRandom_.RandomInt(1, 1280)), static_cast<float>(-(GameEngineRandom::mainRandom_.RandomInt(1, 640))), 0.0f);
}
void Monster::Chaseplayer()
{
	float mx = GetTransform().GetWorldPosition().x;
	float my = GetTransform().GetWorldPosition().y;
	float px	= Player::GetMainPlayer()->GetTransform().GetWorldPosition().x;
	float py = Player::GetMainPlayer()->GetTransform().GetWorldPosition().y;
	float RangeX = abs(mx - px) / (abs(mx - px)+ abs(my - py)); //�밢���̵��� ���� ������
	float RangeY = abs(my - py) / (abs(mx - px) + abs(my - py));
	if (mx -px < 0)
	{
		MXmove_ = mx + 1.0f * RangeX;
	}
	else if (mx - px >=0)
	{
		MXmove_ = mx - 1.0f * RangeX;
	}
	if (my -py < 0)
	{
		MYmove_ = my + 1.0f * RangeY;
	}
	else if (my - py >= 0)
	{
		MYmove_ = my - 1.0f * RangeY;
	}


	GetTransform().SetWorldPosition(MXmove_, MYmove_, 0.0f);
}

void Monster::Update(float _deltaTime)
{
	Chaseplayer();
}

void Monster::End()
{
}

