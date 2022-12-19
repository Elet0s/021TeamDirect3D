#pragma once
#include "GameEngineLevel.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineLighting.h"

enum class RenderingPath
{
	ForwardRendering,	//일반 렌더링.
	DeferredRendering,	//지연 렌더링.
	None
};

enum class CameraProjectionMode
{
	Perspective, //원근투영.
	Orthographic //직교투영.
};

class GameEngineInstancingRenderer;
class GameEngineInstancing;
class GameEngineMaterial;
class GameEngineCamera : public GameEngineTransformComponent
{
	//카메라. 
	//월드공간의 오브젝트들이 뷰 스페이스라고 하는 가상의 카메라 시야범위 안에 들어 왔을때, 
	// 오브젝트들을 구성하는 정점들을 뷰행렬에 맞춰서 재배치하고 투영행렬에 맞춰서 축소한 후
	// 뷰포트행렬대로 다시 확대한 만큼의 정점 좌표를 계산해서 변형된 대로 그리는 컴포넌트.

	friend GameEngineLevel;
	friend class GameEngineRenderer;

public:

	GameEngineCamera();
	~GameEngineCamera();

	GameEngineCamera(const GameEngineCamera& _other) = delete;
	GameEngineCamera(GameEngineCamera&& _other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _other) = delete;

public:
	//마우스 포인터의 위치를 윈도우 스크린 좌표로 받아오는 함수.
	float4 GetMouseScreenPosition();

	//마우스 포인터의 위치를 월드좌표(고정 카메라 기준)로 받아오는 함수.
	float4 GetMouseWorldPosition();

	//마우스 포인터의 위치를 월드좌표(이동 카메라 기준)로 받아오는 함수.
	float4 GetMouseWorldPositionToActor();

	//주어진 월드좌표를 윈도우좌표로 바꾸는 함수.
	float4 GetWorldPositionToScreenPosition(const float4& _worldPosition);

	//카메라의 순서를 변경하는 함수.
	void SetCameraOrder(CameraOrder _order);
	//할 일이 있을지는 모르겠지만, 카메라 오더 런타임에 변경 금지.

	//인스턴싱 반환. 없다면 빈 인스턴싱을 만들어서 반환한다.
	GameEngineInstancing& GetInstancing(const std::string& _name);

	//인스턴싱렌더러 반환. 없다면 빈 인스턴싱렌더러를 만들어서 반환한다.
	std::shared_ptr<GameEngineInstancingRenderer> GetInstancingRenderer(const std::string& _name);

	//카메라에 조명 추가.
	void PushLighting(std::shared_ptr<GameEngineLighting> _newLighting);

public:
	void SetProjectionMode(CameraProjectionMode _mode)
	{
		projectionMode_ = _mode;
	}
	inline const float4& GetMouseWorldDirection()
	{
		return mouseDirection_;
	}
	CameraProjectionMode GetProjectionMode()
	{
		return projectionMode_;
	}

	inline void SetProjectionSize(const float4& _size)
	{
		size_ = _size;
	}
	inline const float4& GetProjectionSize() const
	{
		return size_;
	}

	inline const float4x4& GetViewMatrix()
	{
		return viewMatrix_;
	}

	inline const float4x4& GetProjectionMatrix() const
	{
		return projectionMatrix_;
	}

	//이 카메라의 최종 렌더타겟을 가져오는 함수.
	inline std::shared_ptr<class GameEngineRenderTarget> GetConclusionRenderTarget()
	{
		return conclusionRenderTarget_;
	}

	//이 카메라의 포워드렌더링용 렌더타겟을 가져오는 함수.
	inline std::shared_ptr<class GameEngineRenderTarget> GetForwardRenderTarget()
	{
		return forwardRenderTarget_;
	}

	inline LightingDatas& GetLightingDatas()
	{
		return lightingDatasInst_;
	}


protected:
	void Start();

private:
	//이 카메라가 가진 렌더러들에게 이 카메라가 가진 렌더타겟에 렌더링 정보를 적용시키게 하는 함수.
	void Render(float _deltaTime);

	//주어진 렌더러를 이 카메라에 등록하는 함수.
	void PushRenderer(std::shared_ptr<GameEngineRenderer> _renderer);

