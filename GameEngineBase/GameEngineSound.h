#pragma once
#include "GameEngineNameObject.h"
#include "GameEngineFile.h"
#include <GameEngineBase\ThirdParty\FMOD\Include\fmod.hpp>

class GameEngineSoundPlayer;
class GameEngineSound : public GameEngineNameObject
{

public:

	GameEngineSound();
	~GameEngineSound();

	GameEngineSound(const GameEngineSound& _other) = delete;
	GameEngineSound(GameEngineSound&& _other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _other) = delete;

public:
	static GameEngineSoundPlayer SoundPlayControl(const std::string& _name, unsigned int _loopCount = 0);
	static void SoundPlayOneshot(const std::string& _name, int _loopCount = 0);
	static void Update();

	//파일이 사운드보다 더 근본에 가까우므로 게임엔진사운드에서 게임엔진 파일도 받을 수 있게 구성한다.
	static GameEngineSound* LoadResource(const GameEngineFile& _path);
	static GameEngineSound* LoadResource(const std::string& _path);
	static GameEngineSound* LoadResource(const std::string& _path, const std::string& _name);
	static GameEngineSound* FindResources(const std::string& _name);

	static void ResourceDestroy();

protected:
	bool Load(const std::string& _path);

private:
	FMOD::Sound* sound_;

	static std::map<std::string, GameEngineSound*> allResources_;

};


class GameEngineSound;
class GameEngineSoundPlayer
{
	friend GameEngineSound;

	GameEngineSound* sound_;
	FMOD::Channel* controlHandle_;


	GameEngineSoundPlayer(GameEngineSound* _sound, FMOD::Channel* _controlHandle);

public:
	GameEngineSoundPlayer();
	GameEngineSoundPlayer(const GameEngineSoundPlayer& _other);
	~GameEngineSoundPlayer();


public:
	void Stop();
	void PlaySpeed(float _speed);
	void Volume(float _value);

};
