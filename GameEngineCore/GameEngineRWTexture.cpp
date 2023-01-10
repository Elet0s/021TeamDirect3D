#include "PreCompile.h"
#include "GameEngineRWTexture.h"
#include "GameEngineDevice.h"
#include "GameEngineTexture.h"

GameEngineRWTexture::GameEngineRWTexture()
{
}

GameEngineRWTexture::~GameEngineRWTexture()
{
}

std::shared_ptr<GameEngineRWTexture> GameEngineRWTexture::Create(const std::string& _name)
{
    return CreateNamedRes(_name);
}

std::shared_ptr<GameEngineRWTexture> GameEngineRWTexture::Create()
{
    return CreateUnnamedRes();
}

void GameEngineRWTexture::CreateUnorderedAccessTexture(D3D11_TEXTURE2D_DESC _desc, const float4& _clearColor)
{
    std::shared_ptr<GameEngineTexture> newTexture = GameEngineTexture::Create(_desc);
    CreateUnorderedAccessTexture(newTexture, _clearColor);
}

void GameEngineRWTexture::CreateUnorderedAccessTexture(std::shared_ptr<GameEngineTexture> _texture, const float4& _clearColor)
{
    this->unorderedAccessTexture_.push_back(_texture);
    this->unorderedAccessViews_.push_back(_texture->CreateUnorderedAccessView());
    this->clearColors_.push_back(_clearColor);
}

void GameEngineRWTexture::CSSetUnorderedAccessView(int _bindPoint)
{
    if (true == unorderedAccessViews_.empty())
    {
        MsgBoxAssert("세팅할 순서없는 접근 뷰가 하나도 없습니다.");
        return;
    }

    GameEngineDevice::GetDC()->CSSetUnorderedAccessViews(
        _bindPoint,
        static_cast<UINT>(unorderedAccessViews_.size()),
        &this->unorderedAccessViews_[0],
        0 /*-1*/
    );
}

void GameEngineRWTexture::Clear()
{
    for (size_t i = 0; i < unorderedAccessViews_.size(); ++i)
    {
        GameEngineDevice::GetDC()->ClearUnorderedAccessViewFloat(
            this->unorderedAccessViews_[i],
            this->clearColors_[i].arr1D
        );
    }
}
