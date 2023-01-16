#include "PreCompile.h"
#include "GameEngineDepthStencil.h"
#include "GameEngineDevice.h"

GameEngineDepthStencil::GameEngineDepthStencil() : depthStencilState_(nullptr), depthStencilDesc_()
{
}

GameEngineDepthStencil::~GameEngineDepthStencil()
{
    if (nullptr != depthStencilState_)
    {
        depthStencilState_->Release();
        depthStencilState_ = nullptr;
    }
}

GameEngineDepthStencil* GameEngineDepthStencil::Create(
    const std::string_view& _name,
    const D3D11_DEPTH_STENCIL_DESC& _desc
)
{
    GameEngineDepthStencil* newRes = CreateNamedRes(_name);
    newRes->CreateDepthStencilState(_desc);
    return newRes;
}

void GameEngineDepthStencil::Set()
{
    if (nullptr == depthStencilState_)
    {
        MsgBoxAssert("깊이 스텐실 스테이트가 없습니다.");
        return;
    }

    GameEngineDevice::GetDC()->OMSetDepthStencilState(//깊이 스텐실 스테이트를 렌더링 파이프라인에 연결시키는 함수. 
        depthStencilState_, //연결할 깊이 스텐실 스테이트.
        0                   //깊이 스텐실 테스트를 수행할 때 필요한 기준 값??
    );
}

void GameEngineDepthStencil::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC& _desc)
{
    depthStencilDesc_ = _desc;

    if (S_OK != GameEngineDevice::GetDevice()->CreateDepthStencilState(//깊이 스텐실 스테이트 생성 함수.
        &depthStencilDesc_, //깊이 스텐실 스테이트 생성시 필요한 명세서.
        &depthStencilState_ //생성할 ID3D11DepthStencilState 인터페이스 포인터.
    ))
    {
        MsgBoxAssert("깊이 스텐실 스테이트 생성 실패.");
        return;
    }
}
