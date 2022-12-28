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
        MsgBoxAssert("지오메트리 셰이더가 없습니다.");
        return;
    }

    //두번째 인자는 #include나 #define등 hlsl에서 사용할 헤더나 디파인의 객체를 넣어줄수 있다.
    GameEngineDevice::GetContext()->GSSetShader(//파이프라인에 지오메트리 셰이더를 세팅하는 함수.
        geometryShader_,                    //지오메트리 셰이더 포인터.
        nullptr,                            //클래스 인스턴스 인터페이스 배열 주소값. 없으면 NULL.
        0                                   //사용할 클래스 인스턴스 인터페이스 배열의 인덱스.
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
        this->binaryCode_->GetBufferPointer(),  //컴파일된 바이너리코드.
        this->binaryCode_->GetBufferSize(),     //컴파일된 바이너리코드 크기.
        NULL,                                   //??
        &this->geometryShader_                  //픽셀셰이더 포인터.
    ))
    {
        MsgBoxAssert("지오메트리 셰이더 생성 실패.");
        return;
    }
}