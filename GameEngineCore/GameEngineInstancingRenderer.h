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
        friend GameEngineInstancingRenderer;


        InstancingUnit(const std::set<std::string>& _structuredBufferSetterNames);
    
        void Link(const std::string_view& _name, const void* _data);

    public:
        void SetWorldScale(const float4& _worldScaleVector);
        void SetWorldRotation(const float4& _worldRotationVector);
        void SetWorldPosition(const float4& _worldPositionVector);

        void SetColorTextureIndex(unsigned int _colortextureIndex);
        void SetNormalMapTextureIndex(unsigned int _normalMapTextureIndex);

        //�� �ν��Ͻ� ������ �׸��� �ؽ�ó�� �¿�����ϴ� �Լ�.
        void SwitchLeftToRight();

    public:
        //Ʈ������������, ��Ʋ�󽺵����ʹ� ���⿡ ���� �� ��!
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

        std::map<std::string, const void*> data_;  //Ű������ ���� ���ڿ��� ���� �̸��� ���� ����ȭ���ۿ� �־� ���̴��� ������ ������.

        unsigned int colorTextureIndex_; //�ν��Ͻ����� ����� �÷��ؽ�ó �迭�� �ε���.

        unsigned int normalMapTextureIndex_; //�ν��Ͻ����� ����� �÷��ؽ�ó �迭�� �ε���.
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
    //�ʱ�ȭ.
    void Initialize(
        size_t _instancingUnitCount,            //�ν��Ͻ� ���� ��.
        const std::string_view& _meshName,      //����� �޽� �̸�.
        const std::string_view& _materialName  //����� ���׸��� �̸�.
    );

    //�� �������� ��� ���彺������ �ѹ��� �����ϴ� �Լ�.
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
    void DeferredRender(float _deltaTime, const float4x4& _viewMatrix, const float4x4& _projectionMatrix);

private:

    size_t instancingUnitCount_;    //��ü �ν��Ͻ����� ����.

    std::vector<InstancingUnit> allInstancingUnits_;   //�ν��Ͻ̵����� ����.

    std::shared_ptr<GameEngineMesh> mesh_;                  //�޽�.

    std::shared_ptr<GameEngineInputLayout> inputLayout_;    //��ǲ ���̾ƿ�.

    std::shared_ptr<GameEngineMaterial> material_;    //���̴����ҽ����� ����Ÿ�ٿ� �׸� ���׸���.

    D3D11_PRIMITIVE_TOPOLOGY topology_;                     //��������.

    std::shared_ptr<GameEngineInstancingBuffer> instancingBuffer_;  //�ν��Ͻ����� �޶����� �������� ���̴��� �����ϴ� ����

    std::vector<char> instanceIndexBuffer_;  //�ν��Ͻ� �ε����� �ؽ�ó �ε����� �����ϴ� ����.

    GameEngineShaderResourceHelper shaderResourceHelper_;   //�� �������� �� ���̴����ҽ�����.

    std::set<std::string> structuredBufferSetterNames_;    //���̴����ҽ����۰� ���� �ν��Ͻ��������� ����ȭ���� ���͵��� �̸� ����. 
    //�ݵ�� ���� �빮�ڷ� ������ ��.

};

