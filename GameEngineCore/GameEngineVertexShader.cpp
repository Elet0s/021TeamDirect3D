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

    if (nullptr != inst_VertexShader_)
    {
        delete inst_VertexShader_;
        inst_VertexShader_ = nullptr;
    }
}

void GameEngineVertexShader::Set()
{
    if (nullptr == vertexShader_)
    {
        MsgBoxAssert("버텍스 셰이더가 없습니다.");
        return;
    }

    //두번째 인자는 #include나 #define등 hlsl에서 사용할 헤더나 디파인의 객체를 넣어줄수 있다.
    GameEngineDevice::GetDC()->VSSetShader(//파이프라인에 버텍스셰이더를 세팅하는 함수.
        vertexShader_,                     //버텍스 셰이더 포인터.
        nullptr,                           //클래스 인스턴스 인터페이스 배열 주소값. 없으면 NULL.
        0                                  //사용할 클래스 인스턴스 인터페이스 배열의 인덱스.
    );
}

GameEngineVertexShader* GameEngineVertexShader::Load(
    const std::string_view& _path,
    const std::string_view& _entryPoint,
    UINT _versionHigh /*= 5*/,
    UINT _versionLow /*= 0*/
)
{
    return Load(_path, GameEnginePath::GetFileName(_path), _entryPoint, _versionHigh, _versionLow);
}

GameEngineVertexShader* GameEngineVertexShader::Load(
    const std::string_view& _path,
    const std::string_view& _name,
    const std::string_view& _entryPoint,
    UINT _versionHigh /*= 5*/,
    UINT _versionLow /*= 0*/
)
{
    GameEngineVertexShader* newRes = CreateNamedRes(_name);
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
    inst_VertexShader_ = new GameEngineVertexShader(); //GameEngineRes에 등록되지 않는 점 주의.
    inst_VertexShader_->SetName(_entryPoint);
    inst_VertexShader_->CreateVersion("vs", _versionHigh, _versionLow);
    inst_VertexShader_->SetEntrtyPoint(_entryPoint);
    inst_VertexShader_->CompileHLSLCode(_path);
    inst_VertexShader_->CreateInstancingVertexShader();
    inst_VertexShader_->ShaderResCheck(inst_VertexShader_->GetName());
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
        MsgBoxAssert("버텍스 셰이더 생성 실패.");
        return;
    }
}


void GameEngineVertexShader::CreateInstancingVertexShader()
{
    if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader(  //버텍스셰이더 생성 함수.
        this->binaryCode_->GetBufferPointer(), //컴파일된 바이너리 코드.
        this->binaryCode_->GetBufferSize(),    //컴파일된 바이너리코드 크기.
        NULL,                                   //??
        &this->vertexShader_                   //인스턴스 버텍스셰이더 포인터.
    ))
    {
        MsgBoxAssert("인스턴싱 버텍스셰이더 생성 실패.");
        return;
    }
}
