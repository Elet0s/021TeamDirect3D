#pragma once
#include "GameEngineRes.h"
#include "GameEngineShaderResourceHelper.h"
#include "GameEngineRenderer.h"

class GameEnginePostEffect
{
	bool isUpdate_ = true;

public:
	virtual ~GameEnginePostEffect() {};
	virtual void EffectInit() = 0;
	virtual void Effect(class GameEngineRenderTarget* _renderTarget) = 0;

public:
	inline bool IsUpdate()
	{
		return isUpdate_;
	}

	virtual void On()
	{
		isUpdate_ = true;
	}

	virtual void Off()
	{
		isUpdate_ = false;
	}
};

class GameEngineTexture;
class GameEngineRenderTarget: public GameEngineRes<GameEngineRenderTarget>
{
	//����Ÿ�ٺ�� ���̽��ٽǺ並 �����ϴ� Ŭ����.
	//����Ÿ��: ������ ������������ ���� ��ģ ������μ��� ���� 2���� �迭�� �޴µ� ���Ǵ� �׷��� ī�� �� �޸� ����.
	//GameEngineTexture Ŭ���� ���·� ����� �ؽ��ĵ�� ������ �ؽ��ĵ鿡 ������ ����Ÿ�ٺ���� �� Ŭ������ �����Ѵ�. 

	friend GameEngineRes<GameEngineRenderTarget>;
	//GameEngineRenderTargetŬ������ �����̺� �Ҹ��ڸ� GameEngineResŬ�������� ȣ���ϱ� ���� ���.

	friend class GameEngineStatusWindow;
	//������ ����??

	friend class GameEngineBlur;


	//���ӿ�������Ÿ�ٰ� ���ӿ����ؽ��� Ŭ������ �и��� ����: 
	//���ӿ����ؽ��Ĵ� �ڱⰡ ���� �ؽ��Ŀ� �� ���긮�ҽ��鸸 ������ �����ϴ� Ŭ�����̰�,
	//���ӿ�������Ÿ���� �� �����ӿ�ũ�� ��� ����Ÿ�ٺ並 �����ϴ� Ŭ�����̴�. 

private:
	GameEngineRenderTarget();
	~GameEngineRenderTarget();
	//�ܺο��� ���ڴ�� ���ҽ��� ����/�����ϴ°� ���� ���ؼ� ������/�Ҹ��ڸ� �����̺����� �����ؼ� �ܺ� ������ ���´�.
	//�� �����ӿ�ũ�� ���ҽ��� �ݵ�� �Ҹ��ڰ� �ƴ϶� ResourceDestroy()�Լ����� �����ؾ� �Ѵ�.
	//���α׷� ���������� ���ҽ������� ���ϸ� ������ �������� �׷��� �ִ��� ���Ƶд�.

	GameEngineRenderTarget(const GameEngineRenderTarget& _other) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&& _other) noexcept = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _other) = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget&& _other) = delete;
	
public:

	static GameEngineRenderTarget* Create(const std::string_view& _name);
	static GameEngineRenderTarget* Create();

	void CreateRenderTargetTexture(	//����Ÿ������ �� ���ӿ����ؽ�ó ��ü�� ����, �����ϴ� �Լ�.
		ID3D11Texture2D* _texture,
		const float4& _clearColor);
	void CreateRenderTargetTexture(
		const float4& _size,
		const float4& _color);
	void CreateRenderTargetTexture(
		const float4& _size,
		DXGI_FORMAT _format,
		const float4& _color);
	void CreateRenderTargetTexture(
		D3D11_TEXTURE2D_DESC _desc,
		const float4& _color	);
	void CreateRenderTargetTexture(
		GameEngineTexture* _texture,
		const float4& _color);
	GameEngineTexture* GetRenderTargetTexture(size_t _index);

	void CreateDepthTexture(int _index);
	void SetDepthTexture(GameEngineTexture* _depthTexture);

	//�� ����Ÿ���� ���� ����Ÿ�ٺ�� ���̽��ٽǺ並 �� ���� ������ ���� ��� �ʱ�ȭ�ϴ� �Լ�.
	void Clear();

	//�� ����Ÿ�ٺ並 ����̽� ���ؽ�Ʈ�� ������ ������ ������������ ��ģ ������� ���� �� �ְ� �ϴ� �Լ�.
	void Setting();

	//�� ����Ÿ�ٿ� �ִ� ���� ������ ������ �����ϰ�, �ٸ� ����Ÿ���� ������ ������ �����ͼ� ������ �Լ�.
	void Copy(GameEngineRenderTarget* _otherRenderTarget, int _index = 0);

	//�־��� ����Ÿ���� ���� ������ ������ �� ����Ÿ���� ���� ���� ������������ ���� ������ �����ϴ� �Լ�. 
	void Merge(GameEngineRenderTarget* _otherRenderTarget, int _index = 0);

	//�� ����Ÿ�ٿ�, �־��� ���������� ���� ������ ������ ���� ����� �Լ�. 
	void Effect(GameEngineRenderUnit& _renderUnit);

	//�� ����Ÿ���� ���� ��� ��ó��ȿ���� ����Ÿ���� ���� ������������ �����Ű�� �Լ�.
	void EffectProcess();

public:
	GameEngineTexture* GetDepthTexture()
	{
		return depthTexture_;
	}

	template<typename EffectType>
	EffectType* AddEffect()
	{
		GameEnginePostEffect* newEffect = new EffectType();
		newEffect->EffectInit();
		allEffects_.push_back(newEffect);
		return reinterpret_cast<EffectType*>(newEffect);
	}


private:
	//����Ÿ������ ����� �ؽ��ĵ�.
	std::vector<GameEngineTexture*> renderTargets_;

	//�� �ؽ��Ŀ��� �Ļ��� ����Ÿ�ٺ��.
	std::vector<ID3D11RenderTargetView*> renderTargetViews_;

	//�� �ؽ��Ŀ��� �Ļ��� ���̴����ҽ����.
	std::vector<ID3D11ShaderResourceView*> shaderResourceViews_;

	//����Ÿ�ٺ並 �ʱ�ȭ�Ҷ� �� ���󰪵�.
	std::vector<float4> clearColors_;
	//���Ϳ� �־��ٰ� �ݵ�� ������ ����Ѵٴ� ������ ����.

	GameEngineTexture* depthTexture_;	//���̽��ٽǺ並 ���� �ؽ�ó.

	ID3D11DepthStencilView* depthStencilView_;	//�� �ؽ�ó�� ���� ���̽��ٽǺ�.

	GameEngineRenderUnit mergeUnit_;	//Copy(), Merge()���� �Լ� ���࿡ �ʿ��� ��������.

	std::list<GameEnginePostEffect*> allEffects_;	//�� ����Ÿ���� ���� ��� ��ó��ȿ����.
	//���⿡ ����Ǵ� 

};

