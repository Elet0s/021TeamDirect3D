#include "PreCompile.h"
#include "GameEngineDefaultRenderer.h"
#include "GameEngineMaterial.h"
#include "GameEngineCamera.h"
#include "GameEnginePixelShader.h"
#include "GameEngineFontRenderer.h"

GameEngineDefaultRenderer::GameEngineDefaultRenderer(): isShadowRendering_(false)
{
}

GameEngineDefaultRenderer::~GameEngineDefaultRenderer()
{
}

void GameEngineDefaultRenderer::Render(float _deltaTime)
{
	if (true == isShadowRendering_)
	{
		return;
		//�׸��� �������� ���⼭ �������� �ʴ´�.
	}

	if (true == renderUnit_.GetMaterial()->GetPixelShader()->IsDeferredRendering())
	{
		return;
		//DeferredRenderingOutput�� ���� �ȼ����̴��� ���� ���׸����� ���� �������� �ɷ�����.
	}

	renderUnit_.Render(_deltaTime);
}

void GameEngineDefaultRenderer::DeferredRender(float _deltaTime)
{
	if (nullptr != dynamic_cast<GameEngineFontRenderer*>(this))
	{
		return;
		//��ü ���׸����� ���� ���� ��Ʈ�������� ���⼭ ������Ű�� �ʴ´�.
	}

	if (true == isShadowRendering_)
	{
		return;
		//�׸��� �������� ���⼭ �������� �ʴ´�.
	}

	if (false == renderUnit_.GetMaterial()->GetPixelShader()->IsDeferredRendering())
	{
		return;
		//DeferredRenderingOutput�� ���� �ȼ����̴��� ���� ���׸����� ���� �������� �����Ų��.
	}

	renderUnit_.Render(_deltaTime);
}

void GameEngineDefaultRenderer::RenderShadow(float _deltaTime)
{
	if (nullptr != dynamic_cast<GameEngineFontRenderer*>(this))
	{
		return;
		//��ü ���׸����� ���� ���� ��Ʈ�������� ���⼭ ������Ű�� �ʴ´�.
	}

	if (false == isShadowRendering_)
	{
		return;
		//�׸��� �������� ���⼭ �����Ѵ�.
	}

	if (true == renderUnit_.GetMaterial()->GetPixelShader()->IsDeferredRendering())
	{
		return;
		//DeferredRenderingOutput�� ���� �ȼ����̴��� ���� ���׸����� ���� �������� �ɷ�����.
	}

	renderUnit_.Render(_deltaTime);
}

void GameEngineDefaultRenderer::SetMaterial(const std::string_view& _materialName)
{
	this->renderUnit_.SetMaterial(_materialName);
	this->renderUnit_.SetRenderer(this);
}

void GameEngineDefaultRenderer::SetMesh(const std::string_view& _meshName)
{
	this->renderUnit_.SetMesh(_meshName);
}

void GameEngineDefaultRenderer::Start()
{
	GameEngineRenderer::Start();	//���� ����� ����� ������ Ȥ�� ���� �θ� Ŭ������ �Լ��� �ѹ� ȣ��.
}

void GameEngineDefaultRenderer::Update(float _deltaTime)
{
}

void GameEngineDefaultRenderer::End()
{
}
