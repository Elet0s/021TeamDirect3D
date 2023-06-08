#include "PreCompile.h"
#include "GameEngineInputLayout.h"
#include "GameEngineDevice.h"
#include "GameEngineVertexes.h"
#include "GameEngineVertexShader.h"

GameEngineInputLayout::GameEngineInputLayout() : inputLayout_(nullptr)
{
}

GameEngineInputLayout::~GameEngineInputLayout()
{
    if (nullptr != inputLayout_)
    {
        inputLayout_->Release();
        inputLayout_ = nullptr;
    }
}

void GameEngineInputLayout::CreateInputLayout(
    const GameEngineInputLayoutDesc& _desc,
    GameEngineVertexShader* _vertexShader
)
{
    if (S_OK != GameEngineDevice::GetDevice()->CreateInputLayout(	//인풋레이아웃 생성 함수.
        &_desc.descs_[0],									//인풋레이아웃 생성시 필요한 D3D11_INPUT_ELEMENT_DESC포인터 배열 첫번째 원소의 포인터.
        static_cast<UINT>(_desc.descs_.size()),				//D3D11_INPUT_ELEMENT_DESC포인터 배열의 크기.
        _vertexShader->binaryCode_->GetBufferPointer(),	    //컴파일된 셰이더 바이너리코드
        _vertexShader->binaryCode_->GetBufferSize(),		//컴파일된 셰이더 바이너리코드 크기.
        &inputLayout_                                       //생성된 인풋레이아웃을 받을 ID3D11InputLayout포인터.
    ))
    {
        MsgBoxAssert("인풋레이아웃 생성 실패.");
        return;
    }
}

void GameEngineInputLayout::Set()
{
    if (nullptr == inputLayout_)
    {
        MsgBoxAssert("인풋레이아웃이 없습니다.");
        return;
    }

    GameEngineDevice::GetDC()->IASetInputLayout(inputLayout_);
}

GameEngineInputLayout* GameEngineInputLayout::Create(
    const GameEngineInputLayoutDesc& _desc,
    GameEngineVertexShader* _vertexShader
)
{
    GameEngineInputLayout* newRes = CreateUnnamedRes();
    newRes->CreateInputLayout(_desc, _vertexShader);
    return newRes;
}
