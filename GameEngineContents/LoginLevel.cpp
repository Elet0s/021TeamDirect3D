#include "PreCompile.h"
#include "LoginLevel.h"
#include "LoginUI.h"
#include "Enums.h"
#include "Player.h"
#include "GlobalContentsValue.h"

LoginLevel::LoginLevel()
{
}

LoginLevel::~LoginLevel()
{
}

void LoginLevel::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("P"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChange", 'P');
	}

	//GameEngineCameraActor* tempCameraActor = CreateActor<GameEngineCameraActor>(GameObjectGroup::UI);
	//tempCameraActor->GetTransform().SetLocalPosition(0, 0, -100);
	//tempCameraActor->GetCameraComponent()->SetProjectionMode(CameraProjectionMode::Orthographic);
	//[1]  [0]  [0]   [0]
	//[0]  [1]  [0]   [0]
	//[0]  [0]  [1]   [0]	앞을 보고 있다.
	//[0]  [0]  [-100][0]	뒤로 100만큼 물러나서.



}

void LoginLevel::Update(float _deltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Play");
	}

	if (true == GameEngineInput::GetInst()->IsDown("FreeCameraModeOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}
}

void LoginLevel::End()
{
}

void LoginLevel::LevelStartEvent()
{
	if (nullptr == GameEngineTexture::Find("LoginBackground.png"))
	{
		GameEngineDirectory dir;
		dir.MoveParentToExistChildDirectory("ContentsResources");
		dir.MoveToChild("ContentsResources");
		dir.MoveToChild("Texture");
		dir.MoveToChild("Login");

		std::vector<GameEngineFile> shaders = dir.GetAllFiles();

		for (size_t i = 0; i < shaders.size(); i++)
		{
			GameEngineTexture::Load(shaders[i].GetFullPath());
		}
	}

	LoginUI* ptr = CreateActor<LoginUI>(GameObjectGroup::UI);
	ptr->CreateComponent<GameEngineCollision>();
}
