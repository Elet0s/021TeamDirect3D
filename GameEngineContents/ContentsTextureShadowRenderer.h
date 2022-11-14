#pragma once

class ContentsTextureShadowRenderer: public GameEngineDefaultRenderer
{
	//이 클래스의 존재 이유: 텍스처렌더러의 텍스처 받아서 그림자 렌더링.
public:
	ContentsTextureShadowRenderer();
	~ContentsTextureShadowRenderer();

protected:
	ContentsTextureShadowRenderer(const ContentsTextureShadowRenderer& _other) = delete;
	ContentsTextureShadowRenderer(ContentsTextureShadowRenderer&& _other) noexcept = delete;

private:
	ContentsTextureShadowRenderer& operator=(const ContentsTextureShadowRenderer& _other) = delete;
	ContentsTextureShadowRenderer& operator=(const ContentsTextureShadowRenderer&& _other) = delete;


public:	
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	//void SetTextureRenderer(std::shared_ptr<GameEngineTextureRenderer> _textureRenderer);

private:
	const float4 shadowColor_;

};

