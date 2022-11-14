#pragma once

class Texture2DShadowRenderer: public GameEngineDefaultRenderer
{
	//�� Ŭ������ ���� ����: �ؽ�ó�������� �ؽ�ó �޾Ƽ� �׸��� ������.
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
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;
	//void SetTextureRenderer(std::shared_ptr<GameEngineTextureRenderer> _textureRenderer);

private:
	//const float4 shadowColor_;

};

