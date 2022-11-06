#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineCamera.h"
#include "GameEngineMaterial.h"
#include "GameEngineShaderResourceHelper.h"
#include "GameEngineMesh.h"

struct RenderOption
{
    float deltaTime_ = 0.f;
    float sumDeltaTime_ = 0.f;      
    int isAnimation_ = 0;    
    int temp02_ = 0;
};

class GameEngineRenderUnit
{
    //�� �����ӿ�ũ���� �������� �ʼ����� �ΰ��� ����� ������ ���������ΰ� ���̴����ҽ����۸� 
    // �ѵ� ��� �������� ���� �����ϱ� ���ϱ� ���� ���� Ŭ����.
    //�پ��� ������ �޽��� �����ؼ� ����ϱ� �� �� ������ ü��.

    friend class GameEngineRenderer;
    //���̴����ҽ����� ������ ����ؼ� ������.

public:
    GameEngineRenderUnit();
    ~GameEngineRenderUnit();

    GameEngineRenderUnit(const GameEngineRenderUnit& _other);
    //GameEngineRenderUnit(GameEngineRenderUnit&& _other) noexcept;
private:
    GameEngineRenderUnit& operator=(const GameEngineRenderUnit& _other) = delete;
    GameEngineRenderUnit& operator=(GameEngineRenderUnit&& _other) = delete;

public:
    //�������ֿ� ���׸����� �����ϴ� �Լ�.
    void SetMaterial(const std::string_view& _materialName);

    //�������ֿ� �޽��� �����ϴ� �Լ�. 
    void SetMesh(const std::string_view& _meshName);
    void SetMesh(GameEngineMesh* _mesh);

    //�� �θ� �������� �����ϰ� ���������� ���� ���̴����ҽ����ۿ�
    // ���� �⺻���� ��������� "TRANSFORMDATA"�� "RENDEROPTION"�� ����ϴ� �Լ�.
    void EngineShaderResourceSetting(GameEngineRenderer* _parentRenderer);

    //���������� ���̴����ҽ����ۿ� ����� ���̴����ҽ����� ������ ������������ ���� 
    // �θ� �������� ��ϵ� ī�޶��� ����Ÿ�ٿ� �ű�� �Լ�.
    void Render(float _deltaTime);

    GameEngineMaterial* GetMaterial();

    GameEngineMaterial* GetCloneMaterial();

    GameEngineMaterial* CloneMaterial(GameEngineMaterial* _original);

    //�������ֿ� �θ� �������� �����ϰ� EngineShaderResourceSetting() �Լ��� ȣ���ؼ� ���� �⺻ ������۸� ����ϴ� �Լ�.
    void SetRenderer(GameEngineRenderer* _parentRenderer);    


public:
    inline GameEngineShaderResourceHelper& GetShaderResourceHelper()
    {
        return this->shaderResourceHelper_;
    }


private:
    GameEngineRenderer* parentRenderer_;    //�� ���������� ���� �θ� ������.

    GameEngineMesh* mesh_;                  //

    GameEngineInputLayout* inputLayout_;    //

    GameEngineMaterial* material_;    //���̴����ҽ����� ����Ÿ�ٿ� �׸� ���׸���.

    D3D11_PRIMITIVE_TOPOLOGY topology_;     //

    GameEngineShaderResourceHelper shaderResourceHelper_;   //���̴����ҽ����� ���� ���̴����ҽ� ����.
    //������ ����: �������ָ��� ������ ���̴����ҽ����۸� ������ �ϱ� ���ؼ�.
};

class GameEngineShaderResourceHelper;
class GameEngineMaterial;
class GameEngineRenderer: public GameEngineTransformComponent
{
    //��� �������� ���������� ������ �ϴ� ��ɸ��� �ּ��ѵ��� ���� �������̽� Ŭ����.
    //�������� ������ Ʈ������ ������ ������ ���ӿ���ī�޶� ��ϵǾ� ������ ����� �ǰ�, 
    //�ڽ� ���������� ������ �����Ѵ�.

	friend GameEngineLevel;
	friend class GameEngineCamera;

public:

	GameEngineRenderer();
	~GameEngineRenderer();

	GameEngineRenderer(const GameEngineRenderer& _other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _other) = delete;

public:
	void ChangeCamera(CameraOrder _order);
    void SetRenderingOrder(int _renderingOrder);
    bool IsInstancing(GameEngineMaterial* _pipeLine);
    void InstancingDataSetting(GameEngineMaterial* _pipeLine);

public:
    inline int GetRenderingOrder()
    {
        return renderingOrder_;
    }

    virtual void InstancingOn()
    {
        isInstancing_ = true;
    }

public:
    RenderOption renderOptionInst_;

protected:
	virtual void Start();
	virtual void Render(float _deltaTime) = 0;	

	void PushRendererToMainCamera();	//�������� ����ī�޶� ����ϴ� �Լ�.
	void PushRendererToUICamera();		//�������� UIī�޶� ����ϴ� �Լ�.

protected:
    class GameEngineCamera* camera_;    //�������� ��ϵ� ī�޶�.

private:
	CameraOrder cameraOrder_;
    int renderingOrder_;
    bool isInstancing_;
};

