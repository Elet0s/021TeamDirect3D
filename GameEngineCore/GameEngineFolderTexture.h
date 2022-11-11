#pragma once
#include "GameEngineRes.h"

class GameEngineTexture;
class GameEngineFolderTexture : public GameEngineRes<GameEngineFolderTexture>
{
	//

public:
	GameEngineFolderTexture();
	~GameEngineFolderTexture();
private:


	GameEngineFolderTexture(const GameEngineFolderTexture& _other) = delete;
	GameEngineFolderTexture(GameEngineFolderTexture&& _other) noexcept = delete;
	GameEngineFolderTexture& operator=(const GameEngineFolderTexture& _other) = delete;
	GameEngineFolderTexture& operator=(const GameEngineFolderTexture&& _other) = delete;


public:
	static std::shared_ptr<GameEngineFolderTexture> Load(const std::string_view& _path);
	static std::shared_ptr<GameEngineFolderTexture> Load(const std::string_view& _path, const std::string_view& _name);

public:
	size_t GetTextureCount()
	{
		return textures_.size();
	}

	std::shared_ptr<GameEngineTexture> GetTexture(size_t _index)
	{
		if (textures_.size() <= _index || 0 > _index)
		{
			MsgBoxAssert("폴더 텍스쳐 참조 범위를 넘겼습니다.");
			return nullptr;
		}

		return textures_[_index];
	}

private:
	void LoadFolder(const std::string_view& _path);

private:
	std::vector<std::shared_ptr<GameEngineTexture>> textures_;

};

