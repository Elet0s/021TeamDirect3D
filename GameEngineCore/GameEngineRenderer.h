#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineShaderResourceHelper.h"
#include "GameEngineMesh.h"

struct RenderOption
{
    float deltaTime_ = 0.f;
    float sumDeltaTime_ = 0.f;      
    int temp01_ = 0;    
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

private:
    GameEngineRenderUnit(const GameEngineRenderUnit& _other) = delete;
    GameEngineRenderUnit(GameEngineRenderUnit&& _other) noexcept = delete;
    GameEngineRenderUnit& operator=(const GameEngineRenderUnit& _other) = delete;
    GameEngineRenderUnit& operator=(GameEngineRenderUnit&& _other) = delete;

public:
    //�������ֿ� ������ ������������ �����ϴ� �Լ�.
    void SetPipeLine(const std::string& _renderingPipeLineName);

    //�������ֿ� �޽��� �����ϴ� �Լ�. 
    void SetMesh(const std::string& _meshName);

    //�� �θ� �������� �����ϰ� ���������� ���� ���̴����ҽ����ۿ�
    // ���� �⺻���� ��������� "TRANSFORMDATA"�� "RENDEROPTION"�� ����ϴ� �Լ�.
    void EngineShaderResourceSetting(GameEngineRenderer* _parentRenderer);

    //���������� ���̴����ҽ����ۿ� ����� ���̴����ҽ����� ������ ������������ ���� 
    // �θ� �������� ��ϵ� ī�޶��� ����Ÿ�ٿ� �ű�� �Լ�.
    void Render(float _deltaTime);

    GameEngineRenderingPipeLine* GetPipeLine();

    GameEngineRenderingPipeLine* GetClonePipeLine();

    GameEngineRenderingPipeLine* ClonePipeLine(GameEngineRenderingPipeLine* _original);

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

    GameEngineRenderingPipeLine* renderingPipeLine_;    //���̴����ҽ����� ����Ÿ�ٿ� �׸� ������ ����������.

    D3D11_PRIMITIVE_TOPOLOGY topology_;     //

    GameEngineShaderResourceHelper shaderResourceHelper_;   //���̴����ҽ����� ���� ���̴����ҽ� ����.
    //������ ����: �������ָ��� ������ ���̴����ҽ����۸� ������ �ϱ� ���ؼ�.
};

class GameEngineShaderResourceHelper;
class GameEngineRenderingPipeLine;
class GameEngineRenderer: public GameEngineTransformComponent
{
    //��� �������� ���������� ������ �ϴ� ��ɸ��� �ּ��ѵ��� ���� �������̽� Ŭ����.
    //�������� ������ Ʈ������ ������ ������ ���ӿ���ī�޶� ��ϵǾ� ������ ����� �ǰ�, 
    //�ڽ� ���������� ������ �����Ѵ�.

	friend GameEngineLevel;
	friend class GameEngineCamera;

    friend GameEngineRenderUnit;
    //�����ɼ� ������ ����ؼ� ������.

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
    bool IsInstancing(GameEngineRenderingPipeLine* _pipeLine);
    void InstancingDataSetting(GameEngineRenderingPipeLine* _pipeLine);

public:
    inline int GetRenderingOrder()
    {
        return renderingOrder_;
    }

    virtual void InstancingOn()
    {
        isInstancing_ = true;
    }



protected:
	virtual void Start();
	virtual void Render(float _deltaTime) = 0;	

	void PushRendererToMainCamera();	//�������� ����ī�޶� ����ϴ� �Լ�.
	void PushRendererToUICamera();		//�������� UIī�޶� ����ϴ� �Լ�.

protected:
    class GameEngineCamera* camera_;    //�������� ��ϵ� ī�޶�.
    RenderOption renderOption_;

private:
	CameraOrder cameraOrder_;
    int renderingOrder_;
    bool isInstancing_;
};

