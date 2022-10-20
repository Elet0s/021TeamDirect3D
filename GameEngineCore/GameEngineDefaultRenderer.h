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

	//렌더러들은 반드시 렌더링 파이프라인이 포함된 렌더유닛을 들고 있다. 렌더링 파이프라인은 다이렉트X와 직접적으로 연결되어 있다.
	//하나의 렌더링 파이프라인은 하나의 메쉬, 하나의 메테리얼, 하나의 렌더타겟을 가진다.


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

	//렌더러에 필요한 렌더링 파이프라인을 등록하고 이 렌더러를 메인 카메라에 등록하는 함수.
	void SetPipeLine(const std::string& _renderingPipeLineName);

	void SetMesh(const std::string& _meshName);


	virtual void InstancingOn();


public:
	inline GameEngineShaderResourceHelper& GetShaderResourceHelper()	
		//셰이더리소스헬퍼 없는 렌더러란 있을 수 없으므로 레퍼런스 반환.
	{
		return this->renderUnit_.GetShaderResourceHelper();
	}


	inline GameEngineRenderUnit& GetRenderUnit()	
		//렌더유닛 없는 렌더러란 있을 수 없으므로 레퍼런스 반환.
	{
		return this->renderUnit_;
	}

protected:
	virtual void Start();
	virtual void Update(float _deltaTime);
	virtual void End();


	

private:
	GameEngineRenderUnit renderUnit_;
	//한개의 디폴트렌더러마다 최소 한개의 렌더유닛을 가진다.
};

