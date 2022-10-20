#include "PreCompile.h"
#include "GameEngineMath.h"

const float GameEngineMath::PI = 3.14159265359f;
const float GameEngineMath::PI2 = PI * 2.0f;
const float GameEngineMath::HalfPI = PI * 0.5f;
const float GameEngineMath::DegreeToRadian = GameEngineMath::PI / 180.0f;	//60분법->호도법(0.017453...)
const float GameEngineMath::RadianToDegree = 180.0f / GameEngineMath::PI;	//호도법->60분법(57.29577...)

const float4 float4::Zero = { 0, 0, 0, 0 };
const float4 float4::One = { 1, 1, 1, 1 };

const float4 float4::Left = { -1, 0, 0, 1};
const float4 float4::Right = { 1, 0, 0, 1 };
const float4 float4::Up = { 0, 1, 0, 1 };
const float4 float4::Down = { 0, -1, 0, 1 };
const float4 float4::Forward = { 0, 0, 1, 1 };
const float4 float4::Back = { 0, 0, -1, 1 };

const float4 float4::Red = { 1, 0, 0, 1 };
const float4 float4::Green = { 0, 1, 0, 1 };
const float4 float4::Blue = { 0, 0, 1, 1 };
const float4 float4::Yellow = { 1, 1, 0, 1 };
const float4 float4::Magenta = { 1, 0, 1, 1 };
const float4 float4::Cyan = { 0, 1, 1, 1 };

const float4 float4::Black = { 0, 0, 0, 1 };
const float4 float4::White = { 1, 1, 1, 1 };

const float4x4 float4x4::ZeroMatrix = {
	float4::Zero, float4::Zero, float4::Zero, float4::Zero
};

GameEngineMath::GameEngineMath()
{
}

GameEngineMath::~GameEngineMath()
{
}

float4 operator*(const float4& _vector, const float4x4& _matrix)
{
	float4 result = DirectX::XMVector4Transform(_vector.directXVector_, _matrix.directXMatrix_);
	return result;
}

float4& operator*=(float4& _vector, const float4x4& _matrix)
{
	_vector = DirectX::XMVector4Transform(_vector.directXVector_, _matrix.directXMatrix_);
	return _vector;
}
