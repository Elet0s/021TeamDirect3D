#pragma once

class Texture2DShadowRenderer: public GameEngineDefaultRenderer
{
	//�� Ŭ������ ���� ����: �ؽ�ó�������� ���� �ؽ�ó �޾Ƽ� �׸��� ������.
	//�ؽ�ó�������� �̹� �ִµ� �׸��ڷ������� ���� ���� ����:
	//������ �׸��� �׸��� �ؽ�ó�������� � �����ε� �߰��� �����ؾ� �ϴµ� �׷��Ÿ� 
	// �ִ��� ������ �������� ����� �;.


	//�߰��� ��.
	// 1. ���� ��ġ�� ���� �׸��� ������ȭ.
	// 2. �׸��� ��輱�� ��.

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

