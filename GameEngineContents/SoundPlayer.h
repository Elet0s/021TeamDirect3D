#pragma once

class SoundPlayer
{
public:
	static SoundPlayer* BGMPlay_;

	SoundPlayer();
	~SoundPlayer();

	SoundPlayer(const SoundPlayer& _Other) = delete;
	SoundPlayer(SoundPlayer&& _Other) noexcept = delete;
	SoundPlayer& operator=(const SoundPlayer& _Other) = delete;
	SoundPlayer& operator=(SoundPlayer&& _Other) noexcept = delete;

	GameEngineSoundPlayer BGMPlayer_;

public:

	void Stop() // 플레이어 멈춤
	{
		BGMPlayer_.Stop();
	}

	void VolumeSet(float _Volume) // 플레이어 볼륨 세팅
	{
		BGMPlayer_.Volume(_Volume);
	}
	void SpeedSet(float _Speed) //플레이어 재생속도 세팅
	{
		BGMPlayer_.PlaySpeed(_Speed);
	}
	void ChangeBgm(std::string _BgmName, float _volume = 1.0f) // 재생음악 변경
	{
		if (false == BGMPlayer_.IsControlHandleEmpty())
		{
			BGMPlayer_.Stop();
		}

		BGMPlayer_ = GameEngineSound::SoundPlayControl(_BgmName);
	}

	void Destroy() // 종료할때 호출해줄것
	{
		if (BGMPlay_ != nullptr)
		{
			delete BGMPlay_;
		}
	}
};