#pragma once

class Texture2DShadowRenderer: public GameEngineDefaultRenderer
{
	//이 클래스의 존재 이유: 텍스처렌더러의 현재 텍스처 받아서 그림자 렌더링.
	//텍스처렌더러가 이미 있는데 그림자렌더러를 따로 만든 이유:
	//어차피 그림자 그리는 텍스처렌더러를 어떤 식으로든 추가로 생성해야 하는데 그럴거면 
	// 최대한 가벼운 렌더러를 만들고 싶어서.


	//추가할 것.
	// 1. 조명 위치에 따른 그림자 각도변화.
	// 2. 그림자 경계선에 블러.

public:
	Texture2DShadowRenderer();
	~Texture2DShadowRenderer();

protected:
	Texture2DShadowRenderer(const Texture2DShadowRenderer& _other) = delete;
	Texture2DShadowRenderer(Texture2DShadowRenderer&& _other) noexcept = delete;

private:
	Texture2DShadowRenderer& operator=(const Texture2DShadowRenderer& _other) = delete;
	Texture2DShadowRenderer& operator=(const Texture2DShadowRenderer&& _other) = delete;


public:	
	void SetTextureRenderer(GameEngineTextureRenderer* _textureRenderer);
	void SetShadowAngle(float _angle = 30.f);

private:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;


private:
	bool isAnimation_;
	GameEngineTextureRenderer* parentTextureRenderer_;

};

