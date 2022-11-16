#pragma once

class Texture2DShadowRenderer: public GameEngineDefaultRenderer
{
	//�� Ŭ������ ���� ����: �ؽ�ó�������� ���� �ؽ�ó �޾Ƽ� �׸��� ������.
	//�ؽ�ó�������� �̹� �ִµ� �׸��ڷ������� ���� ���� ����:
	// 1. ������ �׸��� �׸��� �ؽ�ó�������� � �����ε� �߰��� �����ؾ� �ϴµ� �׷��Ÿ� 
	// �ִ��� ������ �������� ����� �;.
	// 
	// 2. 
	// 
	// 3. ������ ���� �ľ��Ϸ���.


	//�߰��� ��.
	// 1. �ִϸ��̼� �׸��� ������.
	// 2. ���� ��ġ�� ���� �׸��� ������ȭ.
	// 3. �׸��� ��輱�� ��.

	//���Ͱ� ��� �ִµ� �ؽ�ó�������� �ı��ϴ� ��� ��� �ȵ�.

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
	void SetTextureRenderer(std::shared_ptr<GameEngineTextureRenderer> _textureRenderer);

private:
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;


private:
	bool isAnimation_;
	std::weak_ptr<GameEngineTextureRenderer> parentTextureRenderer_;

};

