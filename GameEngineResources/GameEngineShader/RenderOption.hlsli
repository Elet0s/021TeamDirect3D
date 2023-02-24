cbuffer RenderOption : register(b10)
{
    float deltaTime_;
    float sumDeltaTime_;
    int isAnimation_;
    int vertexInversion_;   //�׸��ڿ� ���� �¿� ������ ǥ�� ����. �¿� ������� �ϸ� -1 ����.
    float pivotPosX_;       //�Ǻ����� X
    float pivotPosY_;       //�Ǻ����� Y
    float lightingRotationX_; //���� X�� ����. �⺻�� 30��.
    float lightingRotationY_; //���� Y�� ����. �⺻�� 0��.
}

struct InstRenderOption
{
    float deltaTime_;
    float sumDeltaTime_;
    int isAnimation_;
    int vertexInversion_; //�׸��ڿ� ���� �¿� ������ ǥ�� ����. �¿� ������� �ϸ� -1 ����.
    float pivotPosX_; //�Ǻ����� X.
    float pivotPosY_; //�Ǻ����� Y.
    float lightingRotationX_; //���� X�� ����.
    float lightingRotationY_; //���� Y�� ����.
};