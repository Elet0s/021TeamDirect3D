#pragma once
#include "GameEngineRenderer.h"

class GameEngineFBXRenderer: public GameEngineRenderer 
{
	//�� Ŭ������ ���� ����:
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
	virtual void SetFBXMesh(
		const std::string& _fbxMeshName, const std::string& _materialName,
		size_t _meshIndex,
		size_t _subsetIndex = 0
	);

	void Render(float _deltaTime) override;

	std::vector<std::vector<GameEngineRenderUnit>>& GetAllRenderUnit()
	{
		return Unit;
	}

	inline class GameEngineFBXMesh* GetFBXMesh()
	{
		return FBXMesh;
	}

private:
	class GameEngineFBXMesh* FBXMesh;

	std::vector<std::vector<GameEngineRenderUnit>> Unit;
};

