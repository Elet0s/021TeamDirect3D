#pragma once
#include "GameEngineRes.h"

class GameEngineTexture;
class GameEngineFolderTexture: public GameEngineRes<GameEngineFolderTexture>
{
	//

	friend GameEngineRes<GameEngineFolderTexture>;
	//GameEngineFolderTexture Ŭ������ �����̺� �Ҹ��ڸ� GameEngineResŬ�������� ȣ���ϱ� ���� ���.

private:
	GameEngineFolderTexture();
	~GameEngineFolderTexture();
	//�ܺο��� ���ڴ�� ���ҽ��� ����/�����ϴ°� ���� ���ؼ� ������/�Ҹ��ڸ� �����̺����� �����ؼ� �ܺ� ������ ���´�.
	//�� �����ӿ�ũ�� ���ҽ��� �ݵ�� �Ҹ��ڰ� �ƴ϶� ResourceDestroy()�Լ����� �����ؾ� �Ѵ�.
	//���α׷� ���������� ���ҽ������� ���ϸ� ������ �������� �׷��� �ִ��� ���Ƶд�.

	GameEngineFolderTexture(const GameEngineFolderTexture& _other) = delete;
	GameEngineFolderTexture(GameEngineFolderTexture&& _other) noexcept = delete;
	GameEngineFolderTexture& operator=(const GameEngineFolderTexture& _other) = delete;
	GameEngineFolderTexture& operator=(const GameEngineFolderTexture&& _other) = delete;


public:	
	static GameEngineFolderTexture* Load(const std::string_view& _path);
	static GameEngineFolderTexture* Load(const std::string_view& _path, const std::string_view& _name);

public:
	size_t GetTextureCount()
	{
		return textures_.size();
	} 

	GameEngineTexture* GetTexture(size_t _index)
	{
		if (textures_.size() <= _index || 0 > _index)
		{
			MsgBoxAssert("���� �ؽ��� ���� ������ �Ѱ���ϴ�.");
			return nullptr;
		}

		return textures_[_index];
	}

private:
	void LoadFolder(const std::string_view& _path);

private:
	std::vector<GameEngineTexture*> textures_;

};

