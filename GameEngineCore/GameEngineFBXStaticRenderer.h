#pragma once
#include "GameEngineFBXRenderer.h"

class GameEngineFBXStaticRenderer : public GameEngineFBXRenderer
{
	//이 클래스의 존재 이유:
public:
	GameEngineFBXStaticRenderer();
	~GameEngineFBXStaticRenderer();

protected:
	GameEngineFBXStaticRenderer(const GameEngineFBXStaticRenderer& _other) = delete;
	GameEngineFBXStaticRenderer(GameEngineFBXStaticRenderer&& _other) noexcept = delete;

private:
	GameEngineFBXStaticRenderer& operator=(const GameEngineFBXStaticRenderer& _other) = delete;
	GameEngineFBXStaticRenderer& operator=(const GameEngineFBXStaticRenderer&& _other) = delete;


public:
	virtual void SetFBXMesh(const std::string& _fbxMeshName, const std::string& _materialName) override;
	virtual void SetFBXMesh(
		const std::string& _fbxMeshName,
		const std::string& _materialName,
		size_t _meshIndex,
		size_t _subsetIndex = 0
	) override;


private:
	void Render(float _deltaTime) override;

};

