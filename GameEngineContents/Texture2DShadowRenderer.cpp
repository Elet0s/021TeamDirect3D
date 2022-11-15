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
//		MsgBoxAssert("텍스처렌더러가 없습니다.");
//		return;
//	}
//
//	this->GetTransform().SetWorldPosition(_textureRenderer->GetTransform().GetWorldPosition());
//	GetRenderUnit().GetShaderResourceHelper().SetTexture("Tex",_textureRenderer->GetCurrentTexture());
//
//
//}

// 리인터프리터캐스트의 단점: 주소값을 단순 정수로 바꾸는 형변환이므로 널포인터여도 널포인터로 감지되지 않는다.
// 플레이어를 할당해서 몬스터로 사용해도 에러를 내지 않다가 나중에 문제를 일으킨다.
// 컴파일 타임 어설션: 어떤 값이 컴파일할때 결정나는 것.
//연산자: 런타임 이전에 컴파일러가 처리해버리는 함수.
