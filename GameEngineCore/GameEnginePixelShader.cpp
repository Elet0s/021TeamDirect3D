#include "PreCompile.h"
#include "GameEnginePixelShader.h"
#include "GameEngineDevice.h"

GameEnginePixelShader::GameEnginePixelShader() : pixelShader_(nullptr), isDeferredRendering_(false)
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
        MsgBoxAssert("픽셀 셰이더가 없습니다.");
        return;
    }

    //두번째 인자는 #include나 #define등 hlsl에서 사용할 헤더나 디파인의 객체를 넣어줄수 있다.
    GameEngineDevice::GetContext()->PSSetShader(//파이프라인에 픽셀셰이더를 세팅하는 함수.
        pixelShader_,                      //픽셀셰이더 포인터.
        nullptr,                           //클래스 인스턴스 인터페이스 배열 주소값. 없으면 NULL.
        0                                  //사용할 클래스 인스턴스 인터페이스 배열의 인덱스.
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

void GameEnginePixelShader::InstancingPixelShaderCompile(
    const std::string_view& _path,
    const std::string_view& _entryPoint,
    UINT _versionHigh /*= 5*/,
    UINT _versionLow /*= 0*/
)
{
    inst_PixelShader_ = std::make_shared<GameEnginePixelShader>();  //GameEngineRes에 등록되지 않는 점 주의.
    inst_PixelShader_->SetName(_entryPoint);
    inst_PixelShader_->CreateVersion("ps", _versionHigh, _versionLow);
    inst_PixelShader_->SetEntrtyPoint(_entryPoint);
    inst_PixelShader_->CompileHLSLCode(_path);
    inst_PixelShader_->CreateInstancingPixelShader();
    inst_PixelShader_->ShaderResCheck(inst_PixelShader_->GetName());
}

void GameEnginePixelShader::CreatePixelShader()
{
    if (S_OK != GameEngineDevice::GetDevice()->CreatePixelShader(   //픽셀셰이더 생성 함수.
        binaryCode_->GetBufferPointer(),    //컴파일된 바이너리코드.
        binaryCode_->GetBufferSize(),       //컴파일된 바이너리코드 크기.
        NULL,                               //??
        &pixelShader_                       //픽셀셰이더 포인터.
    ))
    {
        MsgBoxAssert("픽셀 셰이더 생성 실패.");
        return;
    }
}

void GameEnginePixelShader::CreateInstancingPixelShader()
{
    if (S_OK != GameEngineDevice::GetDevice()->CreatePixelShader(   //픽셀셰이더 생성 함수.
        this->binaryCode_->GetBufferPointer(),  //컴파일된 바이너리코드.
        this->binaryCode_->GetBufferSize(),     //컴파일된 바이너리코드 크기.
        NULL,                                   //??
        &this->pixelShader_                     //픽셀셰이더 포인터.
    ))
    {
        MsgBoxAssert("인스턴싱 픽셀셰이더 생성 실패.");
        return;
    }
}

