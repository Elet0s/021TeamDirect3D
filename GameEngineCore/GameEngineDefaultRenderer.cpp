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
		//그림자 렌더러는 여기서 렌더하지 않는다.
	}

	if (true == renderUnit_.GetMaterial()->GetPixelShader()->IsDeferredRendering())
	{
		return;
		//DeferredRenderingOutput을 가진 픽셀셰이더를 가진 마테리얼을 가진 렌더러는 걸러낸다.
	}

	renderUnit_.Render(_deltaTime);
}

void GameEngineDefaultRenderer::DeferredRender(float _deltaTime)
{
	if (nullptr != dynamic_cast<GameEngineFontRenderer*>(this))
	{
		return;
		//자체 마테리얼을 따로 가진 폰트렌더러는 여기서 렌더시키지 않는다.
	}

	if (true == isShadowRendering_)
	{
		return;
		//그림자 렌더러는 여기서 렌더하지 않는다.
	}

	if (false == renderUnit_.GetMaterial()->GetPixelShader()->IsDeferredRendering())
	{
		return;
		//DeferredRenderingOutput을 가진 픽셀셰이더를 가진 마테리얼을 가진 렌더러만 통과시킨다.
	}

	renderUnit_.Render(_deltaTime);
}

void GameEngineDefaultRenderer::RenderShadow(float _deltaTime)
{
	if (nullptr != dynamic_cast<GameEngineFontRenderer*>(this))
	{
		return;
		//자체 마테리얼을 따로 가진 폰트렌더러는 여기서 렌더시키지 않는다.
	}

	if (false == isShadowRendering_)
	{
		return;
		//그림자 렌더러만 여기서 렌더한다.
	}

	if (true == renderUnit_.GetMaterial()->GetPixelShader()->IsDeferredRendering())
	{
		return;
		//DeferredRenderingOutput을 가진 픽셀셰이더를 가진 마테리얼을 가진 렌더러는 걸러낸다.
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
	GameEngineRenderer::Start();	//딱히 대단한 기능은 없지만 혹시 몰라서 부모 클래스의 함수를 한번 호출.
}

void GameEngineDefaultRenderer::Update(float _deltaTime)
{
}

void GameEngineDefaultRenderer::End()
{
}
