#include "PreCompile.h"
#include "TestLevel.h"
#include "MyTileMapRenderer.h"
#include "TileMapActor.h"
#include "TimeActor.h"
#include "StageUI.h"
#include "GlobalContentsValue.h"
#include "Mouse.h"
#include "Player.h"
#include "PlayerUI.h"
#include "Monster.h"
#include "BlackEyes.h"
#include "Brown.h"
#include "Green.h"
#include "NormalGoblin.h"
#include "RedFlyingEyes.h"
#include "FlyingEyes.h"
#include "SoundPlayer.h"
#include "FieldRenderingActor.h"

TestLevel::TestLevel(): fieldRenderingActor_(nullptr)
{
}

TestLevel::~TestLevel() 
{
}

void TestLevel::Start()
{

	GameEngineDirectory monsterDir;
	monsterDir.MoveParentToExistChildDirectory("ContentsResources");
	monsterDir.MoveToChild("ContentsResources");
	monsterDir.MoveToChild("Actor");
	monsterDir.MoveToChild("Monster");

	std::vector<GameEngineFile> monsterTexture = monsterDir.GetAllFiles();
	for (size_t i = 0; i < monsterTexture.size(); i++)
	{
		GameEngineTexture::Load(monsterTexture[i].GetFullPath());
	}


	GameEngineDirectory skillDir;
	skillDir.MoveParentToExistChildDirectory("ContentsResources");
	skillDir.MoveToChild("ContentsResources");
	skillDir.MoveToChild("Actor");
	skillDir.MoveToChild("Skill");

	std::vector<GameEngineFile> skillTexture = skillDir.GetAllFiles();
	for (size_t i = 0; i < skillTexture.size(); i++)
	{
		GameEngineTexture::Load(skillTexture[i].GetFullPath());
	}

	GameEngineDirectory WeaponDir;
	WeaponDir.MoveParentToExistChildDirectory("ContentsResources");
	WeaponDir.MoveToChild("ContentsResources");
	WeaponDir.MoveToChild("Actor");
	WeaponDir.MoveToChild("Skill");
	WeaponDir.MoveToChild("Weapon");

	std::vector<GameEngineFile> WeaponTexture = WeaponDir.GetAllFiles();
	for (size_t i = 0; i < WeaponTexture.size(); i++)
	{
		GameEngineTexture::Load(WeaponTexture[i].GetFullPath());
	}
		
	GameEngineDirectory uiTextureDir;
	uiTextureDir.MoveParentToExistChildDirectory("ContentsResources");
	uiTextureDir.MoveToChild("ContentsResources");
	uiTextureDir.MoveToChild("Texture");
	uiTextureDir.MoveToChild("UI");
	std::vector<GameEngineFile> uiTexture = uiTextureDir.GetAllFiles();

	for (size_t i = 0; i < uiTexture.size(); i++)
	{
		GameEngineTexture::Load(uiTexture[i].GetFullPath());
	}
		
	GameEngineDirectory soundDir;
	soundDir.MoveParentToExistChildDirectory("ContentsResources");
	soundDir.MoveToChild("ContentsResources");
	soundDir.MoveToChild("Sound");

	std::vector<GameEngineFile> sound = soundDir.GetAllFiles();
	for (GameEngineFile& soundPlay : sound)
	{
		GameEngineSound::LoadResource(soundPlay);
	}

	fieldRenderingActor_ = CreateActor<FieldRenderingActor>();
	fieldRenderingActor_->Initialize(
		550,
		50,
		float4(100, 100),
		60.f
	);
	fieldRenderingActor_->GetTransform().SetLocalScale(float4::White);
	fieldRenderingActor_->GetTransform().SetWorldScale(float4::White);
	fieldRenderingActor_->GetTransform().SetWorldPosition(float4::Zero);


	//std::shared_ptr< GameEngineCollision> col = GetMainCameraActor()->CreateComponent<GameEngineCollision>();
	//col->GetTransform().SetWorldScale(float4{ 1280,720 });
	//col->ChangeOrder(ObjectOrder::Camera);
	//col->SetDebugSetting(CollisionType::CT_OBB2D, float4::Zero);

	if (true == Player::GetPlayerWeakPtr().expired())
	{
		Player::CreatePlayer(this, { 0, 0 });
	}

	{
		std::shared_ptr<PlayerUI> NewPlayerUI = CreateActor<PlayerUI>(ObjectOrder::UI);
	}

	Monster::ReserveMonsters(this, 10);

	//Monster::CreateMonster<Brown>(this, 10);
	//Monster::CreateMonster<Green>(this, 10);
	//Monster::CreateMonster<NormalGoblin>(this, 10);
	Monster::CreateMonster<RedFlyingEyes>(this, 10);
	//Monster::CreateMonster<FlyingEyes>(this, 10);

	//Monster::SummonMonster<Brown>(this, 10);
	//Monster::SummonMonster<Green>(this, 10);
	//Monster::SummonMonster<NormalGoblin>(this, 10);
	Monster::SummonMonster<RedFlyingEyes>(this, 10);
	//Monster::SummonMonster<FlyingEyes>(this, 10);

	
	std::shared_ptr<Mouse> NewMouse = CreateActor<Mouse>(ObjectOrder::Mouse);

	
	//ShowCursor(false); 마우스 감추기
	CreateActor<TimeActor>();
	CreateActor<StageUI>()->SoulCoinRenderersOff();

}

void TestLevel::Update(float _DeltaTime)
{						

	PlayerMoveCamera();

	fieldRenderingActor_->GetTransform().SetWorldPosition(GetMainCameraActor()->GetTransform().GetWorldPosition());
}

void TestLevel::LevelStartEvent()
{
	SoundPlayer::BGMPlay_->ChangeBgm("ForestFightMusic.wav", 1);
}
void TestLevel::LevelEndEvent()
{
	SoundPlayer::BGMPlay_->Stop();
}

void TestLevel::PlayerMoveCamera()
{
	float Time = GameEngineTime::GetDeltaTime();
	float4 MoveVector = Player::GetPlayerInst()->GetTransform().GetWorldPosition() - GetMainCameraActorTransform().GetWorldPosition();

	if (abs(MoveVector.x) < 1.0f)
	{
		MoveVector.x = 0.f;
	}

	if (abs(MoveVector.y) < 1.0f)
	{
		MoveVector.y = 0.f;
	}

	GetMainCameraActor()->GetTransform().SetWorldMove(float4((MoveVector.x) * Time, (MoveVector.y) *1.5f * Time));

}

void TestLevel::MouseMoveCamera()
{
	float Time = GameEngineTime::GetDeltaTime();

	float4 MouseDir = float4::Zero;
	float4 CheckPos = GetMainCamera()->GetMouseWorldPositionToActor() - Player::GetPlayerInst()->GetTransform().GetWorldPosition();


		if (CheckPos.x > 360.f)
		{
			MouseDir.x = 100.f;
		}
		else if (CheckPos.x < -360.f)
		{
			MouseDir.x = -100.f;
		}

		if (CheckPos.y > 180.f)
		{
			MouseDir.y = 100.f;
		}
		else if (CheckPos.x < -180.f)
		{
			MouseDir.y = -100.f;
		}
	

	GetMainCameraActor()->GetTransform().SetWorldMove(float4((MouseDir.x) * Time, (MouseDir.y) * Time));

}


