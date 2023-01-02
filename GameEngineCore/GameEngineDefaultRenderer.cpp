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
	//��� ����Ʈ ���������� �⺻������ �ּ� �Ѱ��� ������ ���������� ������ �Ѵ�.
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
		//�׸��� �������� ���⼭ �������� �ʴ´�.
	}

	if (true == renderUnit_->GetMaterial()->GetPixelShader()->IsDeferredRendering())
	{
		return;
		//DeferredRenderingOutput�� ���� �ȼ����̴��� ���� ���׸����� ���� �������� �ɷ�����.
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
		//��ü ���׸����� ���� ���� ��Ʈ�������� ���⼭ ������Ű�� �ʴ´�.
	}

	if (true == isShadowRendering_)
	{
		return;
		//�׸��� �������� ���⼭ �������� �ʴ´�.
	}

	if (false == renderUnit_->GetMaterial()->GetPixelShader()->IsDeferredRendering())
	{
		return;
		//DeferredRenderingOutput�� ���� �ȼ����̴��� ���� ���׸����� ���� �������� �����Ų��.
	}

	renderUnit_->Render(_deltaTime);
}

void GameEngineDefaultRenderer::RenderShadow(float _deltaTime)
{
	if (nullptr != std::dynamic_pointer_cast<GameEngineFontRenderer>(shared_from_this()))
	{
		return;
		//��ü ���׸����� ���� ���� ��Ʈ�������� ���⼭ ������Ű�� �ʴ´�.
	}

	if (false == isShadowRendering_)
	{
		return;
		//�׸��� �������� ���⼭ �����Ѵ�.
	}

	if (true == renderUnit_->GetMaterial()->GetPixelShader()->IsDeferredRendering())
	{
		return;
		//DeferredRenderingOutput�� ���� �ȼ����̴��� ���� ���׸����� ���� �������� �ɷ�����.
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
	GameEngineRenderer::Start();	//���� ����� ����� ������ Ȥ�� ���� �θ� Ŭ������ �Լ��� �ѹ� ȣ��.
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
