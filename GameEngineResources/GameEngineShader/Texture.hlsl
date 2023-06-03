#include "TransformHeader.hlsli"

struct Input
{
    //멤버변수간 순서는 전혀 중요하지 않다. 인풋 레이아웃을 통해 각 멤버변수의 오프셋값만 정확히 알려주면 된다??
    //단지 편의를 위해서 되도록 순서를 지킬 뿐이다??
    float4 pos_ : POSITION;
    float4 texcoord_ : TEXCOORD;
};

struct Output
{
    //시맨틱(semantic). GPU에게 알려주는, 해당 값의 종류. GPU가 자동으로 처리할 수 있는 종류의 값이면 자동으로 처리해준다.
    float4 pos_ : SV_Position; //SV_Position: 이 시맨틱을 통해서만이 버텍스 셰이더에서 변경된 정점 위치를 래스터라이저로 전달할 수 있다.
    //SV는 System-Value semantic의 약자로, DirectX10에서부터 도입된, 용도가 정해져 있어서 GPU가 자동으로 처리하는 시맨틱 키워드이다.
    
    float4 posLocal_ : POSITION; //최초 정점좌표(-0.5~0.5 사이 좌표). 

    float4 texcoord_ : TEXCOORD; //TEXCOORD[n]: 텍스쳐의 UV값을 의미하는 시맨틱네임. 텍스쳐좌표를 뜻하는 Texture Coordinate의 줄임말.

};

Output Texture_VS(Input _input)
{
    Output result = (Output) 0; //Output타입 변수 newOutput을 0으로 초기화.
    //HLSL의 경우에는 대부분의 상황에서 형변환이 가능하다.

    result.pos_ = mul(_input.pos_, worldViewProjectionMatrix_); //WVP행렬 적용.
    
    result.posLocal_ = _input.pos_; //WVP행렬 비적용. 최초 정점좌표(-0.5~0.5 사이 좌표) 유지.
    
    result.texcoord_ = _input.texcoord_;
    
    return result;
}

//cbuffer ColorData : register(b0)
//{
//    float4 mulColor_;
//    float4 plusColor_;
//};

Texture2D DiffuseTexture : register(t0);
SamplerState LINEARWRAP : register(s0);

float4 Texture_PS(Output _input) : SV_Target0 //SV_Target[n]: n번 렌더타겟에 결과값을 저장한다.
{
    float4 resultColor = DiffuseTexture.Sample(LINEARWRAP, _input.texcoord_.xy);
    //float4 color = (Tex.Sample(Smp, _input.texcoord_.xy) * mulColor_) + plusColor_;
    
    if (resultColor.a <= 0.f)
    {
        clip(-1);
    }

    return resultColor;
}