#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineCamera.h"
#include "GameEngineMaterial.h"
#include "GameEngineShaderResourceHelper.h"
#include "GameEngineMesh.h"
#include "GlobalHeader.h"

class GameEngineRenderUnit
{
    //이 프레임워크에서 렌더링에 필수적인 요소인 메쉬, 마테리얼과 셰이더리소스헬퍼를 
    // 한데 모아 렌더러를 통해 관리하기 편하기 위해 만든 클래스.
    //다양한 종류의 메쉬를 세팅해서 사용하기 좀 더 편해진 체제.

    friend class GameEngineRenderer;
    //셰이더리소스헬퍼 가져다 써야해서 프렌드.

public:
    GameEngineRenderUnit();
    ~GameEngineRenderUnit();

    GameEngineRenderUnit(const GameEngineRenderUnit& _other);
    //GameEngineRenderUnit(GameEngineRenderUnit&& _other) noexcept = delete;

private:
    GameEngineRenderUnit& operator=(const GameEngineRenderUnit& _other) = delete;
    GameEngineRenderUnit& operator=(GameEngineRenderUnit&& _other) = delete;

public:
    //렌더유닛에 메쉬를 지정하는 함수. 
    void SetMesh(const std::string_view& _meshName);
    void SetMesh(GameEngineMesh* _mesh);

    //렌더유닛에 마테리얼을 지정하는 함수.
    void SetMaterial(const std::string_view& _materialName);

    //새 부모 렌더러를 지정하고 렌더유닛이 가진 셰이더리소스헬퍼에
    // 엔진 기본제공 상수버퍼인 "TRANSFORMDATA"와 "RENDEROPTION"을 등록하는 함수.
    void EngineShaderResourceSetting(GameEngineRenderer* _parentRenderer);

    //렌더유닛의 셰이더리소스헬퍼에 저장된 셰이더리소스들을 렌더링 파이프라인을 통해 
    // 부모 렌더러가 등록된 카메라의 렌더타겟에 옮기는 함수.
    void Render(float _deltaTime);

    GameEngineMesh* GetMesh();
    GameEngineMaterial* GetMaterial();

    //렌더유닛에 부모 렌더러를 지정하고 EngineShaderResourceSetting() 함수를 호출해서 엔진 기본 상수버퍼를 등록하는 함수.
    void SetRenderer(GameEngineRenderer* _parentRenderer);


public:
    inline GameEngineShaderResourceHelper& GetShaderResourceHelper()
    {
        return this->shaderResourceHelper_;
    }

public:
    //Render()함수의 기본적인 렌더링 기능에 추가적으로 필요한 것이 있거나, 아예 렌더링 기능을 대체해야 하는 경우 사용하는 함수포인터.
    std::function<bool(float)> specialRenderingFunction_;
    //true: 이 함수가 끝난 후에도 나머지 렌더링 기능을 마저 실행한다.
    //false: 이 함수가 끝나면 Render()함수를 바로 끝낸다.

private:

    GameEngineRenderer* parentRenderer_;    //이 렌더유닛을 가진 부모 렌더러.

    GameEngineMesh* mesh_;                  //메쉬.

    GameEngineInputLayout* inputLayout_;    //인풋 레이아웃.

    GameEngineMaterial* material_;    //셰이더리소스들을 렌더타겟에 그릴 마테리얼.

    D3D11_PRIMITIVE_TOPOLOGY topology_;     //토폴로지.

    GameEngineShaderResourceHelper shaderResourceHelper_;   //셰이더리소스들을 가진 셰이더리소스 헬퍼.
    //값형인 이유: 렌더유닛마다 각각의 셰이더리소스헬퍼를 가지게 하기 위해서.
};

class GameEngineShaderResourceHelper;
class GameEngineMaterial;
class GameEngineRenderer : public GameEngineTransformComponent
{
    //모든 렌더러가 공통적으로 가져야 하는 기능만을 최소한도로 가진 인터페이스 클래스.
    //실질적인 역할은 트랜스폼 정보를 가지고 게임엔진카메라에 등록되어 렌더링 대상이 되고, 
    //자식 렌더러들의 형식을 규정한다.

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

    void PushRendererToMainCamera();	//렌더러가 자기 자신을 메인카메라에 등록하는 함수.
    void PushRendererToUICamera();		//렌더러가 자기 자신을 UI카메라에 등록하는 함수.

protected:
    GameEngineCamera* camera_;    //이 렌더러가 등록된 카메라.

private:
    CameraOrder cameraOrder_;
    int renderingOrder_;
};

