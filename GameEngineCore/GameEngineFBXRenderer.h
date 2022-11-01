#pragma once
#include "GameEngineRenderer.h"

class GameEngineFBXRenderer: public GameEngineRenderer 
{
	//이 클래스의 존재 이유:
public:
	GameEngineFBXRenderer();
	~GameEngineFBXRenderer();

protected:
	GameEngineFBXRenderer(const GameEngineFBXRenderer& _other) = delete;
	GameEngineFBXRenderer(GameEngineFBXRenderer&& _other) noexcept = delete;

private:
	GameEngineFBXRenderer& operator=(const GameEngineFBXRenderer& _other) = delete;
	GameEngineFBXRenderer& operator=(const GameEngineFBXRenderer&& _other) = delete;


public:	
	void SetFBXMesh(const std::string& _fbxMeshName, const std::string& _materialName);
	void SetFBXMesh(
		const std::string& _fbxMeshName, const std::string& _materialName,
		size_t _meshIndex,
		size_t _subsetIndex = 0
	);

	void Render(float _deltaTime) override;

	std::vector<std::vector<GameEngineRenderUnit>>& GetAllRenderUnit()
	{
		return Unit;
	}

	void CreateAnimation(
		const std::string& _AnimationName,
		const std::string& _MeshFBX,
		const std::string& _AnimationFBX
	);

private:
	class GameEngineFBXMesh* FBXMesh;

	std::vector<std::vector<GameEngineRenderUnit>> Unit;
};

