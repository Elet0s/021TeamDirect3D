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
        MsgBoxAssert("�����Ͷ����� ������Ʈ�� �����ϴ�.");
        return;
    }

    GameEngineDevice::GetContext()->RSSetState(rasterizerState_);
    //�����Ͷ����� ������Ʈ ��ü�� ���������ο� �����ϴ� �Լ�.
}

void GameEngineRasterizer::Create(const D3D11_RASTERIZER_DESC& _desc)
{
    rasterizerDesc_ = _desc;

    if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(
        &rasterizerDesc_,
        &rasterizerState_
    ))
    {
        MsgBoxAssert("�����Ͷ����� ������Ʈ ���� ����.");
        return;
    }
}
