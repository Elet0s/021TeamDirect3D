#pragma once
#include "GameEngineMaterial.h"
#include "GameEngineShaderResourceHelper.h"
#include "GameEngineMesh.h"
#include "GameEngineRenderer.h"

class GameEngineMaterial;
class GameEngineInstancingBuffer;
class GameEngineInstancingRenderer
{

    class InstancingUnit
    {
        friend GameEngineInstancingRenderer;


        InstancingUnit(
            const std::set<std::string>& _sreucturedBufferSetterNames,
            const std::string_view& _meshName,
            const std::string_view& _materialName
        );
    
        void Link(const std::string_view& _name, const void* _data);

    public:
        //계산이 끝난 월드행렬이 포함된 트랜스폼데이터만 넣을 것!
        void SetTransformData(const TransformData& _transformData);

    public:
        //트랜스폼데이터는 여기에 넣지 말 것!
        template<typename ValueType>
        void Link(const std::string_view& _name, ValueType& _data)
        {
            Link(_name, reinterpret_cast<const void*>(&_data));
        }

        RenderOption& GetRenderOption()
        {
            return this->renderOptionInst_;
        }

    private:

        std::shared_ptr<GameEngineRenderUnit> renderUnit_;	//렌더유닛.

        TransformData transformData_;

        RenderOption renderOptionInst_;

        std::map<std::string, const void*> data_;  //키값으로 쓰인 이름을 가진 구조화버퍼에 넣어 GPU로 전달할 데이터.
    };



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
    void Initialize(
        size_t _renderUnitCount,
        const std::string_view& _meshName = "Rect",
        const std::string_view& _materialName = "Test"
    );

    void Render(float _deltaTime, const float4x4& _viewMatrix, const float4x4& _projectionMatrix);


public:
    InstancingUnit& GetInstancingUnit(int _index)
    {
        return instancingUnits_[_index];
    }

    void SetTexture(
        const std::string_view& _textureSetterName,
        const std::string_view& _textureName
    )
    {
        shaderResourceHelper_.SetTexture(_textureSetterName, _textureName);
    }

    void SetSampler(
        const std::string_view& _samplerSetterName,
        const std::string_view& _samplerName
    )
    {
        shaderResourceHelper_.SetSampler(_samplerSetterName, _samplerName);
    }

    void SetTexture2DArray(
        const std::string_view& _textureArraySetterName,
        const std::string_view& _textureArrayName
    )
    {
        shaderResourceHelper_.SetTexture2DArray(_textureArraySetterName, _textureArrayName);
    }

private:

    size_t instancingUnitCount_;    //전체 인스턴싱유닛 개수.

    std::vector<InstancingUnit> instancingUnits_;   //렌더유닛 + 인스턴싱데이터 배열.

    std::shared_ptr<GameEngineInstancingBuffer> instancingBuffer_;  //


    std::vector<char> rowIndexBuffer_;  //로우인덱스 저장, 전달용 버퍼.



    GameEngineShaderResourceHelper shaderResourceHelper_;   //이 렌더러가 쓸 셰이더리소스헬퍼.




    std::set<std::string> structuredBufferSetterNames_;    //셰이더리소스헬퍼가 가진 인스턴스렌더링용 구조화버퍼 세터들의 이름 모음. 
    //반드시 전부 대문자로 구성할 것.

};

