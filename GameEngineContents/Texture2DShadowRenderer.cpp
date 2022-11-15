#include "PreCompile.h"
#include "Texture2DShadowRenderer.h"

Texture2DShadowRenderer::Texture2DShadowRenderer()
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

	GetShaderResourceHelper().SetTexture("Tex", "tree_Group_A.png");
	GetShaderResourceHelper().SetSampler("POINTCLAMP", "POINTCLAMP");

}

void Texture2DShadowRenderer::Update(float _deltaTime)
{
}

void Texture2DShadowRenderer::End()
{
}

//void ContentsTextureShadowRenderer::SetTextureRenderer(std::shared_ptr<GameEngineTextureRenderer> _textureRenderer)
//{
//	if (nullptr == _textureRenderer)
//	{
//		MsgBoxAssert("�ؽ�ó�������� �����ϴ�.");
//		return;
//	}
//
//	this->GetTransform().SetWorldPosition(_textureRenderer->GetTransform().GetWorldPosition());
//	GetRenderUnit().GetShaderResourceHelper().SetTexture("Tex",_textureRenderer->GetCurrentTexture());
//
//
//}

// ������������ĳ��Ʈ�� ����: �ּҰ��� �ܼ� ������ �ٲٴ� ����ȯ�̹Ƿ� �������Ϳ��� �������ͷ� �������� �ʴ´�.
// �÷��̾ �Ҵ��ؼ� ���ͷ� ����ص� ������ ���� �ʴٰ� ���߿� ������ ����Ų��.
// ������ Ÿ�� ���: � ���� �������Ҷ� �������� ��.
//������: ��Ÿ�� ������ �����Ϸ��� ó���ع����� �Լ�.
