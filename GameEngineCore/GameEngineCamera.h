#pragma once
#include "GameEngineLevel.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineLighting.h"

enum class ProjectionMode
{
	Perspective, //��������.
	Orthographic //��������.
};

class GameEngineInstanceRenderer;
class GameEngineMaterial;
class GameEngineRenderTarget;
class GameEngineRenderUnit;
class GameEngineCamera : public GameEngineTransformComponent
{
	//ī�޶�. 
	//��������� ������Ʈ���� �� ���������̶�� �ϴ� ������ ī�޶� �þ߹��� �ȿ� ��� ������, 
	// ������Ʈ���� �����ϴ� �������� ����Ŀ� ���缭 ���ġ�ϰ� ������Ŀ� ���缭 ����� ��
	// ����Ʈ��Ĵ�� �ٽ� Ȯ���� ��ŭ�� ���� ��ǥ�� ����ؼ� ������ ��� �׸��� ������Ʈ.

	friend GameEngineLevel;
	friend GameEngineRenderer;

public:

	GameEngineCamera();
	~GameEngineCamera();

	GameEngineCamera(const GameEngineCamera& _other) = delete;
	GameEngineCamera(GameEngineCamera&& _other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _other) = delete;

public:
	//�־��� ������ǥ�� ��������ǥ�� �ٲٴ� �Լ�.
	float4 ConvertWorldPositionToScreenPosition(const float4& _worldPosition);

	//�־��� ������ǥ�� �������ǥ�� �ٲٴ� �Լ�.
	float4 ConvertWorldPositionToViewPosition(const float4& _worldPosition);

	//���콺 �������� ��ġ�� ������ ��ũ�� ��ǥ�� �޾ƿ��� �Լ�.
	float4 GetMousePositionInScreen();

	//���콺 �������� ��ġ�� ����� �������� �޾ƿ��� �Լ�.
	float4 GetMousePositionInViewSpace();

	//���콺 �������� ��ġ�� ������� �������� �޾ƿ��� �Լ�.
	float4 GetMousePositionInWorldSpace();

	//�� ī�޶󿡼� ���콺 �����͹������� ���� ������ ������� ���⺤�͸� �޾ƿ��� �Լ�. 
	float4 GetRayTowardMousePointer();


	//ī�޶��� ������ �����ϴ� �Լ�.
	void SetCameraOrder(CameraOrder _order);
	//�� ���� �������� �𸣰�����, ��Ÿ�� �߰��� ī�޶� ���� ���� ����.

	//�ν��Ͻ̷����� ��ȯ. ���ٸ� �� �ν��Ͻ̷������� ���� ��ȯ�Ѵ�.
	GameEngineInstanceRenderer& GetInstanceRenderer(const std::string_view& _name);

	//ī�޶� ���� �߰�.
	void PushLighting(GameEngineLighting* _newLighting);

public:
	void SetProjectionMode(ProjectionMode _mode)
	{
		projectionMode_ = _mode;
	}

	inline const float4& GetMouseDirection()
	{
		return mouseDirection_;
	}

	ProjectionMode GetProjectionMode()
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

	inline const float4x4& GetViewMatrix() const
	{
		return viewMatrix_;
	}

	inline const float4x4& GetProjectionMatrix() const
	{
		return projectionMatrix_;
	}

	//�� ī�޶��� ���� ����Ÿ���� �������� �Լ�.
	GameEngineRenderTarget* GetConclusionRenderTarget()
	{
		return conclusionRenderTarget_;
	}

	//�� ī�޶��� �����巻������ ����Ÿ���� �������� �Լ�.
	GameEngineRenderTarget* GetForwardRenderTarget()
	{
		return forwardRenderTarget_;
	}

	//�� ī�޶��� ���۵巻������ ����Ÿ���� �������� �Լ�.
	GameEngineRenderTarget* GetDeferredRenderTarget()
	{
		return deferredRenderTarget_;
	}

	//�� ī�޶��� GBuffer ����Ÿ���� �������� �Լ�.
	GameEngineRenderTarget* GetGBufferRenderTarget()
	{
		return geometryBufferRenderTarget_;
	}

	//�� ī�޶� ���� ��� �������� ��ȯ.
	AllLightingDatas& GetLightingDatas()
	{
		return lightingDatasInst_;
	}

	void SetFarZ(float _farZ)
	{
		this->farZ_ = _farZ;
	}


protected:
	void Start();

private:
	//�� ī�޶� ���� �������鿡�� �� ī�޶� ���� ����Ÿ�ٿ� ������ ������ �����Ű�� �ϴ� �Լ�.
	void Render(float _deltaTime);

