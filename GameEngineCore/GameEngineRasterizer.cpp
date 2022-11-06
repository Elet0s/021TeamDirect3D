#include "PreCompile.h"
#include "GameEngineRasterizer.h"
#include "GameEngineDevice.h"

GameEngineRasterizer::GameEngineRasterizer(): rasterizerState_(nullptr), rasterizerDesc_()
{
}

GameEngineRasterizer::~GameEngineRasterizer()
{
    if (nullptr != rasterizerState_)
    {
        rasterizerState_->Release();
        rasterizerState_ = nullptr;
    }
}

GameEngineRasterizer* GameEngineRasterizer::Create(
    const std::string_view& _name,
    const D3D11_RASTERIZER_DESC& _desc
)
{
    GameEngineRasterizer* newRes = CreateNamedRes(_name);
    newRes->Create(_desc);
    return newRes;
}

void GameEngineRasterizer::Setting()
{
    if (nullptr == rasterizerState_)
    {
        MsgBoxAssert("래스터라이저 스테이트가 없습니다.");
        return;
    }

    GameEngineDevice::GetContext()->RSSetState(rasterizerState_);
    //래스터라이저 스테이트 객체를 파이프라인에 연결하는 함수.
}

void GameEngineRasterizer::Create(const D3D11_RASTERIZER_DESC& _desc)
{
    rasterizerDesc_ = _desc;

    if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(
        &rasterizerDesc_,
        &rasterizerState_
    ))
    {
        MsgBoxAssert("래스터라이저 스테이트 생성 실패.");
        return;
    }
}
