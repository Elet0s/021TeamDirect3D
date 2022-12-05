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
        //����� ���� ��������� ���Ե� Ʈ�����������͸� ���� ��!
        void SetTransformData(const TransformData& _transformData);

    public:
        //Ʈ�����������ʹ� ���⿡ ���� �� ��!
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

        std::shared_ptr<GameEngineRenderUnit> renderUnit_;	//��������.

        TransformData transformData_;

        RenderOption renderOptionInst_;

        std::map<std::string, const void*> data_;  //Ű������ ���� �̸��� ���� ����ȭ���ۿ� �־� GPU�� ������ ������.
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

    size_t instancingUnitCount_;    //��ü �ν��Ͻ����� ����.

    std::vector<InstancingUnit> instancingUnits_;   //�������� + �ν��Ͻ̵����� �迭.

    std::shared_ptr<GameEngineInstancingBuffer> instancingBuffer_;  //


    std::vector<char> rowIndexBuffer_;  //�ο��ε��� ����, ���޿� ����.



    GameEngineShaderResourceHelper shaderResourceHelper_;   //�� �������� �� ���̴����ҽ�����.




    std::set<std::string> structuredBufferSetterNames_;    //���̴����ҽ����۰� ���� �ν��Ͻ��������� ����ȭ���� ���͵��� �̸� ����. 
    //�ݵ�� ���� �빮�ڷ� ������ ��.

};

