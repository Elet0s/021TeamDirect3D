#include "PreCompile.h"
#include "GameEngineDefaultRenderer.h"
#include "GameEngineMaterial.h"
#include "GameEngineCamera.h"

GameEngineDefaultRenderer::GameEngineDefaultRenderer()
{
}

GameEngineDefaultRenderer::~GameEngineDefaultRenderer()
{
}

void GameEngineDefaultRenderer::Render(float _deltaTime)
{
	this->renderUnit_.Render(_deltaTime);
}

void GameEngineDefaultRenderer::SetPipeLine(const std::string& _renderingPipeLineName)
{
	this->renderUnit_.SetPipeLine(_renderingPipeLineName);
	this->renderUnit_.SetRenderer(this);
}

void GameEngineDefaultRenderer::SetMesh(const std::string& _meshName)
{
	this->renderUnit_.SetMesh(_meshName);
}

void GameEngineDefaultRenderer::InstancingOn()
{
	GameEngineRenderer::InstancingOn();
}

void GameEngineDefaultRenderer::Start()
{
	GameEngineRenderer::Start();
}

void GameEngineDefaultRenderer::Update(float _deltaTime)
{
}

void GameEngineDefaultRenderer::End()
{
}