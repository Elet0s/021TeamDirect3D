#include "PreCompile.h"
#include "GameEngineComputeShader.h"
#include "GameEngineDevice.h"

GameEngineComputeShader::GameEngineComputeShader(): computeShader_(nullptr)
{
    shaderType_ = ShaderType::ComputeShader;
}

GameEngineComputeShader::~GameEngineComputeShader()
{
    if (nullptr != computeShader_)
    {
        computeShader_->Release();
        computeShader_ = nullptr;
    }
}

void GameEngineComputeShader::Set()
{
    if (nullptr == computeShader_)
    {
        MsgBoxAssert("��ǻƮ ���̴��� �����ϴ�.");
        return;
    }

    GameEngineDevice::GetDC()->CSSetShader(
        computeShader_,
        nullptr,
        0
    );
}

GameEngineComputeShader* GameEngineComputeShader::Load(const std::string_view& _path, const std::string_view& _entryPoint, UINT _versionHigh, UINT _versionLow)
{
    return Load(_path, GameEnginePath::GetFileName(_path), _entryPoint, _versionHigh, _versionLow);
}

GameEngineComputeShader* GameEngineComputeShader::Load(const std::string_view& _path, const std::string_view& _name, const std::string_view& _entryPoint, UINT _versionHigh, UINT _versionLow)
{
    GameEngineComputeShader* newRes = CreateNamedRes(_name);
    newRes->CreateVersion("cs", _versionHigh, _versionLow);
    newRes->SetEntrtyPoint(_entryPoint);
    newRes->CompileHLSLCode(_path);
    newRes->CreateComputeShader();
    newRes->ShaderResCheck(newRes->GetName());
    return newRes;
}

void GameEngineComputeShader::CreateComputeShader()
{
    if (S_OK != GameEngineDevice::GetDevice()->CreateComputeShader(
        this->binaryCode_->GetBufferPointer(),  //�����ϵ� ���̳ʸ��ڵ�.
        this->binaryCode_->GetBufferSize(),     //�����ϵ� ���̳ʸ��ڵ� ũ��.
        NULL,                                   //??
        &this->computeShader_                  //��ǻƮ ���̴� ������.
    ))
    {
        MsgBoxAssert("��ǻƮ ���̴� ���� ����.");
        return;
    }
}
