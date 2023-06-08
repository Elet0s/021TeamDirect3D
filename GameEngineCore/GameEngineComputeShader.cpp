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
        MsgBoxAssert("컴퓨트 셰이더가 없습니다.");
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
        this->binaryCode_->GetBufferPointer(),  //컴파일된 바이너리코드.
        this->binaryCode_->GetBufferSize(),     //컴파일된 바이너리코드 크기.
        NULL,                                   //??
        &this->computeShader_                  //컴퓨트 셰이더 포인터.
    ))
    {
        MsgBoxAssert("컴퓨트 셰이더 생성 실패.");
        return;
    }
}
