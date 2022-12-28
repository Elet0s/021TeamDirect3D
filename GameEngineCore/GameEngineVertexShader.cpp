#include "PreCompile.h"
#include "GameEngineVertexShader.h"
#include "GameEngineDevice.h"

GameEngineVertexShader::GameEngineVertexShader()
    : vertexShader_(nullptr),
    inst_VertexShader_(nullptr)

{
    shaderType_ = ShaderType::VertexShader;
}

GameEngineVertexShader::~GameEngineVertexShader()
{
    if (nullptr != vertexShader_)
    {
        vertexShader_->Release();
        vertexShader_ = nullptr;
    }

    //if (nullptr != instancingVertexShader_)
    //{
    //    delete instancingVertexShader_;
    //    instancingVertexShader_ = nullptr;
    //}   
}

void GameEngineVertexShader::Setting()
{
    if (nullptr == vertexShader_)
    {
        MsgBoxAssert("���ؽ� ���̴��� �����ϴ�.");
        return;
    }

    //�ι�° ���ڴ� #include�� #define�� hlsl���� ����� ����� �������� ��ü�� �־��ټ� �ִ�.
    GameEngineDevice::GetContext()->VSSetShader(//���������ο� ���ؽ����̴��� �����ϴ� �Լ�.
        vertexShader_,                     //���ؽ� ���̴� ������.
        nullptr,                           //Ŭ���� �ν��Ͻ� �������̽� �迭 �ּҰ�. ������ NULL.
        0                                  //����� Ŭ���� �ν��Ͻ� �������̽� �迭�� �ε���.
    );
}

std::shared_ptr<GameEngineVertexShader> GameEngineVertexShader::Load(
    const std::string_view& _path,
    const std::string_view& _entryPoint,
    UINT _versionHigh /*= 5*/,
    UINT _versionLow /*= 0*/
)
{
    return Load(_path, GameEnginePath::GetFileName(_path), _entryPoint, _versionHigh, _versionLow);
}

std::shared_ptr<GameEngineVertexShader> GameEngineVertexShader::Load(
    const std::string_view& _path,
    const std::string_view& _name,
    const std::string_view& _entryPoint,
    UINT _versionHigh /*= 5*/,
    UINT _versionLow /*= 0*/
)
{
    std::shared_ptr<GameEngineVertexShader> newRes = CreateNamedRes(_name);
    newRes->CreateVersion("vs", _versionHigh, _versionLow);
    newRes->SetEntrtyPoint(_entryPoint);
    newRes->CompileHLSLCode(_path);
    newRes->CreateVertexShader();
    newRes->ShaderResCheck(newRes->GetName());
    return newRes;
}

void GameEngineVertexShader::InstancingVertexShaderCompile(
    const std::string_view& _path,
    const std::string_view& _entryPoint,
    UINT _versionHigh /*= 5*/,
    UINT _versionLow /*= 0*/
)
{
    inst_VertexShader_ = std::make_shared<GameEngineVertexShader>(); //GameEngineRes�� ��ϵ��� �ʴ� �� ����.
    inst_VertexShader_->SetName(_entryPoint);
    inst_VertexShader_->CreateVersion("vs", _versionHigh, _versionLow);
    inst_VertexShader_->SetEntrtyPoint(_entryPoint);
    inst_VertexShader_->CompileHLSLCode(_path);
    inst_VertexShader_->CreateInstancingVertexShader();
    inst_VertexShader_->ShaderResCheck(inst_VertexShader_->GetName());
}

void GameEngineVertexShader::CreateVertexShader()
{
    if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader(  //���ؽ����̴� ���� �Լ�.
        binaryCode_->GetBufferPointer(), //�����ϵ� ���̳ʸ� �ڵ�.
        binaryCode_->GetBufferSize(),    //�����ϵ� ���̳ʸ��ڵ� ũ��.
        NULL,                               //??
        &vertexShader_                      //���ؽ����̴� ������.
    ))
    {
        MsgBoxAssert("���ؽ� ���̴� ���� ����.");
        return;
    }
}


void GameEngineVertexShader::CreateInstancingVertexShader()
{
    if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader(  //���ؽ����̴� ���� �Լ�.
        this->binaryCode_->GetBufferPointer(), //�����ϵ� ���̳ʸ� �ڵ�.
        this->binaryCode_->GetBufferSize(),    //�����ϵ� ���̳ʸ��ڵ� ũ��.
        NULL,                                   //??
        &this->vertexShader_                   //�ν��Ͻ� ���ؽ����̴� ������.
    ))
    {
        MsgBoxAssert("�ν��Ͻ� ���ؽ����̴� ���� ����.");
        return;
    }
}
