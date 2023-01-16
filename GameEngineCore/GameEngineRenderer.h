#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineCamera.h"
#include "GameEngineMaterial.h"
#include "GameEngineShaderResourceHelper.h"
#include "GameEngineMesh.h"
#include "GlobalHeader.h"

class GameEngineRenderUnit
{
    //�� �����ӿ�ũ���� �������� �ʼ����� ����� �޽�, ���׸���� ���̴����ҽ����۸� 
    // �ѵ� ��� �������� ���� �����ϱ� ���ϱ� ���� ���� Ŭ����.
    //�پ��� ������ �޽��� �����ؼ� ����ϱ� �� �� ������ ü��.

    friend class GameEngineRenderer;
    //���̴����ҽ����� ������ ����ؼ� ������.

public:
    GameEngineRenderUnit();
    ~GameEngineRenderUnit();

    GameEngineRenderUnit(const GameEngineRenderUnit& _other);
    //GameEngineRenderUnit(GameEngineRenderUnit&& _other) noexcept = delete;

private:
    GameEngineRenderUnit& operator=(const GameEngineRenderUnit& _other) = delete;
    GameEngineRenderUnit& operator=(GameEngineRenderUnit&& _other) = delete;

public:
    //�������ֿ� �޽��� �����ϴ� �Լ�. 
    void SetMesh(const std::string_view& _meshName);
    void SetMesh(GameEngineMesh* _mesh);

    //�������ֿ� ���׸����� �����ϴ� �Լ�.
    void SetMaterial(const std::string_view& _materialName);

    //�� �θ� �������� �����ϰ� ���������� ���� ���̴����ҽ����ۿ�
    // ���� �⺻���� ��������� "TRANSFORMDATA"�� "RENDEROPTION"�� ����ϴ� �Լ�.
    void EngineShaderResourceSetting(GameEngineRenderer* _parentRenderer);

    //���������� ���̴����ҽ����ۿ� ����� ���̴����ҽ����� ������ ������������ ���� 
    // �θ� �������� ��ϵ� ī�޶��� ����Ÿ�ٿ� �ű�� �Լ�.
    void Render(float _deltaTime);

    GameEngineMesh* GetMesh();
    GameEngineMaterial* GetMaterial();

    //�������ֿ� �θ� �������� �����ϰ� EngineShaderResourceSetting() �Լ��� ȣ���ؼ� ���� �⺻ ������۸� ����ϴ� �Լ�.
    void SetRenderer(GameEngineRenderer* _parentRenderer);


public:
    inline GameEngineShaderResourceHelper& GetShaderResourceHelper()
    {
        return this->shaderResourceHelper_;
    }

public:
    //Render()�Լ��� �⺻���� ������ ��ɿ� �߰������� �ʿ��� ���� �ְų�, �ƿ� ������ ����� ��ü�ؾ� �ϴ� ��� ����ϴ� �Լ�������.
    std::function<bool(float)> specialRenderingFunction_;
    //true: �� �Լ��� ���� �Ŀ��� ������ ������ ����� ���� �����Ѵ�.
    //false: �� �Լ��� ������ Render()�Լ��� �ٷ� ������.

private:

    GameEngineRenderer* parentRenderer_;    //�� ���������� ���� �θ� ������.

    GameEngineMesh* mesh_;                  //�޽�.

    GameEngineInputLayout* inputLayout_;    //��ǲ ���̾ƿ�.

    GameEngineMaterial* material_;    //���̴����ҽ����� ����Ÿ�ٿ� �׸� ���׸���.

    D3D11_PRIMITIVE_TOPOLOGY topology_;     //��������.

    GameEngineShaderResourceHelper shaderResourceHelper_;   //���̴����ҽ����� ���� ���̴����ҽ� ����.
    //������ ����: �������ָ��� ������ ���̴����ҽ����۸� ������ �ϱ� ���ؼ�.
};

class GameEngineShaderResourceHelper;
class GameEngineMaterial;
class GameEngineRenderer : public GameEngineTransformComponent
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

public:
    inline int GetRenderingOrder()
    {
        return renderingOrder_;
    }

    inline GameEngineCamera* GetCamera()
    {
        return this->camera_;
    }

public:
    RenderOption renderOptionInst_;


protected:
    virtual void Start();
    virtual void Render(float _deltaTime) = 0;
    virtual void DeferredRender(float _deltaTime) = 0;
    virtual void RenderShadow(float _deltaTime) = 0;

    void PushRendererToMainCamera();	//�������� �ڱ� �ڽ��� ����ī�޶� ����ϴ� �Լ�.
    void PushRendererToUICamera();		//�������� �ڱ� �ڽ��� UIī�޶� ����ϴ� �Լ�.

protected:
    GameEngineCamera* camera_;    //�� �������� ��ϵ� ī�޶�.

private:
    CameraOrder cameraOrder_;
    int renderingOrder_;
};

