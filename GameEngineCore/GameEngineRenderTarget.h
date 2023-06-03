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
	//렌더타겟뷰와 깊이스텐실뷰를 관리하는 클래스.
	//렌더타겟: 렌더링 파이프라인을 전부 거친 결과물로서의 색상값 2차원 배열을 받는데 사용되는 그래픽 카드 내 메모리 영역.
	//GameEngineTexture 클래스 형태로 저장된 텍스쳐들과 각각의 텍스쳐들에 연동된 렌더타겟뷰들을 이 클래스로 통제한다. 

	friend GameEngineRes<GameEngineRenderTarget>;
	//GameEngineRenderTarget클래스의 프라이빗 소멸자를 GameEngineRes클래스에서 호출하기 위한 방법.

	friend class GameEngineStatusWindow;
	//프렌드 이유??

	friend class GameEngineBlur;
	//프렌드 이유??


	//게임엔진렌더타겟과 게임엔진텍스처 클래스를 분리한 이유: 
	//게임엔진텍스쳐는 자기가 가진 텍스처와 그 서브리소스들만 가지고 관리하는 클래스이고,
	//게임엔진렌더타겟은 이 프레임워크내 모든 렌더타겟뷰를 관리하는 클래스이다. 

private:
	GameEngineRenderTarget();
	~GameEngineRenderTarget();
	//외부에서 제멋대로 리소스를 생성/삭제하는걸 막기 위해서 생성자/소멸자를 프라이빗으로 지정해서 외부 접근을 막는다.
	//이 프레임워크의 리소스는 반드시 소멸자가 아니라 ResourceDestroy()함수에서 제거해야 한다.
	//프로그램 끝날때까지 리소스삭제를 안하면 끝나는 문제지만 그래도 최대한 막아둔다.

	GameEngineRenderTarget(const GameEngineRenderTarget& _other) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&& _other) noexcept = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _other) = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget&& _other) = delete;

public:

	static GameEngineRenderTarget* Create(const std::string_view& _name);
	static GameEngineRenderTarget* Create();

	//렌더타겟으로 쓸 게임엔진텍스처 객체를 생성, 저장하는 함수.
	void CreateRenderTargetTexture(	
		ID3D11Texture2D* _texture,
		const float4& _clearColor
	);

	//렌더타겟으로 쓸 게임엔진텍스처 객체를 생성, 저장하는 함수.
	void CreateRenderTargetTexture(
		const float4& _size,
		const float4& _clearColor
	);

	//렌더타겟으로 쓸 게임엔진텍스처 객체를 생성, 저장하는 함수.
	void CreateRenderTargetTexture(
		const float4& _size,
		DXGI_FORMAT _format,
		const float4& _clearColor
	);

	//렌더타겟으로 쓸 게임엔진텍스처 객체를 생성, 저장하는 함수.
	void CreateRenderTargetTexture(
		D3D11_TEXTURE2D_DESC _desc,
		const float4& _clearColor
	);

	//렌더타겟으로 쓸 게임엔진텍스처 객체를 생성, 저장하는 함수.
	void CreateRenderTargetTexture(
		GameEngineTexture* _texture,
		const float4& _clearColor
	);

	GameEngineTexture* GetRenderTargetTexture(size_t _index);

	void CreateDepthTexture(int _renderTargetIndex);
	void SetDepthTexture(GameEngineTexture* _depthTexture);

	//이 렌더타겟이 가진 렌더타겟뷰와 깊이스텐실뷰를 한 가지 값으로 전부 덮어서 초기화하는 함수.
	void Clear(bool _clearDepthStencilView = true);

	//이 렌더타겟뷰를 디바이스 컨텍스트에 세팅해 렌더링 파이프라인을 거친 결과물을 받을 수 있게 하는 함수.
	void SetRenderTarget();

	//이 렌더타겟뷰를 디바이스 컨텍스트에서 빼는 함수.
	void ResetRenderTarget();

	//이 렌더타겟에 있던 기존 렌더링 정보를 무시하고, 다른 렌더타겟의 렌더링 정보를 가져와서 덮어씌우는 함수.
	void Copy(GameEngineRenderTarget* _otherRenderTarget, int _index = 0);

	//주어진 렌더타겟이 가진 렌더링 정보를 이 렌더타겟이 가진 기존 렌더링정보에 덮어 씌워서 통합하는 함수. 
	void Merge(GameEngineRenderTarget* _otherRenderTarget, int _index = 0);

	//이 렌더타겟에, 주어진 렌더유닛이 가진 렌더링 정보를 덮어 씌우는 함수. 
	void Effect(GameEngineRenderUnit& _renderUnit);

	//이 렌더타겟이 가진 모든 후처리효과를 렌더타겟의 기존 렌더링정보에 적용시키는 함수.
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
		return std::dynamic_pointer_cast<EffectType>(newEffect);
	}


private:
	//렌더타겟으로 사용할 텍스쳐들.
	std::vector<GameEngineTexture*> renderTargetTextures_;

	//위 텍스쳐에서 파생된 렌더타겟뷰들.
	std::vector<ID3D11RenderTargetView*> renderTargetViews_;

	//위 텍스쳐에서 파생된 셰이더리소스뷰들.
	std::vector<ID3D11ShaderResourceView*> shaderResourceViews_;

	//렌더타겟뷰를 초기화할때 쓸 색상값들.
	std::vector<float4> clearColors_;
	//벡터에 넣었다고 반드시 여러개 사용한다는 보장은 없음.

	GameEngineTexture* depthTexture_;	//깊이스텐실뷰를 만들 텍스처.

	ID3D11DepthStencilView* depthStencilView_;	//위 텍스처로 만든 깊이스텐실뷰.

	GameEngineRenderUnit mergeUnit_;	//Copy(), Merge()등의 함수 실행에 필요한 렌더유닛.
	//값형인 이유??

	std::list<GameEnginePostEffect*> allEffects_;	//이 렌더타겟이 가진 모든 후처리효과들.

};

