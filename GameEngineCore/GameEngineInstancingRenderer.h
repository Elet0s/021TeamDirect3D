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
        //�ν��Ͻ��� ������ ���� ����� ����.

        friend GameEngineInstancingRenderer;


        InstancingUnit(const std::multiset<std::string>& _structuredBufferSetterNames, size_t _unitIndexs);
    
        void Link(const std::string_view& _structuredBufferName, const void* _data);

    public:
        void SetWorldScale(const float4& _worldScaleVector);
        void SetWorldRotation(const float4& _worldRotationVector);
        void SetWorldPosition(const float4& _worldPositionVector);

        void SetColorTextureIndex(unsigned int _colorTextureIndex);
        void SetNormalMapTextureIndex(unsigned int _normalMapTextureIndex);

        //�� �ν��Ͻ� ������ �׸��� �ؽ�ó�� �¿�����ϴ� �Լ�.
        void SwitchLeftToRight();

    public:
        //Ʈ������������, ��Ʋ�󽺵����ʹ� ���⿡ ���� �� ��!
        template<typename ValueType>
        void Link(const std::string_view& _structuredBufferName, ValueType& _data)
        {
            Link(_structuredBufferName, reinterpret_cast<const void*>(&_data));
        }

        AtlasData& GetAtlasData()
        {
            return atlasData_;
        }

        const float4& GetWorldPosition() const
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
        void UpdateTransformData(
            const float4x4& _viewMatrix,
            const float4x4& _projectionMatrix,
            char* _transformDataPtr
        );
        void UpdateAtlasData(char* _atlasDataPtr);
        void UpdateLinkedData(
            std::multimap<std::string, GameEngineStructuredBufferSetter>& _structuredBufferSetters
        );
        void UpdateTextureIndex(char* _instanceDataBufferPtr1, char* _instanceDataBufferPtr2);

    private:

        const size_t unitIndex_;

        //�޽��� �׸� ��ġ, ũ�� ���� ������ ��� Ʈ������������.
        TransformData transformData_;

        //�޽� �ȿ� �׷��� �ؽ�ó UV��, �Ǻ� ���� ����.
        AtlasData atlasData_;

        //Ű������ ���� ���ڿ��� ���� �̸��� ���� ����ȭ���ۿ� �־� ���̴��� ������ ������.
        std::multimap<std::string, const void*> linkedData_;  

        //�ν��Ͻ����� ����� �÷��ؽ�ó�� �ε���.
        unsigned int colorTextureIndex_; 

        //�ν��Ͻ����� ����� �븻���ؽ�ó�� �ε���.
        unsigned int normalMapTextureIndex_; 
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
        const std::string_view& _materialName,  //����� ���׸��� �̸�.
        bool _isShadowRendering = false         //true: �׸����� ���̰��� ����Ÿ�ٺ信 �����Ѵ�.
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
    //������ ������.
    void Render(float _deltaTime, const float4x4& _viewMatrix, const float4x4& _projectionMatrix);

    //���۵� ������.
    void DeferredRender(float _deltaTime, const float4x4& _viewMatrix, const float4x4& _projectionMatrix);

    //���۵� �׸��� ������.
    void RenderShadow(float _deltaTime, const float4x4& _viewMatrix, const float4x4& _projectionMatrix);

private:
    bool isShadowRendering_;                        //true: ����Ÿ�ٿ� �Ϲ����� �ؽ�ó �÷����� �ƴ϶� �׸����� ���̰��� �����Ѵ�.

    size_t instancingUnitCount_;                    //��ü �ν��Ͻ����� ����.

    std::vector<InstancingUnit> allInstancingUnits_;   //��� �ν��Ͻ����ֵ��� ����� ����.
    //�ν��Ͻ� ���ֵ��� �ַ� �����ϰ� �� �������� float�� unsigned int�� ��κ��̶� ������� ���� ȿ�� ���Һ��� 
    // ĳ�� ������ ������� ���� ȿ�� ������ �� ũ�ٰ� �Ǵ��ؼ� ������ ������.
    
    GameEngineMesh* mesh_;                          

    GameEngineInputLayout* inputLayout_;            

    GameEngineMaterial* material_;                  

    D3D11_PRIMITIVE_TOPOLOGY topology_;             

    //������ �ν��Ͻ����� ������ �ִ� �������� ��Ƽ� ���� ������� �Բ� �������̴��� �����ϴ� ����.
    GameEngineInstancingBuffer* instancingBuffer_;  

    //�÷��ؽ�ó �ε����� �븻���ؽ�ó �ε��� ���� �ν��Ͻ��� �������� ��� �����ؼ� �ν��Ͻ̹��۷� �����ϴ� �߰������ �����̳�.
    std::vector<char> instanceDataVector_;  

    size_t instanceDataSize_; //�ν��Ͻ����� ������ �ִ� ��ǲ ���̾ƿ����� ���� ũ��.

    GameEngineShaderResourceHelper shaderResourceHelper_;   //�� �������� �� ���̴����ҽ�����.

    //���̴����ҽ����۰� ���� �ν��Ͻ��������� ����ȭ���� ���͵��� �̸� ����. 
    std::multiset<std::string> structuredBufferSetterNames_;     
    //��Ƽ���� �ƴ϶� ���� ���Ҹ� ��ĥ �� ���� �Ϲ� ���̸� ���� ���̴��� ���� �̸��� ���̴� ���ҽ��� ����� �� ����.
    //�ݵ�� ���� �빮�ڷ� ������ ��.

};

