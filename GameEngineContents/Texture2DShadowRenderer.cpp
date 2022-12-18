#include "PreCompile.h"
#include "Texture2DShadowRenderer.h"

Texture2DShadowRenderer::Texture2DShadowRenderer(): isAnimation_(false)
{
}

Texture2DShadowRenderer::~Texture2DShadowRenderer()
{
}

void Texture2DShadowRenderer::Start()
{
	GameEngineRenderer::Start();
	SetMesh("Rect");
	SetMaterial("Texture2DShadow");
	GetFirstShaderResourceHelper().SetSampler("LINEARWRAP", "LINEARWRAP");
}

void Texture2DShadowRenderer::Update(float _deltaTime)
{
	if (true == isAnimation_)
		//�θ� �ؽ�ó�������� �ִϸ��̼��϶��� ������Ʈ�� �Ѵ�.
	{
		GetFirstShaderResourceHelper().SetConstantBuffer_Link(
			"AtlasData", parentTextureRenderer_.lock()->GetAtlasData());
		GetFirstShaderResourceHelper().SetTexture(
			"Tex", parentTextureRenderer_.lock()->GetCurrentTexture());

		if (0.f >= parentTextureRenderer_.lock()->GetTransform().GetWorldScale().x)
			//�θ� �ؽ�ó�������� �¿�����Ǹ� vertexInversion_�� -1�� �־ ���ؽ����̴��� �����Ѵ�.
		{
			renderOptionInst_.vertexInversion_ = -1;
		}
		else
		{
			renderOptionInst_.vertexInversion_ = 1;
		}

		if (1.f != renderOptionInst_.vertexInversion_ && -1.f != renderOptionInst_.vertexInversion_)
		{
			MsgBoxAssert("VertexInversion�� 1�� -1�� ���˴ϴ�.");
			return;
		}
	}
}

void Texture2DShadowRenderer::End()
{
}

void Texture2DShadowRenderer::SetTextureRenderer(std::shared_ptr<GameEngineTextureRenderer> _textureRenderer)
{
	if (nullptr == _textureRenderer)
	{
		MsgBoxAssert("�ؽ�ó�������� �����ϴ�.");
		return;
	}

	this->SetParent(_textureRenderer);
	parentTextureRenderer_ = _textureRenderer;
	SetRenderingOrder(parentTextureRenderer_.lock()->GetRenderingOrder() + 2);

	GetFirstShaderResourceHelper().SetConstantBuffer_Link(
		"AtlasData", parentTextureRenderer_.lock()->GetAtlasData());
	GetFirstShaderResourceHelper().SetTexture(
		"Tex", parentTextureRenderer_.lock()->GetCurrentTexture());

	if (true == parentTextureRenderer_.lock()->IsCurAnimation())
	{
		isAnimation_ = true;
	}
}

void Texture2DShadowRenderer::SetShadowAngle(float _angle /*= 30.f*/)
{
	renderOptionInst_.shadowAngle_ = _angle;	//�׸��� �⺻�� 30��.
	GetFirstShaderResourceHelper().SetConstantBuffer_Link("RenderOption", renderOptionInst_);
}

//������������ĳ��Ʈ�� ����: �ּҰ��� �ܼ� ������ �ٲٴ� ����ȯ�̹Ƿ� �������Ϳ��� �������ͷ� �������� �ʴ´�.
//�÷��̾ �Ҵ��ؼ� ���ͷ� ����ص� ������ ���� �ʴٰ� ���߿� ������ ����Ų��.
//������ Ÿ�� ���: � ���� �������Ҷ� �������� ��.
//������: ��Ÿ�� ������ �����Ϸ��� ó���ع����� �Լ�.
