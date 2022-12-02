#pragma once
#include "GameEngineMaterial.h"
#include "GameEngineShaderResourceHelper.h"
#include "GameEngineMesh.h"

struct RenderOption
{
    float deltaTime_ = 0.f;
    float sumDeltaTime_ = 0.f;
    int isAnimation_ = 0;
    int vertexInversion_ = 1;   //그림자용 정점 좌우 뒤집힘 표시 변수. 좌우 뒤집어야 하면 -1 대입.
    float pivotPosX_ = 0.f;     //피봇포스 X
    float pivotPosY_ = 0.f;     //피봇포스 Y
    float shadowAngle_ = 30.f;  //그림자 각도. 기본값 30도.
    int bytePad1_ = 0;          //바이트패드.
};

//class GameEngineInstancingRenderUnit : public std::enable_shared_from_this<GameEngineInstancingRenderUnit>
//{
//    //이 프레임워크에서 렌더링에 필수적인 두가지 요소인 렌더링 파이프라인과 셰이더리소스헬퍼를 
//    // 한데 모아 렌더러를 통해 관리하기 편하기 위해 만든 클래스.
//    //다양한 종류의 메쉬를 세팅해서 사용하기 좀 더 편해진 체제.
//
//    friend class GameEngineRenderer;
//    //셰이더리소스헬퍼 가져다 써야해서 프렌드.
//
//public:
//    GameEngineInstancingRenderUnit();
//    ~GameEngineInstancingRenderUnit();
//
//    GameEngineInstancingRenderUnit(const GameEngineInstancingRenderUnit& _other) = delete;
//    GameEngineInstancingRenderUnit(GameEngineInstancingRenderUnit&& _other) noexcept = delete;
//
//private:
//    GameEngineInstancingRenderUnit& operator=(const GameEngineInstancingRenderUnit& _other) = delete;
//    GameEngineInstancingRenderUnit& operator=(GameEngineInstancingRenderUnit&& _other) = delete;
//
//public:
//
//    void SetMesh(const std::string_view& _meshName);
//    void SetMesh(std::shared_ptr<GameEngineMesh> _mesh);
//
//    void SetMaterial(const std::string_view& _materialName);
//
//    //새 부모 렌더러를 지정하고 렌더유닛이 가진 셰이더리소스헬퍼에
//    // 엔진 기본제공 상수버퍼인 "TRANSFORMDATA"와 "RENDEROPTION"을 등록하는 함수.
//    //void EngineShaderResourceSetting(std::shared_ptr<GameEngineRenderer> _parentRenderer);
//
//    void RenderInstancing(
//        float _deltaTime,
//        size_t _instancingDataCount,
//        std::shared_ptr<class GameEngineInstancingBuffer> _instancingBuffer
//    );
//
//    std::shared_ptr<GameEngineMesh> GetMesh();
//    std::shared_ptr<GameEngineMaterial> GetMaterial();
//
//
//public:
//    inline GameEngineShaderResourceHelper& GetShaderResourceHelper()
//    {
//        return this->shaderResourceHelper_;
//    }
//
//
//private:
//    //std::weak_ptr<GameEngineRenderer> parentRenderer_;    //이 렌더유닛을 가진 부모 렌더러.
//
//    std::shared_ptr<GameEngineMesh> mesh_;                  //
//
//    std::shared_ptr<GameEngineInputLayout> inputLayout_;    //
//
//    std::shared_ptr<GameEngineMaterial> material_;    //셰이더리소스들을 렌더타겟에 그릴 마테리얼.
//
//    D3D11_PRIMITIVE_TOPOLOGY topology_;     //
//
//    GameEngineShaderResourceHelper shaderResourceHelper_;   //셰이더리소스들을 가진 셰이더리소스 헬퍼.
//    //값형인 이유: 렌더유닛마다 각각의 셰이더리소스헬퍼를 가지게 하기 위해서.
//};

class GameEngineInstancingRenderer
{
	//이 클래스의 존재 이유:
public:
	GameEngineInstancingRenderer();
	~GameEngineInstancingRenderer();

protected:
	GameEngineInstancingRenderer(const GameEngineInstancingRenderer& _other) = delete;
	GameEngineInstancingRenderer(GameEngineInstancingRenderer&& _other) noexcept = delete;

private:
	GameEngineInstancingRenderer& operator=(const GameEngineInstancingRenderer& _other) = delete;
	GameEngineInstancingRenderer& operator=(const GameEngineInstancingRenderer&& _other) = delete;


public:	



private:

};

