#include "PreCompile.h"
#include "GameEngineInputLayout.h"
#include "GameEngineDevice.h"
#include "GameEngineVertexes.h"
#include "GameEngineVertexShader.h"

GameEngineInputLayout::GameEngineInputLayout() : inputLayout_(nullptr)
{
}

GameEngineInputLayout::~GameEngineInputLayout()
{
    if (nullptr != inputLayout_)
    {
        inputLayout_->Release();
        inputLayout_ = nullptr;
    }
}

void GameEngineInputLayout::CreateInputLayout(
    const GameEngineInputLayoutDesc& _desc,
    std::shared_ptr<GameEngineVertexShader> _vertexShader
)
{
    if (S_OK != GameEngineDevice::GetDevice()->CreateInputLayout(	//��ǲ���̾ƿ� ���� �Լ�.
        &_desc.descs_[0],									//��ǲ���̾ƿ� ������ �ʿ��� D3D11_INPUT_ELEMENT_DESC������ �迭 ù��° ������ ������.
        static_cast<UINT>(_desc.descs_.size()),				//D3D11_INPUT_ELEMENT_DESC������ �迭�� ũ��.
        _vertexShader->binaryCode_->GetBufferPointer(),	    //�����ϵ� ���̴� ���̳ʸ��ڵ�
        _vertexShader->binaryCode_->GetBufferSize(),		//�����ϵ� ���̴� ���̳ʸ��ڵ� ũ��.
        &inputLayout_                                       //������ ��ǲ���̾ƿ��� ���� ID3D11InputLayout������.
    ))
    {
        MsgBoxAssert("��ǲ���̾ƿ� ���� ����.");
        return;
    }
}

void GameEngineInputLayout::Setting()
{
    if (nullptr == inputLayout_)
    {
        MsgBoxAssert("��ǲ���̾ƿ��� �����ϴ�.");
        return;
    }

    GameEngineDevice::GetContext()->IASetInputLayout(inputLayout_);
}

std::shared_ptr<GameEngineInputLayout> GameEngineInputLayout::Create(
    const GameEngineInputLayoutDesc& _desc,
    std::shared_ptr<GameEngineVertexShader> _vertexShader
)
{
    std::shared_ptr<GameEngineInputLayout> newRes = CreateUnnamedRes();
    newRes->CreateInputLayout(_desc, _vertexShader);
    return newRes;
}
