#include "PreCompile.h"
#include "GameEnginePixelShader.h"
#include "GameEngineDevice.h"

GameEnginePixelShader::GameEnginePixelShader() : pixelShader_(nullptr)
{
    shaderType_ = ShaderType::PixelShader;
}

GameEnginePixelShader::~GameEnginePixelShader()
{
    if (nullptr != pixelShader_)
    {
        pixelShader_->Release();
        pixelShader_ = nullptr;
    }
}

void GameEnginePixelShader::Setting()
{
    if (nullptr == pixelShader_)
    {
        MsgBoxAssert("�ȼ����̴��� �����ϴ�.");
        return;
    }

    //�ι�° ���ڴ� #include�� #define�� hlsl���� ����� ����� �������� ��ü�� �־��ټ� �ִ�.
    GameEngineDevice::GetContext()->PSSetShader(//���������ο� �ȼ����̴��� �����ϴ� �Լ�.
        pixelShader_,                      //�ȼ����̴� ������.
        nullptr,                           //Ŭ���� �ν��Ͻ� �������̽� �迭 �ּҰ�. ������ NULL.
        0                                  //����� Ŭ���� �ν��Ͻ� �������̽� �迭�� �ε���.
    );
}

std::shared_ptr<GameEnginePixelShader> GameEnginePixelShader::Load(
    const std::string_view& _path,
    const std::string_view& _entryPoint,
    UINT _versionHigh /*= 5*/,
    UINT _versionLow /*= 0*/
)
{
    return Load(_path, GameEnginePath::GetFileName(_path), _entryPoint, _versionHigh, _versionLow);
}

std::shared_ptr<GameEnginePixelShader> GameEnginePixelShader::Load(
    const std::string_view& _path,
    const std::string_view& _name,
    const std::string_view& _entryPoint,
    UINT _versionHigh /*= 5*/,
    UINT _versionLow /*= 0*/
)
{
    std::shared_ptr<GameEnginePixelShader> newRes = CreateNamedRes(_name);
    newRes->CreateVersion("ps", _versionHigh, _versionLow);
    newRes->SetEntrtyPoint(_entryPoint);
    newRes->CompileHLSLCode(_path);
    newRes->CreatePixelShader();
    newRes->ShaderResCheck(newRes->GetName());
    return newRes;
}

void GameEnginePixelShader::CreatePixelShader()
{
    if (S_OK != GameEngineDevice::GetDevice()->CreatePixelShader(   //�ȼ����̴� ���� �Լ�.
        binaryCode_->GetBufferPointer(), //�����ϵ� ���̳ʸ��ڵ�.
        binaryCode_->GetBufferSize(),    //�����ϵ� ���̳ʸ��ڵ� ũ��.
        NULL,                               //??
        &pixelShader_                       //�ȼ����̴� ������.
    ))
    {
        MsgBoxAssert("�ȼ����̴� ���� ����.");
        return;
    }
}

