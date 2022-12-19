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
	//렌더타겟뷰와 깊이스텐실뷰를 관리하는 클래스.
	//렌더타겟: 렌더링 파이프라인을 전부 거친 결과물로서의 색상값 2차원 배열을 받는데 사용되는 그래픽 카드 내 메모리 영역.
	//GameEngineTexture 클래스 형태로 저장된 텍스쳐들과 각각의 텍스쳐들에 연동된 렌더타겟뷰들을 이 클래스로 통제한다. 

	friend class GameEngineStatusWindow;
	//프렌드 이유??

	friend class GameEngineBlur;


	//게임엔진렌더타겟과 게임엔진텍스쳐 클래스를 분리한 이유: 
	//게임엔진텍스쳐는 자기가 가진 텍스쳐와 그 서브리소스들만 가지고 관리하는 클래스이고,
	//게임엔진렌더타겟은 이 프레임워크내 모든 렌더타겟뷰를 관리하는 클래스이다. 

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

	void CreateRenderTargetTexture(	//렌더타겟으로 쓸 게임엔진텍스처 객체를 생성, 저장하는 함수.
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

	//이 렌더타겟이 가진 렌더타겟뷰와 깊이스텐실뷰를 한 가지 값으로 전부 덮어서 초기화하는 함수.
	void Clear(bool _clearDepthStencilView = true);

	//이 렌더타겟뷰를 디바이스 컨텍스트에 세팅해 렌더링 파이프라인을 거친 결과물을 받을 수 있게 하는 함수.
	void Setting();

	//이 렌더타겟뷰를 디바이스 컨텍스트에서 빼는 함수.
	void Reset();

	//이 렌더타겟에 있던 기존 렌더링 정보를 무시하고, 다른 렌더타겟의 렌더링 정보를 가져와서 덮어씌우는 함수.
	void Copy(std::shared_ptr<GameEngineRenderTarget> _otherRenderTarget, int _index = 0);

	//주어진 렌더타겟이 가진 렌더링 정보를 이 렌더타겟이 가진 기존 렌더링정보에 덮어 씌워서 통합하는 함수. 
	void Merge(std::shared_ptr<GameEngineRenderTarget> _otherRenderTarget, int _index = 0);

	//이 렌더타겟에, 주어진 렌더유닛이 가진 렌더링 정보를 덮어 씌우는 함수. 
	void Effect(std::shared_ptr<GameEngineRenderUnit> _renderUnit);

	//이 렌더타겟이 가진 모든 후처리효과를 렌더타겟의 기존 렌더링정보에 적용시키는 함수.
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
	//렌더타겟으로 사용할 텍스쳐들.
	std::vector<std::shared_ptr<GameEngineTexture>> renderTargets_;

	//위 텍스쳐에서 파생된 렌더타겟뷰들.
	std::vector<ID3D11RenderTargetView*> renderTargetViews_;

	//위 텍스쳐에서 파생된 셰이더리소스뷰들.
	std::vector<ID3D11ShaderResourceView*> shaderResourceViews_;

	//렌더타겟뷰를 초기화할때 쓸 색상값들.
	std::vector<float4> clearColors_;
	//벡터에 넣었다고 반드시 여러개 사용한다는 보장은 없음.

	std::shared_ptr<GameEngineTexture> depthTexture_;	//깊이스텐실뷰를 만들 텍스처.

	ID3D11DepthStencilView* depthStencilView_;	//위 텍스처로 만든 깊이스텐실뷰.

	std::shared_ptr<GameEngineRenderUnit> mergeUnit_;	//Copy(), Merge()등의 함수 실행에 필요한 렌더유닛.

	std::list<std::shared_ptr<GameEnginePostEffect>> allEffects_;	//이 렌더타겟이 가진 모든 후처리효과들.

};

