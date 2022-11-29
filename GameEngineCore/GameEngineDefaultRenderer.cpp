#include "PreCompile.h"
#include "GameEngineDefaultRenderer.h"
#include "GameEngineMaterial.h"
#include "GameEngineCamera.h"

GameEngineDefaultRenderer::GameEngineDefaultRenderer()
	: renderUnit_(std::make_shared<GameEngineRenderUnit>())
{
}

GameEngineDefaultRenderer::~GameEngineDefaultRenderer()
{
}

void GameEngineDefaultRenderer::Render(float _deltaTime)
{
	this->renderUnit_->Render(_deltaTime);
}

void GameEngineDefaultRenderer::SetMaterial(const std::string_view& _materialName)
{
	this->renderUnit_->SetMaterial(_materialName);
	this->renderUnit_->SetRenderer(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));
}

void GameEngineDefaultRenderer::SetMesh(const std::string_view& _meshName)
{
	this->renderUnit_->SetMesh(_meshName);
}

void GameEngineDefaultRenderer::Start()
{
	GameEngineRenderer::Start();	//���� ����� ����� ������ ���� ������ ���ؼ� �θ� Ŭ������ �Լ��� �ѹ� ȣ��.
}

void GameEngineDefaultRenderer::Update(float _deltaTime)
{
}

void GameEngineDefaultRenderer::End()
{
}