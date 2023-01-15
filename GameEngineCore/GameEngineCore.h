#pragma once

class GEngine;
class GameEngineLevel;
class GameEngineCore
{
	friend GEngine;
	friend class GameEngineStatusWindow;

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
		int* i = new int(11);	//릭 체크가 이루어지고 있는지를 확인하기 위한 의도적인 릭.
#endif							//릴리즈모드에서는 하지 않는다.

		CoreType core{};
		Initiate(core.GetWindowTitle(), &core);
	}

	static GameEngineLevel* GetCurrentLevel()
	{
		return currentLevel_;
	}

protected:
	//컨텐츠 제작자용 함수들.
	virtual void Start() = 0;
	virtual void Update(float _deltaTime) = 0;
	virtual void End() = 0;

	static bool ChangeLevel(const std::string& _levelName);

protected:
	//프로세스 시작.
	static void StartCore(GameEngineCore* _userCore);	

	//프로세스 갱신.
	static void UpdateCore(GameEngineCore* _userCore);	

	//프로세스 종료.
	static void EndCore(GameEngineCore* _userCore);		

	//프로세스 개시 함수. 종료까지 담당.
	static void Initiate(const std::string& _title, GameEngineCore* _userCore);	

	//엔진 기본제공 리소스 초기화 함수.
	static void InitializeEngineResource();
	//사각형, 육면체, 에러텍스쳐, 렌더링 파이프라인, 각종 셰이더 등, 
	// 엔진 수준에서 기본적으로 지원되어야 하는 리소스를 준비하는 함수.

	//엔진 기본제공 리소스 정리 함수.
	static void DestroyEngineResource();

	//헤더 추가하기 싫어서 초기화를 CPP에서 하려고 만든 함수.
	static void InitializeLevel(GameEngineLevel* _level, const std::string& _levelName);


protected:	//컨텐츠코어만 사용해야 하는 함수들.
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

public:
	static GameEngineThreadPool engineThreadPool_;	//엔진 차원에서 제공하는 스레드풀.


private:
	static std::map<std::string, class GameEngineLevel*> allLevels_;
	static GameEngineLevel* currentLevel_;
	static GameEngineLevel* nextLevel_;


};

