cbuffer RenderOption : register(b10)
{
    float deltaTime_;
    float sumDeltaTime_;
    int isAnimation_;
    int vertexInversion_;   //그림자용 정점 좌우 뒤집힘 표시 변수. 좌우 뒤집어야 하면 -1 대입.
    float pivotPosX_;       //피봇포스 X
    float pivotPosY_;       //피봇포스 Y
    float lightingRotationX_; //조명 X축 각도. 기본값 30도.
    float lightingRotationY_; //조명 Y축 각도. 기본값 0도.
}

struct InstRenderOption
{
    float deltaTime_;
    float sumDeltaTime_;
    int isAnimation_;
    int vertexInversion_; //그림자용 정점 좌우 뒤집힘 표시 변수. 좌우 뒤집어야 하면 -1 대입.
    float pivotPosX_; //피봇포스 X.
    float pivotPosY_; //피봇포스 Y.
    float lightingRotationX_; //조명 X축 각도.
    float lightingRotationY_; //조명 Y축 각도.
};