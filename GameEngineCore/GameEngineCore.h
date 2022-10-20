#pragma once

class GEngine;
class GameEngineLevel;
class GameEngineCore
{
	friend GEngine;
	friend class GameEngineStatusWindow;

	static std::map<std::string, class GameEngineLevel*> allLevels_;
	static GameEngineLevel* currentLevel_;
	static GameEngineLevel* nextLevel_;

protected:
	GameEngineCore();
	~GameEngineCore();

private:
	GameEngineCore(const GameEngineCore& _other) = delete;
	GameEngineCore(GameEngineCore&& _other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _other) = delete;

public:
	template<typename CoreType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();

#ifdef _DEBUG
		int* i = new int(11);	//�� üũ�� �̷������ �ִ����� Ȯ���ϱ� ���� �ǵ����� ��.
#endif							//�������忡���� ���� �ʴ´�.

		CoreType core{};
		WindowCreate(core.GetWindowTitle(), &core);


	}

	static GameEngineLevel* GetCurrentLevel()
	{
		return currentLevel_;
	}

protected:
	//������ �����ڿ� �Լ���.
	virtual void Start() = 0;
	virtual void Update(float _deltaTime) = 0;
	virtual void End() = 0;

	static bool ChangeLevel(const std::string& _levelName);

protected:
	static void CoreStart(GameEngineCore* _userCore);	//���α׷� ����.
	static void CoreUpdate(GameEngineCore* _userCore);	//���α׷� ����.
	static void CoreEnd(GameEngineCore* _userCore);	//���α׷� ����.
	static void WindowCreate(const std::string& _title, GameEngineCore* _userCore);

	//���� �⺻���� ���ҽ� �ʱ�ȭ �Լ�.
	static void EngineResourceInitialize();
	//�簢��, ����ü, �����ؽ���, ������ ����������, ���� ���̴� ��, 
	// ���� ���ؿ��� �⺻������ �����Ǿ�� �ϴ� ���ҽ��� �غ��ϴ� �Լ�.

	//���� �⺻���� ���ҽ� ���� �Լ�.
	static void EngineResourceDestroy();

	//��� �߰��ϱ� �Ⱦ �ʱ�ȭ�� CPP���� �Ϸ��� ���� �Լ�.
	static void InitializeLevel(GameEngineLevel* _level, const std::string& _levelName);


protected:	//�������ھ ����ؾ� �ϴ� �Լ���.
	virtual std::string GetWindowTitle()
	{
		return "DefaultWindowTitle";
	}
	virtual float4 StartWindowSize()
	{
		return float4(1280, 720);
	}
	virtual float4 StartWindowPosition()
	{
		return float4(0, 0);
	}


	template <typename LevelType>
	static GameEngineLevel* CreateLevel(const std::string& _levelName)
	{
		std::string uppercaseLevelName = GameEngineString::ToUpperReturn(_levelName);

		GameEngineLevel* newLevel = new LevelType();
		InitializeLevel(newLevel, uppercaseLevelName);
		return newLevel;
	}

	static GameEngineLevel* FindLevel(const std::string& _levelName)
	{
		std::string uppercaseLevelName = GameEngineString::ToUpperReturn(_levelName);
		std::map<std::string, GameEngineLevel*>::iterator findIter = allLevels_.find(uppercaseLevelName);
		if (allLevels_.end() == findIter)
		{
			return nullptr;
		}
		else
		{
			return findIter->second;
		}
	}





};

