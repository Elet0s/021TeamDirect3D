#include "PreCompile.h"
#include "GameEngineVertexShader.h"
#include "GameEngineDevice.h"

GameEngineVertexShader::GameEngineVertexShader()
    : vertexShader_(nullptr),
    instancingVertexShader_(nullptr)

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
    
    if (nullptr != instancingVertexShader_)
    {
        delete instancingVertexShader_;
        instancingVertexShader_ = nullptr;
    }   
}

void GameEngineVertexShader::Setting()
{
    if (nullptr == vertexShader_)
    {
        MsgBoxAssert("버텍스셰이더가 없습니다.");
        return;
    }

    //두번째 인자는 #include나 #define등 hlsl에서 사용할 헤더나 디파인의 객체를 넣어줄수 있다.
    GameEngineDevice::GetContext()->VSSetShader(//파이프라인에 버텍스셰이더를 세팅하는 함수.
        vertexShader_,                     //버텍스 셰이더 포인터.
        nullptr,                           //클래스 인스턴스 인터페이스 배열 주소값. 없으면 NULL.
        0                                  //사용할 클래스 인스턴스 인터페이스 배열의 인덱스.
    );
}

GameEngineVertexShader* GameEngineVertexShader::Load(
    const std::string& _path,
    const std::string& _entryPoint,
    UINT _versionHigh /*= 5*/,
    UINT _versionLow /*= 0*/
)
{
    return Load(_path, GameEnginePath::GetFileName(_path), _entryPoint, _versionHigh, _versionLow);
}

GameEngineVertexShader* GameEngineVertexShader::Load(
    const std::string& _path,
    const std::string& _name,
    const std::string& _entryPoint,
    UINT _versionHigh /*= 5*/,
    UINT _versionLow /*= 0*/
)
{
    GameEngineVertexShader* newRes = CreateNamedRes(_name);
    newRes->CreateVersion("vs", _versionHigh, _versionLow);
    newRes->SetEntrtyPoint(_entryPoint);
    newRes->CompileHLSLCode(_path);
    newRes->CreateVertexShader();
    newRes->ShaderResCheck();
    return newRes;
}

void GameEngineVertexShader::InstancingShaderCompile(
    const std::string& _path, 
    const std::string& _entryPoint,
    UINT _versionHigh /*= 5*/,
    UINT _versionLow /*= 0*/
)
{
    instancingVertexShader_ = new GameEngineVertexShader(); //GameEngineRes에 등록되지 않는 점 주의.
    instancingVertexShader_->SetName(_entryPoint);
    instancingVertexShader_->CreateVersion("vs", _versionHigh, _versionLow);
    instancingVertexShader_->SetEntrtyPoint(_entryPoint);
    instancingVertexShader_->CompileHLSLCode(_path);
    instancingVertexShader_->CreateInstancingShader();
    instancingVertexShader_->ShaderResCheck();
}

void GameEngineVertexShader::CreateVertexShader()
{
    if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader(  //버텍스셰이더 생성 함수.
        binaryCode_->GetBufferPointer(), //컴파일된 바이너리 코드.
        binaryCode_->GetBufferSize(),    //컴파일된 바이너리코드 크기.
        NULL,                               //??
        &vertexShader_                      //버텍스셰이더 포인터.
    ))
    {
        MsgBoxAssert("버텍스셰이더 생성 실패.");
        return;
    }
}


void GameEngineVertexShader::CreateInstancingShader()
{
    if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader(  //버텍스셰이더 생성 함수.
        binaryCode_->GetBufferPointer(), //컴파일된 바이너리 코드.
        binaryCode_->GetBufferSize(),    //컴파일된 바이너리코드 크기.
        NULL,                               //??
        &vertexShader_                   //인스턴싱셰이더 포인터.
    ))
    {
        MsgBoxAssert("인스턴싱셰이더 생성 실패.");
        return;
    }
}
