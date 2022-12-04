cbuffer RenderOption : register(b10)
{
    float deltaTime_;
    float sumDeltaTime_;
    int isAnimation_;
    int vertexInversion_;   //그림자용 정점 좌우 뒤집힘 표시 변수. 좌우 뒤집어야 하면 -1 대입.
    float pivotPosX_;      //피봇포스 X.
    float pivotPosY_;      //피봇포스 Y.
    float shadowAngle_;
    int bytePad1_;
}

struct InstRenderOption
{
    float deltaTime_;
    float sumDeltaTime_;
    int isAnimation_;
    int vertexInversion_; //그림자용 정점 좌우 뒤집힘 표시 변수. 좌우 뒤집어야 하면 -1 대입.
    float pivotPosX_; //피봇포스 X.
    float pivotPosY_; //피봇포스 Y.
    float shadowAngle_;
    int bytePad1_;
};

