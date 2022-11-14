#pragma once
#include "GameEngineRenderer.h"

class GameEngineFBXRenderer : public GameEngineRenderer
{
	//이 클래스의 존재 이유:
public:
	GameEngineFBXRenderer();
	virtual ~GameEngineFBXRenderer() = 0;

protected:
	GameEngineFBXRenderer(const GameEngineFBXRenderer& _other) = delete;
	GameEngineFBXRenderer(GameEngineFBXRenderer&& _other) noexcept = delete;

private:
	GameEngineFBXRenderer& operator=(const GameEngineFBXRenderer& _other) = delete;
	GameEngineFBXRenderer& operator=(const GameEngineFBXRenderer&& _other) = delete;


public:
	virtual void SetFBXMesh(const std::string& _fbxMeshName, const std::string& _materialName);
	virtual void SetFBXMesh(const std::string& _fbxMeshName, const std::string& _materialName, size_t _meshIndex);
	virtual GameEngineRenderUnit* SetFBXMesh(
		const std::string& _fbxMeshName,
		const std::string& _materialName,
		size_t _meshIndex,
		size_t _subsetIndex
	);	// SetFbxMesh를 해서 만들어진 랜더 유니트를 사용하게 하기 위해서 리턴해준다.

	void Render(float _deltaTime) override;

public:
	std::vector<std::vector<GameEngineRenderUnit>>& GetAllRenderUnit()
	{
		return Unit;
	}

	inline std::shared_ptr<class GameEngineFBXMesh> GetFBXMesh()
	{
		return FBXMesh;
	}

private:
	std::shared_ptr<class GameEngineFBXMesh> FBXMesh;

	std::vector<std::vector<GameEngineRenderUnit>> Unit;
};