	//렌더러를 등록 해제하는 함수. 직접 삭제하는 함수가 아님에 주의할 것.
	void Release(float _deltaTime);

	void Update(float _dletaTime) override;

	//이 카메라의 렌더러들을 다른 레벨의 카메라로 옮기는 함수.
	void OverRenderer(std::shared_ptr<GameEngineCamera> _nextCamera);

	//렌더링 순서 변경.
	void ChangeRenderingOrder(std::shared_ptr<GameEngineRenderer> _renderer, int _newRenderingOrder);

private:
	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>> allRenderers_;	//이 카메라가 가진 모든 렌더러들.
	//렌더링오더로 먼저 분류한 후 렌더 직전에 zsort() 함수로 z값 순서대로 정렬한다. 

	std::unordered_map<std::string, GameEngineInstancing> instancingMap_;	//
	//비정렬 맵으로 한 이유: 순회할 일이 거의 없을거라고 생각한 상황에서 비정렬 맵을 그냥 써보고 싶어서.

	std::map<std::string, std::shared_ptr<GameEngineInstancingRenderer>> instancingRenderers_;

	//비정렬 맵(Unordered Map): 들어오는 키값을 해시함수를 거쳐서 나온 숫자로 바꿔서, 
	// 그 값을 인덱스로 하는 배열 내 원소로 데이터를 저장하는 방식의 컨테이너. 
	//장점으로는 검색 속도가 '대체로' 다른 컨테이너들보다 빠르다고 한다(항상 그렇진 않음).
	//단점으로는 이름대로 키값 정렬이 되지 않고, 순회 효율이 떨어지며, 해시 충돌이 많이 발생할 수록 검색 효율이 떨어져서,
	// 최악의 경우 선형 시간복잡도를 보이게 된다고 한다.

	//해시 충돌: 다른 입력값을 해시 함수에 넣었는데 같은 결과값이 나와서 두 입력값을 구분할 수 없게 되는 현상.
	// 해시 충돌 확률이 낮을 수록 더 좋은 해시 함수라고 한다.


	float4x4 viewMatrix_;
	//뷰행렬: 월드공간의 원점 기준으로 배치된 여러 정점들을, 카메라 위치가 원점이 된 뷰공간 안에 어떻게 재배치해서, 
	// 월드공간에 배치되었던 그대로 화면 안에 보이게 할 지 계산하는데 필요한 행렬. 
	//월드 전체의 오브젝트를 재배치하는 특성상, 뷰행렬은 월드 전체에 적용된다.
	//카메라가 뷰행렬만큼 이동 회전했다고 생각하지만 실제로는 카메라는 가만히 있고,
	// 오브젝트들이 뷰행렬의 반대로 같은 값만큼 움직인 것이다.
	// 그래서 실제 뷰행렬로 사용되는건 구한 행렬의 역행렬이다.

	float4x4 projectionMatrix_;
	//투영행렬: 뷰행렬로 재배치된 뷰공간 안의 오브젝트들을 2차원으로 변환하는 과정을 투영변환이라고 하는데, 
	// 이 과정에 필요한 행렬. 크게 직교투영과 원근투영 두가지 투영방식으로 나눈다. 
	//투영행렬을 거치고 난 모든 카메라의 시야범위(보통 절두체(frustum) 형태를 가지기 때문에 뷰 절두체, 뷰 프러스텀이라고 한다)
	// 안에 들어온 정점들의 좌표는 -1 <= x <= 1, -1 <= y <= 1, 0 <= z <=1 범위로 들어오게 된다.
	//뷰 프러스텀 밖에 있어서 저 값을 벗어난 정점들은 투영 대상에서 제외되어 화면에 그려지지 않는다.

	//직교투영: 근평면과의 거리 상관없이 오브젝트 자체의 크기만 반영해서 -1~1 범위로 축소하는 투영. 소실점이 없다.
	// 정점좌표 벡터의 w값은 항상 1로 고정된다. 그래서 신경 쓸 필요 없다.

	//원근투영: 근평면에서 떨어진 거리에 비례해서 가까운 오브젝트는 크게, 멀리 있는 오브젝트는 작게 조정해서
	// -1~1 범위로 축소하는 투영방식. 소실점이 있다.
	//정점좌표 벡터의 w값은 뷰공간 내 z값에 따라서 0~1사이의 값을 가진다. 
	//투영행렬까지 곱한 정점좌표 벡터를 이 w값으로 나누어 주어야 비로소 투영행렬 적용이 끝난다.

