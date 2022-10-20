#include "PreCompile.h"
#include "GameEngineCore.h"
#include "GameEngineLevel.h"
#include "GameEngineDevice.h"
#include "GameEngineGUI.h"
#include "GameEngineCamera.h"
#include "GameEngineCameraActor.h"
#include "GameEngineCoreDebug.h"

#pragma comment(lib, "GameEngineBase.lib")

GameEngineLevel* GameEngineCore::currentLevel_ = nullptr;
GameEngineLevel* GameEngineCore::nextLevel_ = nullptr;

std::map<std::string, GameEngineLevel*> GameEngineCore::allLevels_;

GameEngineCore::GameEngineCore()
{
}

GameEngineCore::~GameEngineCore()
{
}

bool GameEngineCore::ChangeLevel(const std::string& _levelName)
{
	std::string uppercaseLevelName = GameEngineString::ToUpperReturn(_levelName);

	nextLevel_ = FindLevel(uppercaseLevelName);
	if (nullptr == nextLevel_)
	{
		MsgBoxAssertString(_levelName + ": 그런 이름의 레벨이 존재하지 않습니다.");
		return false;
	}
	else
	{
		return true;
	}
}

void GameEngineCore::WindowCreate(const std::string& _title, GameEngineCore* _userCore)
{
	GameEngineWindow::GetInst()->CreateGameWindow(nullptr, _title.c_str());
	//윈도우 핸들 생성.

	GameEngineWindow::GetInst()->SetWindowScaleAndPosition(
		_userCore->StartWindowPosition(), _userCore->StartWindowSize());
	//윈도우 생성 위치와 크기 조정.

	GameEngineWindow::GetInst()->ShowGameWindow();
	//윈도우 생성.
	
	GameEngineDevice::Initialize();
	//다이렉트x 디바이스, DC, 스왑체인 생성.

	GameEngineWindow::GetInst()->MessageLoop(
		std::bind(&GameEngineCore::CoreStart, _userCore),
		std::bind(&GameEngineCore::CoreUpdate, _userCore),
		std::bind(&GameEngineCore::CoreEnd, _userCore)
	);
	//게임 구동.

}

void GameEngineCore::CoreStart(GameEngineCore* _userCore)
{
	EngineResourceInitialize();
	//엔진코어 초기화 및 각종 엔진 리소스 준비.
	//유저코어의 스타트 이전에 엔진 리소스 준비가 끝나있어야 한다.

	GameEngineDevice::CreateSwapChain();
	//스왑체인 생성.

	GameEngineDebug::Debug3DInitialize();

	GameEngineGUI::Initialize();
	//ImGUI 초기화.

	_userCore->Start();
}

void GameEngineCore::CoreUpdate(GameEngineCore* _userCore)
{

	if (nullptr != nextLevel_)
	{
		if (nullptr != currentLevel_)
		{
			currentLevel_->ActorLevelEndEvent();
			currentLevel_->LevelEndEvent();
			currentLevel_->OverChildMove(nextLevel_);	//원하는 오브젝트를 다음 레벨로 넘긴다. 
		}
		currentLevel_ = nextLevel_;
		nextLevel_ = nullptr;
		currentLevel_->LevelStartEvent();
		currentLevel_->ActorLevelStartEvent();

		currentLevel_->ResetAccTime();
		GameEngineTime::GetInst()->Reset();
	}

	if (nullptr == currentLevel_)
	{
		MsgBoxAssert("currentLevel_이 비었습니다.");
		return;
	}

	GameEngineTime::GetInst()->Update();

	GameEngineSound::Update();

	float deltaTime = GameEngineTime::GetDeltaTime();

	GameEngineInput::GetInst()->Update(deltaTime);

	if (true == GameEngineTime::IsUpdateOn())
	{
		_userCore->Update(deltaTime);

		currentLevel_->LevelUpdate(deltaTime);
	}
}

void GameEngineCore::CoreEnd(GameEngineCore* _userCore)
{
	_userCore->End();

	for (std::pair<std::string, GameEngineLevel*> levelPair : allLevels_)
	{
		if (nullptr != levelPair.second)
		{
			delete levelPair.second;
			levelPair.second = nullptr;
		}
	}

	GameEngineGUI::Destroy();
	//텍스처 등의 리소스를 쓸 수도 있으니 리소스보다 먼저 파괴한다.

	GameEngineDebug::Debug3DDestroy();
	//동적할당으로 생성한 렌더유닛들을 파괴한다.

	EngineResourceDestroy();

	GameEngineWindow::Destroy();
	GameEngineInput::Destroy();
	GameEngineDebug::Destroy();
	GameEngineTime::Destroy();
}

void GameEngineCore::InitializeLevel(GameEngineLevel* _level, const std::string& _levelName)
{
	//GameEngineCameraActor* mainCameraActor = _level->CreateActor<GameEngineCameraActor>();
	//mainCameraActor->GetCameraComponent()->SetProjectionMode(CameraProjectionMode::Orthographic);
	//mainCameraActor->GetTransform().SetLocalPosition(0, 0, -100);
	//
	//GameEngineCameraActor* UICameraActor = _level->CreateActor<GameEngineCameraActor>();
	//UICameraActor->GetCameraComponent()->SetProjectionMode(CameraProjectionMode::Orthographic);
	//UICameraActor->GetTransform().SetLocalPosition(0, 0, -100);


	_level->Start();
	_level->SetName(_levelName);

	std::pair<std::map<std::string, GameEngineLevel*>::iterator, bool> insertResult = 
		allLevels_.insert(std::make_pair(_levelName, _level));
	//make_pair()가 std::pair를 한개 만드는 시간 때문에 value_type()보다 약간 느리지만,
	//애초에 시작할때 한번만 실행할 코드이며, 맵으로 보관한다는 것 자체가 많이 반복하지 않는다는 의미이므로 큰 차이가 나지 않는다.
	//그러므로 더 짧고 가독성 좋은 make_pair로 뉴레벨을 저장한다.

	if (false == insertResult.second)
	{
		MsgBoxAssertString(_levelName + ": 같은 이름의 레벨이 이미 존재합니다.");
		return;
	}
}
