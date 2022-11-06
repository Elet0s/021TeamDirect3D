#include "PreCompile.h"
#include "GameEngineDepthStencil.h"
#include "GameEngineDevice.h"

GameEngineDepthStencil::GameEngineDepthStencil(): depthStencilState_(nullptr), depthStencilDesc_()
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
    newRes->Create(_desc);
    return newRes;
}

void GameEngineDepthStencil::Setting()
{
    if (nullptr == depthStencilState_)
    {
        MsgBoxAssert("���� ���ٽ� ������Ʈ�� �����ϴ�.");
        return;
    }

    GameEngineDevice::GetContext()->OMSetDepthStencilState(//���� ���ٽ� ������Ʈ�� ������ ���������ο� �����Ű�� �Լ�. 
        depthStencilState_, //������ ���� ���ٽ� ������Ʈ.
        0                   //���� ���ٽ� �׽�Ʈ�� ������ �� �ʿ��� ���� ��??
    );
}

void GameEngineDepthStencil::Create(const D3D11_DEPTH_STENCIL_DESC& _desc)
{
    depthStencilDesc_ = _desc;

    if (S_OK != GameEngineDevice::GetDevice()->CreateDepthStencilState(//���� ���ٽ� ������Ʈ ���� �Լ�.
        &depthStencilDesc_, //���� ���ٽ� ������Ʈ ������ �ʿ��� ����.
        &depthStencilState_ //������ ID3D11DepthStencilState �������̽� ������.
    ))
    {
        MsgBoxAssert("���� ���ٽ� ������Ʈ ���� ����.");
        return;
    }
}
