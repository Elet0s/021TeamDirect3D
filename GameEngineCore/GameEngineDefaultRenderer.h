#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineShaderResourceHelper.h"

class GameEngineRenderUnit;
class GameEngineDefaultRenderer: public GameEngineRenderer
{
	//이 프레임워크에서 렌더링에 필요한 최소한의 구성 요소인 렌더링 파이프라인과 셰이더리소스헬퍼를 가지고 
	// 자기가 가진 정보를 게임엔진카메라의 렌더링 체계에서 뷰변환, 투영변환, 뷰포트변환을 거쳐 변형된 대로
	// 렌더링 파이프라인을 통해 윈도우 범위 내의 픽셀별 색상값으로 바꿔 렌더타겟에 전달하는 컴포넌트.
	//실질적인 렌더링을 수행하는 컴포넌트이다.

	
public:
	GameEngineDefaultRenderer();
	~GameEngineDefaultRenderer();

protected:
	GameEngineDefaultRenderer(const GameEngineDefaultRenderer& _other) = delete;
	GameEngineDefaultRenderer(GameEngineDefaultRenderer&& _other) noexcept = delete;

private:
	GameEngineDefaultRenderer& operator=(const GameEngineDefaultRenderer& _other) = delete;
	GameEngineDefaultRenderer& operator=(const GameEngineDefaultRenderer&& _other) = delete;


public:	
	virtual void Render(float _deltaTime) override;
	virtual void DeferredRender(float _deltaTime) override;

	//렌더러에 필요한 마테리얼을 등록하고 이 렌더러를 메인 카메라에 등록하는 함수.
	void SetMaterial(const std::string_view& _materialName);

	//
	void SetMesh(const std::string_view& _meshName);


public:
	inline GameEngineShaderResourceHelper& GetShaderResourceHelper()	
		//셰이더리소스헬퍼 없는 렌더러란 있을 수 없으므로 레퍼런스 반환.
	{
		return this->renderUnit_->GetShaderResourceHelper();
		//return this->allRenderUnits_[RenderingPath::ForwardRendering][0]->GetShaderResourceHelper();
	}

	//inline std::vector<std::shared_ptr<GameEngineRenderUnit>> GetForwardRenderUnitVector()
	//{
	//	return this->allRenderUnits_[RenderingPath::ForwardRendering];
	//}

	//inline std::vector<std::shared_ptr<GameEngineRenderUnit>> GetDeferredRenderUnitVector()
	//{
	//	return this->allRenderUnits_[RenderingPath::DeferredRendering];
	//}

protected:
	virtual void Start();
	virtual void Update(float _deltaTime);
	virtual void End();


	//std::shared_ptr<GameEngineRenderUnit> AddRenderUnit();
	//std::shared_ptr<GameEngineRenderUnit> AddDeferredRenderUnit();

private:
	std::shared_ptr<GameEngineRenderUnit> renderUnit_;
	//한개의 디폴트렌더러마다 최소 한개의 렌더유닛을 가진다.

	//이 렌더러가 가진 모든 렌더유닛들.
	//std::map<RenderingPath, std::vector<std::shared_ptr<GameEngineRenderUnit>>> allRenderUnits_;
	//렌더링패스 순서대로 정렬.
	//맵과 벡터라고 만드시 많은 숫자를 저장한다는 보장은 없음.

	//마테리얼이나 셰이더리소스헬퍼는 렌더유닛당 한개씩이 아니라 렌더러당 한개씩 가져도 되지 않을까.
	//만약 이게 맞다면 렌더유닛이 아니라 렌더러가 마테리얼과 셰이더리소스헬퍼를 가지게 하자.

};

