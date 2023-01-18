#pragma once
#include "GameEngineMaterial.h"
#include "GameEngineShaderResourceHelper.h"
#include "GameEngineMesh.h"
#include "GlobalHeader.h"

class GameEngineInstancingBuffer;
class GameEngineInstancingRenderer
{

    class InstancingUnit
    {
        //인스턴스별 렌더링 정보 저장용 유닛.

        friend GameEngineInstancingRenderer;


        InstancingUnit(const std::multiset<std::string>& _structuredBufferSetterNames);
    
        void Link(const std::string_view& _name, const void* _data);

    public:
        void SetWorldScale(const float4& _worldScaleVector);
        void SetWorldRotation(const float4& _worldRotationVector);
        void SetWorldPosition(const float4& _worldPositionVector);

        void SetColorTextureIndex(unsigned int _colortextureIndex);
        void SetNormalMapTextureIndex(unsigned int _normalMapTextureIndex);

        //이 인스턴싱 유닛이 그리는 텍스처를 좌우반전하는 함수.
        void SwitchLeftToRight();

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

        TransformData transformData_;

        AtlasData atlasData_;

        std::multimap<std::string, const void*> data_;  //키값으로 쓰인 문자열과 같은 이름을 가진 구조화버퍼에 넣어 셰이더로 전달할 데이터.

        unsigned int colorTextureIndex_; //인스턴스별로 사용할 컬러텍스처의 인덱스.

        unsigned int normalMapTextureIndex_; //인스턴스별로 사용할 노말맵텍스처의 인덱스.
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
    //초기화.
    void Initialize(
        size_t _instancingUnitCount,            //인스턴싱 유닛 수.
        const std::string_view& _meshName,      //사용할 메쉬 이름.
        const std::string_view& _materialName,  //사용할 마테리얼 이름.
        bool _isShadowRendering = false         //true: 그림자의 깊이값을 렌더타겟뷰에 저장한다.
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
    //포워드 렌더링.
    void Render(float _deltaTime, const float4x4& _viewMatrix, const float4x4& _projectionMatrix);

    //디퍼드 렌더링.
    void DeferredRender(float _deltaTime, const float4x4& _viewMatrix, const float4x4& _projectionMatrix);

    //디퍼드 그림자 렌더링.
    void RenderShadow(float _deltaTime, const float4x4& _viewMatrix, const float4x4& _projectionMatrix);

private:
    bool isShadowRendering_;                        //true: 그림자의 깊이값을 렌더타겟에 저장한다.

    size_t instancingUnitCount_;                    //전체 인스턴싱유닛 개수.

    std::vector<InstancingUnit> allInstancingUnits_;   //모든 인스턴싱유닛들이 저장된 벡터.

    GameEngineMesh* mesh_;                          //메쉬.

    GameEngineInputLayout* inputLayout_;            //인풋 레이아웃.

    GameEngineMaterial* material_;                  //셰이더리소스들을 렌더타겟에 그릴 마테리얼.

    D3D11_PRIMITIVE_TOPOLOGY topology_;             //토폴로지.

    //각각의 인스턴스들이 가지고 있는 정보들을 모아서 정점 정보들과 함께 정점셰이더로 전달하는 버퍼.
    GameEngineInstancingBuffer* instancingBuffer_;  

    //컬러텍스처 인덱스와 노말맵텍스처 인덱스 등의 인스턴스별 정보들을 모아 저장해서 인스턴싱버퍼로 전달하는 임시저장용 버퍼.
    std::vector<char> instanceDataBuffer_;  

    size_t instanceDataSize_; //인스턴스별로 가지고 있는 인풋 레이아웃들의 총합 크기.

    GameEngineShaderResourceHelper shaderResourceHelper_;   //이 렌더러가 쓸 셰이더리소스헬퍼.

    std::multiset<std::string> structuredBufferSetterNames_;     //셰이더리소스헬퍼가 가진 인스턴스렌더링용 구조화버퍼 세터들의 이름 모음. 
    //멀티셋이 아니라 같은 원소를 겹칠 수 없는 일반 셋이면 여러 셰이더가 같은 이름의 셰이더 리소스를 사용할 수 없다.
    //반드시 전부 대문자로 구성할 것.

};

