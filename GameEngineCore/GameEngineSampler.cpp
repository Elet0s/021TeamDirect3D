#include "PreCompile.h"
#include "GameEngineSampler.h"
#include "GameEngineDevice.h"

GameEngineSampler::GameEngineSampler() : samplerState_(nullptr), samplerDesc_()
{
}

GameEngineSampler::~GameEngineSampler()
{
    if (nullptr != samplerState_)
    {
        samplerState_->Release();
        samplerState_ = nullptr;
    }
}

GameEngineSampler* GameEngineSampler::Create(const std::string_view& _name, const D3D11_SAMPLER_DESC& _desc)
{
    GameEngineSampler* newSampler = CreateNamedRes(_name);
    newSampler->CreateSampler(_desc);
    return newSampler;
}

void GameEngineSampler::VSSetSampler(int _bindPoint)
{
    if (nullptr == samplerState_)
    {
        MsgBoxAssert("���÷� ������Ʈ�� �����ϴ�.");
        return;
    }

    GameEngineDevice::GetDC()->VSSetSamplers(
        _bindPoint,
        1,
        &samplerState_
    );
}

void GameEngineSampler::CSSetSampler(int _bindPoint)
{
    if (nullptr == samplerState_)
    {
        MsgBoxAssert("���÷� ������Ʈ�� �����ϴ�.");
        return;
    }

    GameEngineDevice::GetDC()->CSSetSamplers(
        _bindPoint,
        1,
        &samplerState_
    );
}

void GameEngineSampler::PSSetSampler(int _bindPoint)
{
    if (nullptr == samplerState_)
    {
        MsgBoxAssert("���÷� ������Ʈ�� �����ϴ�.");
        return;
    }

    GameEngineDevice::GetDC()->PSSetSamplers(
        _bindPoint,
        1,
        &samplerState_
    );
}

void GameEngineSampler::CreateSampler(const D3D11_SAMPLER_DESC& _desc)
{
    samplerDesc_ = _desc;

    if (S_OK != GameEngineDevice::GetDevice()->CreateSamplerState(
        &samplerDesc_,
        &samplerState_
    ))
    {
        MsgBoxAssert("���÷� ������Ʈ ���� ����.");
        return;
    }
}
