#include "PreCompile.h"
#include "GameEngineGeometryShader.h"
#include "GameEngineDevice.h"

GameEngineGeometryShader::GameEngineGeometryShader(): geometryShader_(nullptr)
{
    shaderType_ = ShaderType::GeometryShader;
}

GameEngineGeometryShader::~GameEngineGeometryShader()
{
    if (nullptr != geometryShader_)
    {
        geometryShader_->Release();
        geometryShader_ = nullptr;
    }
}

void GameEngineGeometryShader::Setting()
{
    if (nullptr == geometryShader_)
    {
        MsgBoxAssert("������Ʈ�� ���̴��� �����ϴ�.");
        return;
    }

    //�ι�° ���ڴ� #include�� #define�� hlsl���� ����� ����� �������� ��ü�� �־��ټ� �ִ�.
    GameEngineDevice::GetContext()->GSSetShader(//���������ο� ������Ʈ�� ���̴��� �����ϴ� �Լ�.
        geometryShader_,                    //������Ʈ�� ���̴� ������.
        nullptr,                            //Ŭ���� �ν��Ͻ� �������̽� �迭 �ּҰ�. ������ NULL.
        0                                   //����� Ŭ���� �ν��Ͻ� �������̽� �迭�� �ε���.
    );
}

std::shared_ptr<GameEngineGeometryShader> GameEngineGeometryShader::Load(
    const std::string_view& _path,
    const std::string_view& _entryPoint,
    UINT _versionHigh, /*= 5*/
    UINT _versionLow /*= 0*/
)
{
	return Load(_path, GameEnginePath::GetFileName(_path), _entryPoint, _versionHigh, _versionLow);
}

std::shared_ptr<GameEngineGeometryShader> GameEngineGeometryShader::Load(
    const std::string_view& _path,
    const std::string_view& _name,
    const std::string_view& _entryPoint,
    UINT _versionHigh, /*= 5*/
    UINT _versionLow /*= 0*/
)
{
	std::shared_ptr<GameEngineGeometryShader> newRes = CreateNamedRes(_name);
    newRes->CreateVersion("gs", _versionHigh, _versionLow);
    newRes->SetEntrtyPoint(_entryPoint);
    newRes->CompileHLSLCode(_path);
    newRes->CreateGeometryShader();
    newRes->ShaderResCheck(newRes->GetName());
    return newRes;
}

void GameEngineGeometryShader::CreateGeometryShader()
{
    if (S_OK != GameEngineDevice::GetDevice()->CreateGeometryShader(
        this->binaryCode_->GetBufferPointer(),  //�����ϵ� ���̳ʸ��ڵ�.
        this->binaryCode_->GetBufferSize(),     //�����ϵ� ���̳ʸ��ڵ� ũ��.
        NULL,                                   //??
        &this->geometryShader_                  //�ȼ����̴� ������.
    ))
    {
        MsgBoxAssert("������Ʈ�� ���̴� ���� ����.");
        return;
    }
}