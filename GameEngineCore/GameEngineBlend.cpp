#include "PreCompile.h"
#include "GameEngineBlend.h"
#include "GameEngineDevice.h"

GameEngineBlend::GameEngineBlend()
    : blendState_(nullptr),
    blendDesc_(),
    factor_(float4::One),
    mask_(0xffffffff)
{
}

GameEngineBlend::~GameEngineBlend()
{
    if (nullptr != blendState_)
    {
        blendState_->Release();
        blendState_ = nullptr;
    }
}

GameEngineBlend* GameEngineBlend::Create(
    const std::string_view& _name,
    const D3D11_BLEND_DESC& _desc
)
{
    GameEngineBlend* newRes = CreateNamedRes(_name);
    newRes->CreateBlendState(_desc);
    return newRes;
}

void GameEngineBlend::Set()
{
    if (nullptr == blendState_)
    {
        MsgBoxAssert("���彺����Ʈ�� �����ϴ�.");
        return;
    }

    GameEngineDevice::GetDC()->OMSetBlendState(blendState_, &factor_.w, mask_);

}

void GameEngineBlend::CreateBlendState(const D3D11_BLEND_DESC& _desc)
{
    blendDesc_ = _desc;


    if (S_OK != GameEngineDevice::GetDevice()->CreateBlendState(
        &blendDesc_,
        &blendState_
    ))
    {
        MsgBoxAssert("���彺����Ʈ ���� ����.");
        return;
    }
}
