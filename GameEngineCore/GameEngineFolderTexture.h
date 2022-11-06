#pragma once
#include "GameEngineRes.h"

class GameEngineTexture;
class GameEngineFolderTexture: public GameEngineRes<GameEngineFolderTexture>
{
	//

	friend GameEngineRes<GameEngineFolderTexture>;
	//GameEngineFolderTexture 클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.

private:
	GameEngineFolderTexture();
	~GameEngineFolderTexture();
	//외부에서 제멋대로 리소스를 생성/삭제하는걸 막기 위해서 생성자/소멸자를 프라이빗으로 지정해서 외부 접근을 막는다.
	//이 프레임워크의 리소스는 반드시 소멸자가 아니라 ResourceDestroy()함수에서 제거해야 한다.
	//프로그램 끝날때까지 리소스삭제를 안하면 끝나는 문제지만 그래도 최대한 막아둔다.

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
			MsgBoxAssert("폴더 텍스쳐 참조 범위를 넘겼습니다.");
			return nullptr;
		}

		return textures_[_index];
	}

private:
	void LoadFolder(const std::string_view& _path);

private:
	std::vector<GameEngineTexture*> textures_;

};

