#pragma once
#include "GameEngineRes.h"
#include "GameEngineShaderResourceHelper.h"
#include "GameEngineRenderer.h"

class GameEnginePostEffect : public std::enable_shared_from_this<GameEnginePostEffect>
{
	bool isUpdate_ = true;

public:
	virtual ~GameEnginePostEffect() {};
	virtual void EffectInit() = 0;
	virtual void Effect(std::shared_ptr<class GameEngineRenderTarget> _renderTarget) = 0;

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
class GameEngineRenderTarget
	: public GameEngineRes<GameEngineRenderTarget>,
	public std::enable_shared_from_this<GameEngineRenderTarget>
{
	//����Ÿ�ٺ�� ���̽��ٽǺ並 �����ϴ� Ŭ����.
	//����Ÿ��: ������ ������������ ���� ��ģ ������μ��� ���� 2���� �迭�� �޴µ� ���Ǵ� �׷��� ī�� �� �޸� ����.
	//GameEngineTexture Ŭ���� ���·� ����� �ؽ��ĵ�� ������ �ؽ��ĵ鿡 ������ ����Ÿ�ٺ���� �� Ŭ������ �����Ѵ�. 

	friend class GameEngineStatusWindow;
	//������ ����??

	friend class GameEngineBlur;


	//���ӿ�������Ÿ�ٰ� ���ӿ����ؽ��� Ŭ������ �и��� ����: 
	//���ӿ����ؽ��Ĵ� �ڱⰡ ���� �ؽ��Ŀ� �� ���긮�ҽ��鸸 ������ �����ϴ� Ŭ�����̰�,
	//���ӿ�������Ÿ���� �� �����ӿ�ũ�� ��� ����Ÿ�ٺ並 �����ϴ� Ŭ�����̴�. 

public:
	GameEngineRenderTarget();
	~GameEngineRenderTarget();

private:
	GameEngineRenderTarget(const GameEngineRenderTarget& _other) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&& _other) noexcept = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _other) = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget&& _other) = delete;

public:

	static std::shared_ptr<GameEngineRenderTarget> Create(const std::string_view& _name);
	static std::shared_ptr<GameEngineRenderTarget> Create();

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
		const float4& _color);
	void CreateRenderTargetTexture(
		std::shared_ptr<GameEngineTexture> _texture,
		const float4& _color);
	std::shared_ptr<GameEngineTexture> GetRenderTargetTexture(size_t _index);

	void CreateDepthTexture(int _renderTargetIndex);
	void SetDepthTexture(std::shared_ptr<GameEngineTexture> _depthTexture);

	//�� ����Ÿ���� ���� ����Ÿ�ٺ�� ���̽��ٽǺ並 �� ���� ������ ���� ��� �ʱ�ȭ�ϴ� �Լ�.
	void Clear(bool _clearDepthStencilView = true);

	//�� ����Ÿ�ٺ並 ����̽� ���ؽ�Ʈ�� ������ ������ ������������ ��ģ ������� ���� �� �ְ� �ϴ� �Լ�.
	void Setting();

	//�� ����Ÿ�ٺ並 ����̽� ���ؽ�Ʈ���� ���� �Լ�.
	void Reset();

	//�� ����Ÿ�ٿ� �ִ� ���� ������ ������ �����ϰ�, �ٸ� ����Ÿ���� ������ ������ �����ͼ� ������ �Լ�.
	void Copy(std::shared_ptr<GameEngineRenderTarget> _otherRenderTarget, int _index = 0);

	//�־��� ����Ÿ���� ���� ������ ������ �� ����Ÿ���� ���� ���� ������������ ���� ������ �����ϴ� �Լ�. 
	void Merge(std::shared_ptr<GameEngineRenderTarget> _otherRenderTarget, int _index = 0);

	//�� ����Ÿ�ٿ�, �־��� ���������� ���� ������ ������ ���� ����� �Լ�. 
	void Effect(std::shared_ptr<GameEngineRenderUnit> _renderUnit);

	//�� ����Ÿ���� ���� ��� ��ó��ȿ���� ����Ÿ���� ���� ������������ �����Ű�� �Լ�.
	void EffectProcess();

public:
	std::shared_ptr<GameEngineTexture> GetDepthTexture()
	{
		return depthTexture_;
	}

	template<typename EffectType>
	std::shared_ptr<EffectType> AddEffect()
	{
		std::shared_ptr<GameEnginePostEffect> newEffect = std::make_shared<EffectType>();
		newEffect->EffectInit();
		allEffects_.push_back(newEffect);
		return std::dynamic_pointer_cast<EffectType>(newEffect);
	}


private:
	//����Ÿ������ ����� �ؽ��ĵ�.
	std::vector<std::shared_ptr<GameEngineTexture>> renderTargets_;

	//�� �ؽ��Ŀ��� �Ļ��� ����Ÿ�ٺ��.
	std::vector<ID3D11RenderTargetView*> renderTargetViews_;

	//�� �ؽ��Ŀ��� �Ļ��� ���̴����ҽ����.
	std::vector<ID3D11ShaderResourceView*> shaderResourceViews_;

	//����Ÿ�ٺ並 �ʱ�ȭ�Ҷ� �� ���󰪵�.
	std::vector<float4> clearColors_;
	//���Ϳ� �־��ٰ� �ݵ�� ������ ����Ѵٴ� ������ ����.

	std::shared_ptr<GameEngineTexture> depthTexture_;	//���̽��ٽǺ並 ���� �ؽ�ó.

	ID3D11DepthStencilView* depthStencilView_;	//�� �ؽ�ó�� ���� ���̽��ٽǺ�.

	std::shared_ptr<GameEngineRenderUnit> mergeUnit_;	//Copy(), Merge()���� �Լ� ���࿡ �ʿ��� ��������.

	std::list<std::shared_ptr<GameEnginePostEffect>> allEffects_;	//�� ����Ÿ���� ���� ��� ��ó��ȿ����.

};

