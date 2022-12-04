cbuffer RenderOption : register(b10)
{
    float deltaTime_;
    float sumDeltaTime_;
    int isAnimation_;
    int vertexInversion_;   //�׸��ڿ� ���� �¿� ������ ǥ�� ����. �¿� ������� �ϸ� -1 ����.
    float pivotPosX_;      //�Ǻ����� X.
    float pivotPosY_;      //�Ǻ����� Y.
    float shadowAngle_;
    int bytePad1_;
}

struct InstRenderOption
{
    float deltaTime_;
    float sumDeltaTime_;
    int isAnimation_;
    int vertexInversion_; //�׸��ڿ� ���� �¿� ������ ǥ�� ����. �¿� ������� �ϸ� -1 ����.
    float pivotPosX_; //�Ǻ����� X.
    float pivotPosY_; //�Ǻ����� Y.
    float shadowAngle_;
    int bytePad1_;
};

