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

float4 float4::MatrixToQuarternion(const float4x4& _matrix)
{
	return DirectX::XMQuaternionRotationMatrix(_matrix.directXMatrix_);

	//float4 Return;

	//if (_matrix.arrVector[0].IsNearlyZero() || _matrix.arrVector[1].IsNearlyZero() || _matrix.arrVector[2].IsNearlyZero())
	//{
	//	Return.x = 0.0f;
	//	Return.y = 0.0f;
	//	Return.z = 0.0f;
	//	Return.w = 1.0f;
	//	return Return;
	//}

	//float	s;

	//// Check diagonal (trace)
	//const float tr = _matrix.arr2D[0][0] + _matrix.arr2D[1][1] + _matrix.arr2D[2][2];

	//if (tr > 0.0f)
	//{
	//	float InvS = InvSqrt(tr + 1.f);
	//	Return.w = 0.5f * (1.f / InvS);
	//	s = 0.5f * InvS;

	//	Return.x = (_matrix.arr2D[1][2] - _matrix.arr2D[2][1]) * s;
	//	Return.y = (_matrix.arr2D[2][0] - _matrix.arr2D[0][2]) * s;
	//	Return.z = (_matrix.arr2D[0][1] - _matrix.arr2D[1][0]) * s;
	//}
	//else
	//{
	//	// diagonal is negative
	//	int i = 0;

	//	if (_matrix.arr2D[1][1] > _matrix.arr2D[0][0])
	//		i = 1;

	//	if (_matrix.arr2D[2][2] > _matrix.arr2D[i][i])
	//		i = 2;

	//	static const int nxt[3] = { 1, 2, 0 };
	//	const int j = nxt[i];
	//	const int k = nxt[j];

	//	s = _matrix.arr2D[i][i] - _matrix.arr2D[j][j] - _matrix.arr2D[k][k] + 1.0f;

	//	float InvS = InvSqrt(s);

	//	float qt[4];
	//	qt[i] = 0.5f * (1.f / InvS);

	//	s = 0.5f * InvS;

	//	qt[3] = (_matrix.arr2D[j][k] - _matrix.arr2D[k][j]) * s;
	//	qt[j] = (_matrix.arr2D[i][j] + _matrix.arr2D[j][i]) * s;
	//	qt[k] = (_matrix.arr2D[i][k] + _matrix.arr2D[k][i]) * s;

	//	Return.x = qt[0];
	//	Return.y = qt[1];
	//	Return.z = qt[2];
	//	Return.w = qt[3];
	//}

	//return Return;
}

