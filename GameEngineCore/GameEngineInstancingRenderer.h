#pragma once
#include "GameEngineMaterial.h"
#include "GameEngineShaderResourceHelper.h"
#include "GameEngineMesh.h"

struct RenderOption
{
    float deltaTime_ = 0.f;
    float sumDeltaTime_ = 0.f;
    int isAnimation_ = 0;
    int vertexInversion_ = 1;   //�׸��ڿ� ���� �¿� ������ ǥ�� ����. �¿� ������� �ϸ� -1 ����.
    float pivotPosX_ = 0.f;     //�Ǻ����� X
    float pivotPosY_ = 0.f;     //�Ǻ����� Y
    float shadowAngle_ = 30.f;  //�׸��� ����. �⺻�� 30��.
    int bytePad1_ = 0;          //����Ʈ�е�.
};

//class GameEngineInstancingRenderUnit : public std::enable_shared_from_this<GameEngineInstancingRenderUnit>
//{
//    //�� �����ӿ�ũ���� �������� �ʼ����� �ΰ��� ����� ������ ���������ΰ� ���̴����ҽ����۸� 
//    // �ѵ� ��� �������� ���� �����ϱ� ���ϱ� ���� ���� Ŭ����.
//    //�پ��� ������ �޽��� �����ؼ� ����ϱ� �� �� ������ ü��.
//
//    friend class GameEngineRenderer;
//    //���̴����ҽ����� ������ ����ؼ� ������.
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
//    //�� �θ� �������� �����ϰ� ���������� ���� ���̴����ҽ����ۿ�
//    // ���� �⺻���� ��������� "TRANSFORMDATA"�� "RENDEROPTION"�� ����ϴ� �Լ�.
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
//    //std::weak_ptr<GameEngineRenderer> parentRenderer_;    //�� ���������� ���� �θ� ������.
//
//    std::shared_ptr<GameEngineMesh> mesh_;                  //
//
//    std::shared_ptr<GameEngineInputLayout> inputLayout_;    //
//
//    std::shared_ptr<GameEngineMaterial> material_;    //���̴����ҽ����� ����Ÿ�ٿ� �׸� ���׸���.
//
//    D3D11_PRIMITIVE_TOPOLOGY topology_;     //
//
//    GameEngineShaderResourceHelper shaderResourceHelper_;   //���̴����ҽ����� ���� ���̴����ҽ� ����.
//    //������ ����: �������ָ��� ������ ���̴����ҽ����۸� ������ �ϱ� ���ؼ�.
//};

class GameEngineInstancingRenderer
{
	//�� Ŭ������ ���� ����:
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