	//�־��� �������� �� ī�޶� ����ϴ� �Լ�.
	void PushRenderer(GameEngineRenderer* _renderer);

	//�������� ��� �����ϴ� �Լ�. ���� �����ϴ� �Լ��� �ƴԿ� ������ ��.
	void Release(float _deltaTime);

	void Update(float _dletaTime) override;

	//�� ī�޶��� ���������� �ٸ� ������ ī�޶�� �ű�� �Լ�.
	void OverRenderer(GameEngineCamera* _nextCamera);

	//������ ���� ����.
	void ChangeRenderingOrder(GameEngineRenderer* _renderer, int _newRenderingOrder);

	//���콺 ������ �̵����� ������Ʈ �Լ�.
	void UpdateMouseDirection();

private:
	std::map<int, std::list<GameEngineRenderer*>> allRenderers_;	//�� ī�޶� ���� ��� ��������.
	//������������ ���� �з��� �� ���� ������ zsort() �Լ��� z�� ������� �����Ѵ�. 

	std::map<std::string, GameEngineInstanceRenderer> allInstancingRenderers_;

	//������ ��(Unordered Map): ������ Ű���� �ؽ��Լ��� ���ļ� ���� ���ڷ� �ٲ㼭, 
	// �� ���� �ε����� �ϴ� �迭 �� ���ҷ� �����͸� �����ϴ� ����� �����̳�. 
	//�������δ� �˻� �ӵ��� '��ü��' �ٸ� �����̳ʵ麸�� �����ٰ� �Ѵ�(�׻� �׷��� ����).
	//�������δ� �̸���� Ű�� ������ ���� �ʰ�, ��ȸ ȿ���� ��������, �ؽ� �浹�� ���� �߻��� ���� �˻� ȿ���� ��������,
	// �־��� ��� ���� �ð����⵵�� ���̰� �ȴٰ� �Ѵ�.

	//�ؽ� �浹: �ٸ� �Է°��� �ؽ� �Լ��� �־��µ� ���� ������� ���ͼ� �� �Է°��� ������ �� ���� �Ǵ� ����.
	// �ؽ� �浹 Ȯ���� ���� ���� �� ���� �ؽ� �Լ���� �Ѵ�.


	float4x4 viewMatrix_;
	//�����: ��������� ���� �������� ��ġ�� ���� ��������, ī�޶� ��ġ�� ������ �� ����� �ȿ� ��� ���ġ�ؼ�, 
	// ��������� ��ġ�Ǿ��� �״�� ȭ�� �ȿ� ���̰� �� �� ����ϴµ� �ʿ��� ���. 
	//���� ��ü�� ������Ʈ�� ���ġ�ϴ� Ư����, ������� ���� ��ü�� ����ȴ�.
	//ī�޶� ����ĸ�ŭ �̵� ȸ���ߴٰ� ���������� �����δ� ī�޶�� ������ �ְ�,
	// ������Ʈ���� ������� �ݴ�� ���� ����ŭ ������ ���̴�.
	// �׷��� ���� ����ķ� ���Ǵ°� ���� ����� ������̴�.

	float4x4 projectionMatrix_;
	//�������: ����ķ� ���ġ�� ����� ���� ������Ʈ���� 2�������� ��ȯ�ϴ� ������ ������ȯ�̶�� �ϴµ�, 
	// �� ������ �ʿ��� ���. ũ�� ���������� �������� �ΰ��� ����������� ������. 
	//��������� ��ġ�� �� ��� ī�޶��� �þ߹���(���� ����ü(frustum) ���¸� ������ ������ �� ����ü, �� ���������̶�� �Ѵ�)
	// �ȿ� ���� �������� ��ǥ�� -1 <= x <= 1, -1 <= y <= 1, 0 <= z <=1 ������ ������ �ȴ�. 
	// �̷��� ��ǥ�踦 NDC(Normalized Device Coodinate)��ǥ���� �Ѵ�.
	//�� �������� �ۿ� �־ �� ���� ��� �������� ���� ��󿡼� ���ܵǾ� ȭ�鿡 �׷����� �ʴ´�.

	//��������: �������� �Ÿ� ������� ������Ʈ ��ü�� ũ�⸸ �ݿ��ؼ� -1~1 ������ ����ϴ� ����. �ҽ����� ����.
	// ������ǥ ������ w���� �׻� 1�� �����ȴ�. �׷��� �Ű� �� �ʿ� ����.

	//��������: ����鿡�� ������ �Ÿ��� ����ؼ� ����� ������Ʈ�� ũ��, �ָ� �ִ� ������Ʈ�� �۰� �����ؼ�
	// -1~1 ������ ����ϴ� �������. �ҽ����� �ִ�.
	//������ǥ ������ w���� ����� �� z���� ���� 0~1������ ���� ������. 
	//������ı��� ���� ������ǥ ���͸� �� w������ ������ �־�� ��μ� ������� ������ ������.

