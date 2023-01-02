#include "PreCompile.h"
#include "GameEngineDefaultRenderer.h"
#include "GameEngineMaterial.h"
#include "GameEngineCamera.h"
#include "GameEnginePixelShader.h"
#include "GameEngineFontRenderer.h"

GameEngineDefaultRenderer::GameEngineDefaultRenderer()
	: renderUnit_(std::make_shared<GameEngineRenderUnit>()),
	isShadowRendering_(false)
{
	//allRenderUnits_[RenderingPath::ForwardRendering].push_back(std::make_shared<GameEngineRenderUnit>());
	//모든 디폴트 렌더러들은 기본적으로 최소 한개의 포워드 렌더유닛을 가지게 한다.
}

GameEngineDefaultRenderer::~GameEngineDefaultRenderer()
{
}

void GameEngineDefaultRenderer::Render(float _deltaTime)
{
	//for (std::shared_ptr<GameEngineRenderUnit>& singleRenderUnit : allRenderUnits_[RenderingPath::ForwardRendering])
	//{
	//	singleRenderUnit->Render(_deltaTime);
	//}

	if (true == isShadowRendering_)
	{
		return;
		//그림자 렌더러는 여기서 렌더하지 않는다.
	}

	if (true == renderUnit_->GetMaterial()->GetPixelShader()->IsDeferredRendering())
	{
		return;
		//DeferredRenderingOutput을 가진 픽셀셰이더를 가진 마테리얼을 가진 렌더러는 걸러낸다.
	}

	renderUnit_->Render(_deltaTime);
}

void GameEngineDefaultRenderer::DeferredRender(float _deltaTime)
{
	//for (std::shared_ptr<GameEngineRenderUnit>& singleRenderUnit : allRenderUnits_[RenderingPath::DeferredRendering])
	//{
	//	singleRenderUnit->Render(_deltaTime);
	//}

	if (nullptr != std::dynamic_pointer_cast<GameEngineFontRenderer>(shared_from_this()))
	{
		return;
		//자체 마테리얼을 따로 가진 폰트렌더러는 여기서 렌더시키지 않는다.
	}

	if (true == isShadowRendering_)
	{
		return;
		//그림자 렌더러는 여기서 렌더하지 않는다.
	}

	if (false == renderUnit_->GetMaterial()->GetPixelShader()->IsDeferredRendering())
	{
		return;
		//DeferredRenderingOutput을 가진 픽셀셰이더를 가진 마테리얼을 가진 렌더러만 통과시킨다.
	}

	renderUnit_->Render(_deltaTime);
}

void GameEngineDefaultRenderer::RenderShadow(float _deltaTime)
{
	if (nullptr != std::dynamic_pointer_cast<GameEngineFontRenderer>(shared_from_this()))
	{
		return;
		//자체 마테리얼을 따로 가진 폰트렌더러는 여기서 렌더시키지 않는다.
	}

	if (false == isShadowRendering_)
	{
		return;
		//그림자 렌더러만 여기서 렌더한다.
	}

	if (true == renderUnit_->GetMaterial()->GetPixelShader()->IsDeferredRendering())
	{
		return;
		//DeferredRenderingOutput을 가진 픽셀셰이더를 가진 마테리얼을 가진 렌더러는 걸러낸다.
	}

	renderUnit_->Render(_deltaTime);
}

void GameEngineDefaultRenderer::SetMaterial(const std::string_view& _materialName)
{
	this->renderUnit_->SetMaterial(_materialName);
	this->renderUnit_->SetRenderer(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));
	//this->renderUnit_->PushCamera();

	//for (size_t i = 0; i < allRenderUnits_[RenderingPath::ForwardRendering].size(); ++i)
	//{
	//	allRenderUnits_[RenderingPath::ForwardRendering][i]->SetMaterial(_materialName);
	//	allRenderUnits_[RenderingPath::ForwardRendering][i]->SetRenderer(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));
	//}

	//for (size_t i = 0; i < allRenderUnits_[RenderingPath::DeferredRendering].size(); ++i)
	//{
	//	allRenderUnits_[RenderingPath::DeferredRendering][i]->SetMaterial(_materialName);
	//	allRenderUnits_[RenderingPath::DeferredRendering][i]->SetRenderer(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));
	//}
}

void GameEngineDefaultRenderer::SetMesh(const std::string_view& _meshName)
{
	this->renderUnit_->SetMesh(_meshName);

	//for (size_t i = 0; i < allRenderUnits_[RenderingPath::ForwardRendering].size(); ++i)
	//{
	//	allRenderUnits_[RenderingPath::ForwardRendering][i]->SetMesh(_meshName);
	//}
	//
	//for (size_t i = 0; i < allRenderUnits_[RenderingPath::DeferredRendering].size(); ++i)
	//{
	//	allRenderUnits_[RenderingPath::DeferredRendering][i]->SetMesh(_meshName);
	//}
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

//std::shared_ptr<GameEngineRenderUnit> GameEngineDefaultRenderer::AddRenderUnit()
//{
//	std::shared_ptr<GameEngineRenderUnit> newRenderUnit = std::make_shared<GameEngineRenderUnit>();
//	newRenderUnit->SetRenderer(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));
//	allRenderUnits_[RenderingPath::ForwardRendering].push_back(newRenderUnit);
//	return newRenderUnit;
//}

//std::shared_ptr<GameEngineRenderUnit> GameEngineDefaultRenderer::AddDeferredRenderUnit()
//{
//	std::shared_ptr<GameEngineRenderUnit> newRenderUnit = std::make_shared<GameEngineRenderUnit>();
//	newRenderUnit->SetRenderer(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));
//	allRenderUnits_[RenderingPath::DeferredRendering].push_back(newRenderUnit);
//	return newRenderUnit;
//}
