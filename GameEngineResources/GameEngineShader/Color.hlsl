//HLSL(High-Level Shader Language): 
//�׷���ī�� �޸𸮿� ����� Ư�� �����Ϳ� ���� ó�� ����� GPU�� ������ �� �ִ� ���̴� ���ۿ� ���.

//���̴� ��Ģ0: ���ؽ� ���̴��� "_VS + (",�ȼ� ���̴��� "_PS + ("�� ���ڿ����ο� ���ԵǾ��־�� �Ѵ�.
//���̴� ��Ģ1: ���̴����ϸ�.hlsl ������ �ݵ�� ���̴����ϸ�_VS, ���̴����ϸ�_PS��� �̸��� 
// ���ؽ� ���̴�, �ȼ� ���̴� �Ѱ������� ������ �ִ�. �׸��� "���̴����ϸ�.hlsl" �̶�� �̸����� ����ȴ�. 

#include "TransformHeader.hlsli"

struct Input
{
    //��������� ������ ���� �߿����� �ʴ�. ��ǲ ���̾ƿ��� ���� �� ��������� �����°��� ��Ȯ�� �˷��ָ� �ȴ�.
    //���� ���Ǹ� ���ؼ� �ǵ��� ������ ��ų ���̴�.
    float4 pos_: POSITION;
};

struct Output
{
    //�ø�ƽ(semantic). GPU���� �˷��ִ�, �ش� ���� ����. GPU�� �ڵ����� ó���� �� �ִ� ������ ���̸� �ڵ����� ó�����ش�.
    float4 pos_ : SV_Position; 
    //SV_Position: �� �ø�ƽ�� ���ؼ����� ���ؽ� ���̴����� ����� ���� ��ġ�� �����Ͷ������� ������ ����Ʈ��ȯ�� �̷������.
    //SV�� System-Value semantic�� ���ڷ�, DirectX10�������� ���Ե�, �뵵�� ������ �־ GPU�� �ڵ����� ó���ϴ� �ø�ƽ Ű�����̴�.   
    
};

Output Color_VS(Input _input)
{
    Output newOutput = (Output)0;  //OutputŸ�� ���� newOutput�� 0���� �ʱ�ȭ.
    
    //HLSL�� ��쿡�� ��κ��� ��Ȳ���� ����ȯ�� �����ϴ�.

    newOutput.pos_ = mul(_input.pos_, worldViewProjectionMatrix_);  //WVP��� ����.
    
    

	return newOutput;
}

cbuffer ResultColor : register(b8)
{
    float4 color_;
}


//���ؽ� ���̴��� ��ȯ���� �����ϸ� �ڵ����� �ȼ����̴��� �Ű������� ����.
//������ �ȼ� ���ڸ�ŭ ȣ��ȴ�.
float4 Color_PS(Output _input) : SV_Target0 
//SV_Target[n]: �� ���̴��� ��ģ ������� n�� ����Ÿ�ٿ� ����ȴٴ� �ǹ��� �ø�ƽ.
{
    return color_;
    
  
    //�� �׸���.
    //if (0.5f < length(_input.posLocal_.xy))
    //{
    //    clip(-1);
    //}
    
    //Ÿ�� �׸���1.
    //if (0.5f < length(_input.pos2_.xy - f))
    //{
    //    clip(-1);
    //}
    //if (0.5f < length(_input.pos2_.xy + (float2)0.2f))
    //{
    //    clip(-1);
    //}
    
    
    //Ÿ�� �׸���2.
    //if (0.5f < length(_input.pos2_.xy - float2(0.2f, 0.f)))
    //{
    //    clip(-1);
    //}
    //if (0.5f < length(_input.pos2_.xy + float2(0.2f, 0.f)))
    //{
    //    clip(-1);
    //}
    
    
  
    //if (_input.pos_.x < 675.f)  
    //{
    //    clip(-1);
    //}
    

}