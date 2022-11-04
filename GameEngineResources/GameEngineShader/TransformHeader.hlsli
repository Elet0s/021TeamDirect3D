//cbuffer: ��� ����(Constant Buffer) ����ü.
//�� ��� ���۴� �ִ� 4096���� 16 * n����Ʈ ũ���� ���͸� ������ �� �ִ�. 
//�� ���Ϳ��� �ִ� 4���� 32��Ʈ ���� ������ �� �ִ�. 

//������۴� �ּ� 16����Ʈ �̻��� ũ�⸦ ������ �ϴ� ������ ����??
//->MSDN���� ����� �׼����� ������Ʈ�� ���� ����ȭ���ױ� �����̶�� �Ѵ�.

//������۴� ���α׷� ���ο��� ��������ó�� ���ȴ�.
cbuffer TransformData : register(b0) //<-register(b0): ������ ���������� 0�� ���Կ� ����Ǵ� ��� ���۶�� �ǹ�.
    //t: �ؽ���, c: ���� ������, s: ���÷�, u: unordered access view.
    //register(ps_5_0, b0) <-�̷� ������ Ư�� ���̴��� hlsl�����Ϸ� ������ �����ؼ� ����� ���� �ִٰ� �Ѵ�.
{
    float4 localScaleVector_;    //���� ��ǥ�� ũ��. ũ�Ⱑ 0�� ��ü�� ������ �� �����Ƿ� �⺻���� 1�� �Ǿ�� �Ѵ�.
    float4 localRotationVector_; //���� ��ǥ�� ����(����).
    float4 localPositionVector_; //���� ��ǥ�� �̵�(��ġ).

    float4x4 localScaleMatrix_;    //ũ�����.
    float4x4 localRotationMatrix_; //�������(����).
    float4x4 localPositionMatrix_; //�̵����(��ġ).

    float4x4 localWorldMatrix_;
	//������Ʈ�� ũ��, ����, �̵������ �ݿ���, �θ� ������Ʈ�� ���ÿ���󿡼��� �������. ����� �߰�����.


    float4 worldScaleVector_; //������ǥ�� ũ��. �̵����� �����Ƿ� w�� 0���� �����Ѵ�.
    float4 worldRotationVector_; //������ǥ�� ȸ����. �̵����� �����Ƿ� w�� 0���� �����Ѵ�.
    float4 worldPositionVector_; //������ǥ�� ��ġ. �̵����� �ݿ��ؾ� �ϹǷ� w�� 1���� �����Ѵ�.


    float4x4 worldWorldMatrix_;
	//������Ʈ�� ���� ũ��, ���� ����, ���� �̵���Ŀ� �θ��� ������ı��� �ݿ��� ���� ���� ���.
	//���⿡ ī�޶� ������Ʈ�� ����İ� ������ı��� ��ġ�� ���� ��μ� ����Ϳ� ��� �� �ְ� �ȴ�.

    float4x4 viewMatrix_; //�����.
    float4x4 projectionMatrix_; //�������.

    float4x4 worldViewMatrix_; //������Ŀ� ������� ����� ���.
    float4x4 worldViewProjectionMatrix_; //������Ŀ� ����� + ������ı��� ����� ���.
};

struct InstTransformData
{
    float4 localScaleVector_; //���� ��ǥ�� ũ��. ũ�Ⱑ 0�� ��ü�� ������ �� �����Ƿ� �⺻���� 1�� �Ǿ�� �Ѵ�.
    float4 localRotationVector_; //���� ��ǥ�� ����(����).
    float4 localPositionVector_; //���� ��ǥ�� �̵�(��ġ).

    float4x4 localScaleMatrix_; //ũ�����.
    float4x4 localRotationMatrix_; //�������(����).
    float4x4 localPositionMatrix_; //�̵����(��ġ).

    float4x4 localWorldMatrix_;
	//������Ʈ�� ũ��, ����, �̵������ �ݿ���, �θ� ������Ʈ�� ���ÿ���󿡼��� �������. ����� �߰�����.


    float4 worldScaleVector_; //������ǥ�� ũ��. �̵����� �����Ƿ� w�� 0���� �����Ѵ�.
    float4 worldRotationVector_; //������ǥ�� ȸ����. �̵����� �����Ƿ� w�� 0���� �����Ѵ�.
    float4 worldPositionVector_; //������ǥ�� ��ġ. �̵����� �ݿ��ؾ� �ϹǷ� w�� 1���� �����Ѵ�.

    float4x4 worldWorldMatrix_;
	//������Ʈ�� ���� ũ��, ���� ����, ���� �̵���Ŀ� �θ��� ������ı��� �ݿ��� ���� ���� ���.
	//���⿡ ī�޶� ������Ʈ�� ����İ� ������ı��� ��ġ�� ���� ��μ� ����Ϳ� ��� �� �ְ� �ȴ�.

    float4x4 viewMatrix_; //�����.
    float4x4 projectionMatrix_; //�������.

    float4x4 worldViewMatrix_; //������Ŀ� ������� ����� ���.
    float4x4 worldViewProjectionMatrix_; //������Ŀ� ����� + ������ı��� ����� ���.
};

StructuredBuffer<InstTransformData> allInstancingTransformDataBuffer : register(t12);