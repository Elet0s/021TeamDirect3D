#pragma once
#include "GameEngineMaterial.h"
#include "GameEngineShaderResourceHelper.h"
#include "GameEngineMesh.h"
#include "GameEngineRenderer.h"
#include "GameEngineTextureRenderer.h"

class GameEngineMaterial;
class GameEngineInstancingBuffer;
class GameEngineInstancingRenderer
{

    class InstancingUnit
    {
        friend GameEngineInstancingRenderer;


        InstancingUnit(
            const std::set<std::string>& _structuredBufferSetterNames
            //const std::string_view& _meshName,
            //const std::string_view& _materialName
        );
    
        void Link(const std::string_view& _name, const void* _data);

    public:
        void SetWorldScale(const float4& _worldScaleVector);
        void SetWorldRotation(const float4& _worldRotationVector);
        void SetWorldPosition(const float4& _worldPositionVector);

        void SetTextureIndex(unsigned int _textureIndex);

    public:
        //트랜스폼데이터, 아틀라스데이터는 여기에 넣지 말 것!
        template<typename ValueType>
        void Link(const std::string_view& _name, ValueType& _data)
        {
            Link(_name, reinterpret_cast<const void*>(&_data));
        }

        AtlasData& GetAtlasData()
        {
            return atlasData_;
        }

        const float4& GetWorldPosition()
        {
            return this->transformData_.worldPositionVector_;
        }

        void SetWorldScale(float _worldScaleX, float _worldScaleY, float _worldScaleZ)
        {
            SetWorldScale(float4(_worldScaleX, _worldScaleY, _worldScaleZ));
        }

        void SetWorldScale(int _worldScaleX, int _worldScaleY, int _worldScaleZ)
        {
            SetWorldScale(float4(_worldScaleX, _worldScaleY, _worldScaleZ));
        }

        void SetWorldRotation(float _worldRotationX, float _worldRotationY, float _worldRotationZ)
        {
            SetWorldRotation(float4(_worldRotationX, _worldRotationY, _worldRotationZ));
        }

        void SetWorldRotation(int _worldRotationX, int _worldRotationY, int _worldRotationZ)
        {
            SetWorldRotation(float4(_worldRotationX, _worldRotationY, _worldRotationZ));
        }

        void SetWorldPosition(float _worldPositionX, float _worldPositionY, float _worldPositionZ)
        {
            SetWorldPosition(float4(_worldPositionX, _worldPositionY, _worldPositionZ));
        }

        void SetWorldPosition(int _worldPositionX, int _worldPositionY, int _worldPositionZ)
        {
            SetWorldPosition(float4(_worldPositionX, _worldPositionY, _worldPositionZ));
        }

    private:
        void CalWorldWorldMatrix();

    private:

        //std::shared_ptr<GameEngineRenderUnit> renderUnit_;	//렌더유닛.

        TransformData transformData_;

        AtlasData atlasData_;

        std::map<std::string, const void*> data_;  //키값으로 쓰인 문자열과 같은 이름을 가진 구조화버퍼에 넣어 셰이더로 전달할 데이터.

        unsigned int textureIndex_;
    };


    friend class GameEngineCamera;

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
        size_t _instancingUnitCount,
        const std::string_view& _meshName,
        const std::string_view& _materialName
    );

    //이 렌더러의 모든 월드스케일을 한번에 세팅하는 함수.
    void SetAllUnitsWorldScale(const float4& _worldScaleVector);

public:
    InstancingUnit& GetInstancingUnit(int _index)
    {
        return allInstancingUnits_[_index];
    }

    InstancingUnit& GetInstancingUnit(size_t _index)
    {
        return allInstancingUnits_[_index];
    }

    size_t GetUnitCount()
    {
        return allInstancingUnits_.size();
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

    void SetAllUnitsWorldScale(float _worldScaleX, float _worldScaleY, float _worldScaleZ)
    {
        SetAllUnitsWorldScale(float4(_worldScaleX, _worldScaleY, _worldScaleZ));
    }

    void SetAllUnitsWorldScale(int _worldScaleX, int _worldScaleY, int _worldScaleZ)
    {
        SetAllUnitsWorldScale(float4(_worldScaleX, _worldScaleY, _worldScaleZ));
    }
    
private:
    void Render(float _deltaTime, const float4x4& _viewMatrix, const float4x4& _projectionMatrix);

private:

    size_t instancingUnitCount_;    //전체 인스턴싱유닛 개수.

    std::vector<InstancingUnit> allInstancingUnits_;   //인스턴싱데이터 벡터.





    std::shared_ptr<GameEngineMesh> mesh_;                  //

    std::shared_ptr<GameEngineInputLayout> inputLayout_;    //

    std::shared_ptr<GameEngineMaterial> material_;    //셰이더리소스들을 렌더타겟에 그릴 마테리얼.

    D3D11_PRIMITIVE_TOPOLOGY topology_;                     //





    std::shared_ptr<GameEngineInstancingBuffer> instancingBuffer_;  //인스턴스별로 달라지는 정보들을 셰이더로 전달하는 버퍼

    std::vector<char> instanceIndexBuffer_;  //인스턴스 인덱스와 텍스처인덱스를 저장하는 버퍼.

    GameEngineShaderResourceHelper shaderResourceHelper_;   //이 렌더러가 쓸 셰이더리소스헬퍼.

    std::set<std::string> structuredBufferSetterNames_;    //셰이더리소스헬퍼가 가진 인스턴스렌더링용 구조화버퍼 세터들의 이름 모음. 
    //반드시 전부 대문자로 구성할 것.

};