	//원근 투영에 탄젠트를 쓰는 이유: 
	// 특정 위치의 정점을 투영변환 후 뷰포트 변환하는 과정을 거칠 때, 
	// 정점 좌표의 x값 / z값, y값 / z값의 비율을 만드는 탄젠트 각도를 저장해 두었다면, 
	// z값 * 아크 탄젠트(각도) 공식을 통해 새로운 z값이 얼마인지에 상관없이,
	// 뷰 스페이스내 평면에 투영변환 이전의 원래 상대좌표를 유지한 상태의 정점을 화면에 그릴 수 있다.
	//그 탄젠트 각도는 정점 좌표 벡터의 w에 저장된다.



	CameraProjectionMode projectionMode_;	//직교투영/원근투영 설정. 

	float4 size_;	//투영행렬을 계산할 기준 평면 == 내가 사용중인 윈도우의 크기. 근평면이라는 보장은 없음.
	float nearZ_;		//원근 중심에서 근평면까지의 거리. 
	float farZ_;		//원근 중심에서 원평면까지의 거리.
	float fovAngleY_;	//FoV(Field of View): 화각, 시야 범위. Y이므로 세로길이를 형성하는 각도.

	float4x4 viewportMatrix_;
	//뷰포트행렬: 투영변환을 통해 축소시킨 뷰 공간의 오브젝트들을 원하는 크기만큼 다시 확대시키는 뷰포트 변환을 할 때 필요한 행렬.

	//typedef struct D3D11_VIEWPORT
	//{
	//	FLOAT TopLeftX;		뷰포트 변환할 윈도우의 좌상단 x좌표.
	//	FLOAT TopLeftY;		뷰포트 변환할 윈도우의 좌상단 y좌표.
	//	FLOAT Width;		뷰포트 변환할 윈도우의 가로길이.
	//	FLOAT Height;		뷰포트 변환할 윈도우의 세로길이.
	//	FLOAT MinDepth;		뷰포트 최소깊이(0~1). 웬만하면 0으로 하는것이 좋다.
	//	FLOAT MaxDepth;		뷰포트 최대깊이(0~1). 웬만하면 1로 하는것이 좋다.
	//} 	D3D11_VIEWPORT;

	D3D11_VIEWPORT viewportDesc_;
	//래스터라이저 단계에서 뷰포트 변환할 때 필요한 윈도우 위치, 크기 정보를 저장하는 D3D11_VIEWPORT구조체 객체.
	//렌더링 파이프라인상 순서는 래스터라이저이지만 뷰포트 변환할 때 필요한 윈도우 크기 정보를 전부 카메라가 가지고 있고,
	// 변경할 일도 거의 없으므로 래스터라이저 대신 카메라가 가진다.


	float4 prevMousePosition_;	//이전 마우스포인터 위치.
	float4 mouseDirection_;		//마우스포인터가 이동한 방향.

	//최종 결과물을 받는 렌더타겟.
	std::shared_ptr<GameEngineRenderTarget> conclusionRenderTarget_;

	//포워드렌더링용 렌더타겟.
	std::shared_ptr<GameEngineRenderTarget> forwardRenderTarget_;

	//디퍼드렌더링용 렌더타겟.
	std::shared_ptr<GameEngineRenderTarget> deferredRenderTarget_;

	//지오메트리버퍼 렌더타겟(이하 g버퍼).
	std::shared_ptr<GameEngineRenderTarget> geometryBufferRenderTarget_;

	//빛정보 저장용 렌더타겟.
	std::shared_ptr<GameEngineRenderTarget> lightDataBufferRenderTarget_;
	//사실 굳이 만들필요 없는데 값을 직접 받아보고 싶어서 추가.


	std::shared_ptr<class GameEngineRenderUnit> lightDataRenderUnit_;	//빛 정보 계산용 렌더유닛.

	std::shared_ptr<class GameEngineRenderUnit> mergerRenderUnit_;	//최종 통합 렌더유닛.





	std::set<std::shared_ptr<GameEngineLighting>> allLightings_;	//모든 조명 정보.

	LightingDatas lightingDatasInst_;	//모든 
};