	//���� ������ ź��Ʈ�� ���� ����: 
	// Ư�� ��ġ�� ������ ������ȯ �� ����Ʈ ��ȯ�ϴ� ������ ��ĥ ��, 
	// ���� ��ǥ�� x�� / z��, y�� / z���� ������ ����� ź��Ʈ ������ ������ �ξ��ٸ�, 
	// z�� * ��ũ ź��Ʈ(����) ������ ���� ���ο� z���� �������� �������,
	// �� �����̽��� ��鿡 ������ȯ ������ ���� �����ǥ�� ������ ������ ������ ȭ�鿡 �׸� �� �ִ�.
	//�� ź��Ʈ ������ ���� ��ǥ ������ w�� ����ȴ�.



	ProjectionMode projectionMode_;	//��������/�������� ����. 

	float4 size_;	//��������� ����� ���� ��� == ���� ������� �������� ũ��. ������̶�� ������ ����.
	float nearZ_;		//���� �߽ɿ��� ���������� �Ÿ�. 
	float farZ_;		//���� �߽ɿ��� ���������� �Ÿ�.
	float fovAngleY_;	//FoV(Field of View): ȭ��, �þ� ����. Y�̹Ƿ� ���α��̸� �����ϴ� ����.

	float4x4 viewportMatrix_;
	//����Ʈ���: ������ȯ�� ���� ��ҽ�Ų �� ������ ������Ʈ���� ���ϴ� ũ�⸸ŭ �ٽ� Ȯ���Ű�� ����Ʈ ��ȯ�� �� �� �ʿ��� ���.

	//typedef struct D3D11_VIEWPORT
	//{
	//	FLOAT TopLeftX;		����Ʈ ��ȯ�� �������� �»�� x��ǥ.
	//	FLOAT TopLeftY;		����Ʈ ��ȯ�� �������� �»�� y��ǥ.
	//	FLOAT Width;		����Ʈ ��ȯ�� �������� ���α���.
	//	FLOAT Height;		����Ʈ ��ȯ�� �������� ���α���.
	//	FLOAT MinDepth;		����Ʈ �ּұ���(0~1). �����ϸ� 0���� �ϴ°��� ����.
	//	FLOAT MaxDepth;		����Ʈ �ִ����(0~1). �����ϸ� 1�� �ϴ°��� ����.
	//} 	D3D11_VIEWPORT;

	D3D11_VIEWPORT viewportDesc_;
	//�����Ͷ����� �ܰ迡�� ����Ʈ ��ȯ�� �� �ʿ��� ������ ��ġ, ũ�� ������ �����ϴ� D3D11_VIEWPORT����ü ��ü.
	//������ ���������λ� ������ �����Ͷ����������� ����Ʈ ��ȯ�� �� �ʿ��� ������ ũ�� ������ ���� ī�޶� ������ �ְ�,
	// ������ �ϵ� ���� �����Ƿ� �����Ͷ����� ��� ī�޶� ������.


	float4 prevMousePosition_;	//���� ���콺������ ��ġ.
	float4 mouseDirection_;		//���콺�����Ͱ� �̵��� ����.

	//���� ������� �޴� ����Ÿ��.
	GameEngineRenderTarget* conclusionRenderTarget_;

	//������ �������� ����Ÿ��.
	GameEngineRenderTarget* forwardRenderTarget_;

	//���۵� �������� ����Ÿ��.
	GameEngineRenderTarget* deferredRenderTarget_;

	//������Ʈ�� ���� ����Ÿ��(���� g����).
	GameEngineRenderTarget* geometryBufferRenderTarget_;
	//������Ʈ�� ���̰��� ���⿡ �����Ѵ�.

	//�׸��� ���̰� ����� ����Ÿ��.
	GameEngineRenderTarget* shadowDepthRenderTarget_;

	//�� ���� ������ ����� ����Ÿ��.
	GameEngineRenderTarget* lightRatioBufferRenderTarget_;

	//������ ����� ����Ÿ��.
	GameEngineRenderTarget* lightDataBufferRenderTarget_;


	class GameEngineRenderUnit* lightRatioRenderUnit_;	//�� ���� ����� ��������.

	class GameEngineRenderUnit* lightDataRenderUnit_;	//�� ���� ���� ��������.

	class GameEngineRenderUnit* mergeRenderUnit_;	//���� ���� ��������.





	std::set<GameEngineLighting*> allLightings_;	//��� ���� ����.

	AllLightingDatas lightingDatasInst_;	//�� ī�޶��� ��� ���� �����͵�. 
};

