#pragma once
#include "GameEngineLevel.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineLighting.h"

enum class RenderingPath
{
	ForwardRendering,	//�Ϲ� ������.
	DeferredRendering,	//���� ������.
	None
};

enum class CameraProjectionMode
{
	Perspective, //��������.
	Orthographic //��������.
};

class GameEngineInstancingRenderer;
class GameEngineInstancing;
class GameEngineMaterial;
class GameEngineCamera : public GameEngineTransformComponent
{
	//ī�޶�. 
	//��������� ������Ʈ���� �� �����̽���� �ϴ� ������ ī�޶� �þ߹��� �ȿ� ��� ������, 
	// ������Ʈ���� �����ϴ� �������� ����Ŀ� ���缭 ���ġ�ϰ� ������Ŀ� ���缭 ����� ��
	// ����Ʈ��Ĵ�� �ٽ� Ȯ���� ��ŭ�� ���� ��ǥ�� ����ؼ� ������ ��� �׸��� ������Ʈ.

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
	//���콺 �������� ��ġ�� ������ ��ũ�� ��ǥ�� �޾ƿ��� �Լ�.
	float4 GetMouseScreenPosition();

	//���콺 �������� ��ġ�� ������ǥ(���� ī�޶� ����)�� �޾ƿ��� �Լ�.
	float4 GetMouseWorldPosition();

	//���콺 �������� ��ġ�� ������ǥ(�̵� ī�޶� ����)�� �޾ƿ��� �Լ�.
	float4 GetMouseWorldPositionToActor();

	//�־��� ������ǥ�� ��������ǥ�� �ٲٴ� �Լ�.
	float4 GetWorldPositionToScreenPosition(const float4& _worldPosition);

	//ī�޶��� ������ �����ϴ� �Լ�.
	void SetCameraOrder(CameraOrder _order);
	//�� ���� �������� �𸣰�����, ī�޶� ���� ��Ÿ�ӿ� ���� ����.

	//�ν��Ͻ� ��ȯ. ���ٸ� �� �ν��Ͻ��� ���� ��ȯ�Ѵ�.
	GameEngineInstancing& GetInstancing(const std::string& _name);

	//�ν��Ͻ̷����� ��ȯ. ���ٸ� �� �ν��Ͻ̷������� ���� ��ȯ�Ѵ�.
	std::shared_ptr<GameEngineInstancingRenderer> GetInstancingRenderer(const std::string& _name);

	//ī�޶� ���� �߰�.
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

	//�� ī�޶��� ���� ����Ÿ���� �������� �Լ�.
	inline std::shared_ptr<class GameEngineRenderTarget> GetConclusionRenderTarget()
	{
		return conclusionRenderTarget_;
	}

	//�� ī�޶��� �����巻������ ����Ÿ���� �������� �Լ�.
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
	//�� ī�޶� ���� �������鿡�� �� ī�޶� ���� ����Ÿ�ٿ� ������ ������ �����Ű�� �ϴ� �Լ�.
	void Render(float _deltaTime);

	//�־��� �������� �� ī�޶� ����ϴ� �Լ�.
	void PushRenderer(std::shared_ptr<GameEngineRenderer> _renderer);

	//�������� ��� �����ϴ� �Լ�. ���� �����ϴ� �Լ��� �ƴԿ� ������ ��.
	void Release(float _deltaTime);

	void Update(float _dletaTime) override;

	//�� ī�޶��� ���������� �ٸ� ������ ī�޶�� �ű�� �Լ�.
	void OverRenderer(std::shared_ptr<GameEngineCamera> _nextCamera);

	//������ ���� ����.
	void ChangeRenderingOrder(std::shared_ptr<GameEngineRenderer> _renderer, int _newRenderingOrder);

private:
	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>> allRenderers_;	//�� ī�޶� ���� ��� ��������.
	//������������ ���� �з��� �� ���� ������ zsort() �Լ��� z�� ������� �����Ѵ�. 

	std::unordered_map<std::string, GameEngineInstancing> instancingMap_;	//
	//������ ������ �� ����: ��ȸ�� ���� ���� �����Ŷ�� ������ ��Ȳ���� ������ ���� �׳� �Ẹ�� �;.

	std::map<std::string, std::shared_ptr<GameEngineInstancingRenderer>> instancingRenderers_;

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



	CameraProjectionMode projectionMode_;	//��������/�������� ����. 

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
	std::shared_ptr<GameEngineRenderTarget> conclusionRenderTarget_;

	//�����巻������ ����Ÿ��.
	std::shared_ptr<GameEngineRenderTarget> forwardRenderTarget_;

	//���۵巻������ ����Ÿ��.
	std::shared_ptr<GameEngineRenderTarget> deferredRenderTarget_;

	//������Ʈ������ ����Ÿ��(���� g����).
	std::shared_ptr<GameEngineRenderTarget> geometryBufferRenderTarget_;

	//������ ����� ����Ÿ��.
	std::shared_ptr<GameEngineRenderTarget> lightDataBufferRenderTarget_;
	//��� ���� �����ʿ� ���µ� ���� ���� �޾ƺ��� �; �߰�.


	std::shared_ptr<class GameEngineRenderUnit> lightDataRenderUnit_;	//�� ���� ���� ��������.

	std::shared_ptr<class GameEngineRenderUnit> mergerRenderUnit_;	//���� ���� ��������.





	std::set<std::shared_ptr<GameEngineLighting>> allLightings_;	//��� ���� ����.

	LightingDatas lightingDatasInst_;	//��� 
};

