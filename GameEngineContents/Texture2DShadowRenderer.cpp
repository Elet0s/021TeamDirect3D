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
		//부모 텍스처렌더러가 애니메이션일때만 업데이트를 한다.
	{
		GetFirstShaderResourceHelper().SetConstantBuffer_Link(
			"AtlasData", parentTextureRenderer_.lock()->GetAtlasData());
		GetFirstShaderResourceHelper().SetTexture(
			"Tex", parentTextureRenderer_.lock()->GetCurrentTexture());

		if (0.f >= parentTextureRenderer_.lock()->GetTransform().GetWorldScale().x)
			//부모 텍스처렌더러가 좌우반전되면 vertexInversion_에 -1을 넣어서 버텍스셰이더로 전달한다.
		{
			renderOptionInst_.vertexInversion_ = -1;
		}
		else
		{
			renderOptionInst_.vertexInversion_ = 1;
		}

		if (1.f != renderOptionInst_.vertexInversion_ && -1.f != renderOptionInst_.vertexInversion_)
		{
			MsgBoxAssert("VertexInversion은 1과 -1만 허용됩니다.");
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
		MsgBoxAssert("텍스처렌더러가 없습니다.");
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
	renderOptionInst_.shadowAngle_ = _angle;	//그림자 기본값 30도.
	GetFirstShaderResourceHelper().SetConstantBuffer_Link("RenderOption", renderOptionInst_);
}

//리인터프리터캐스트의 단점: 주소값을 단순 정수로 바꾸는 형변환이므로 널포인터여도 널포인터로 감지되지 않는다.
//플레이어를 할당해서 몬스터로 사용해도 에러를 내지 않다가 나중에 문제를 일으킨다.
//컴파일 타임 어설션: 어떤 값이 컴파일할때 결정나는 것.
//연산자: 런타임 이전에 컴파일러가 처리해버리는 함수.
