#pragma once
#include<GameEngineBase/GameEngineSound.h>

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

	void Stop() // �÷��̾� ����
	{
		BGMPlayer_.Stop();
	}

	void VolumeSet(float _Volume) // �÷��̾� ���� ����
	{
		BGMPlayer_.Volume(_Volume);
	}
	void SpeedSet(float _Speed) //�÷��̾� ����ӵ� ����
	{
		BGMPlayer_.PlaySpeed(_Speed);
	}
	void ChangeBgm(std::string _BgmName, float _volume = 1.0f) // ������� ����
	{
		if (false == BGMPlayer_.IsEmpty())
		{
			BGMPlayer_.Stop();
		}

		BGMPlayer_ = GameEngineSound::SoundPlayControl(_BgmName);
	}

	void Destory() // �����Ҷ� ȣ�����ٰ�
	{
		if (BGMPlay_ != nullptr)
		{
			delete BGMPlay_;
		}
	}
};