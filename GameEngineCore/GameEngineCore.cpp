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
		MsgBoxAssertString(_levelName + ": �׷� �̸��� ������ �������� �ʽ��ϴ�.");
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
	//������ �ڵ� ����.

	GameEngineWindow::GetInst()->SetWindowScaleAndPosition(
		_userCore->StartWindowPosition(), _userCore->StartWindowSize());
	//������ ���� ��ġ�� ũ�� ����.

	GameEngineWindow::GetInst()->ShowGameWindow();
	//������ ����.
	
	GameEngineDevice::Initialize();
	//���̷�Ʈx ����̽�, DC, ����ü�� ����.

	GameEngineWindow::GetInst()->MessageLoop(
		std::bind(&GameEngineCore::CoreStart, _userCore),
		std::bind(&GameEngineCore::CoreUpdate, _userCore),
		std::bind(&GameEngineCore::CoreEnd, _userCore)
	);
	//���� ����.

}

void GameEngineCore::CoreStart(GameEngineCore* _userCore)
{
	EngineResourceInitialize();
	//�����ھ� �ʱ�ȭ �� ���� ���� ���ҽ� �غ�.
	//�����ھ��� ��ŸƮ ������ ���� ���ҽ� �غ� �����־�� �Ѵ�.

	GameEngineDevice::CreateSwapChain();
	//����ü�� ����.

	GameEngineDebug::Debug3DInitialize();

	GameEngineGUI::Initialize();
	//ImGUI �ʱ�ȭ.

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
			currentLevel_->OverChildMove(nextLevel_);	//���ϴ� ������Ʈ�� ���� ������ �ѱ��. 
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
		MsgBoxAssert("currentLevel_�� ������ϴ�.");
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
	//�ؽ�ó ���� ���ҽ��� �� ���� ������ ���ҽ����� ���� �ı��Ѵ�.

	GameEngineDebug::Debug3DDestroy();
	//�����Ҵ����� ������ �������ֵ��� �ı��Ѵ�.

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
	//make_pair()�� std::pair�� �Ѱ� ����� �ð� ������ value_type()���� �ణ ��������,
	//���ʿ� �����Ҷ� �ѹ��� ������ �ڵ��̸�, ������ �����Ѵٴ� �� ��ü�� ���� �ݺ����� �ʴ´ٴ� �ǹ��̹Ƿ� ū ���̰� ���� �ʴ´�.
	//�׷��Ƿ� �� ª�� ������ ���� make_pair�� �������� �����Ѵ�.

	if (false == insertResult.second)
	{
		MsgBoxAssertString(_levelName + ": ���� �̸��� ������ �̹� �����մϴ�.");
		return;
	}
}
