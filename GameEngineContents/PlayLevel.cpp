#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "Monster.h"


PlayLevel::PlayLevel() 
	: monsterActor_(nullptr)
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
	//GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	//
	//GameEngineDevice::GetBackBuffer()->AddEffect<GameEngineBlur>();
	//
	//GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

	GameEngineDirectory tempDir;
	tempDir.MoveParentToExistChildDirectory("ContentsResources");
	tempDir.MoveToChild("ContentsResources");
	tempDir.MoveToChild("Texture");
	tempDir.MoveToChild("Test");

	GameEngineFolderTexture::Load(tempDir.GetFullPath());


	if (false == GameEngineInput::GetInst()->IsKey("FreeCameraModeOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameraModeOnOff", 'O');
	}
	
	GetMainCamera()->SetProjectionMode(CameraProjectionMode::Orthographic);


	monsterActor_ = CreateActor<Monster>(ObjectOrder::Monster);
	monsterActor_->GetTransform().SetWorldPosition(200, 0, 0);
	monsterActor_->GetTransform().SetWorldScale(1, 1, 1);
}

void PlayLevel::Update(float _deltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("FreeCameraModeOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Login");
	}

	GameEngineStatusWindow::AddDebugRenderTarget("Backbuffer RenderTarget", GameEngineDevice::GetBackBuffer());
	GameEngineStatusWindow::AddDebugRenderTarget("MainCamera RenderTarget", GetMainCamera()->GetCameraRenderTarget());
	GameEngineStatusWindow::AddDebugRenderTarget("UICamera RenderTarget", GetUICamera()->GetCameraRenderTarget());
}

void PlayLevel::End()
{
}

void PlayLevel::LevelStartEvent()
{
	if (nullptr == Player::GetMainPlayer())
	{
		Player* newPlayer = CreateActor<Player>(ObjectOrder::Player);
		newPlayer->SetLevelOverOn();
	}
}
