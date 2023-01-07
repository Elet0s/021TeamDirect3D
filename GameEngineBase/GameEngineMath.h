#pragma once

class GameEngineMath
{
public:
	static const float PI;
	static const float PI2;
	static const float HalfPI;
	static const float DegreeToRadian;	//60분법->호도법(0.017453...)
	static const float RadianToDegree;	//호도법->60분법(57.29577...)


private:
	GameEngineMath();
	~GameEngineMath();

	GameEngineMath(const GameEngineMath& _Other) = delete;
	GameEngineMath(GameEngineMath&& _Other) noexcept = delete;
	GameEngineMath& operator=(const GameEngineMath& _Other) = delete;
	GameEngineMath& operator=(GameEngineMath&& _Other) noexcept = delete;


public:
	static float Lerp(float _p1, float _p2, float _time)
	{
		return (1.0f - _time) * _p1 + _time * _p2;
	}

	static float LerpTime(float _p1, float _p2, float _time)
	{
		if (1.f <= _time)
		{
			_time = 1.f;
		}
		return Lerp(_p1, _p2, _time);
	}

};


class float4x4;
class float4
{
public:

	//자주 사용하는 숫자 조합을 미리 만들어놓으면 생성자 호출하는 연산비용을 아낄 수 있다.

	static const float4 Zero;	//0000
	static const float4 One;	//1111

	static const float4 Left;	//--x
	static const float4 Right;	//++x
	static const float4 Up;		//++y
	static const float4 Down;	//--y
	static const float4 Forward;//++z
	static const float4 Back;	//--z

	static const float4 Red;	//1001
	static const float4 Green;	//0101
	static const float4 Blue;	//0011
	static const float4 Yellow;	//1101
	static const float4 Magenta;//1011
	static const float4 Cyan;	//0111

	static const float4 Black;	//0001
	static const float4 White;	//1111

	//무명유니온의 장점??
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};

		struct
		{
			float posX;
			float posY;
			float sizeX;
			float sizeY;
		};

		struct
		{
			int intValueX; 
			int intValueY;
			int intValueZ;
			int intValueW;
		};

		//동차좌표계(Homogeneous Coordinates): n차원의 공간을 n+1개의 좌표로 나타내는 좌표계라고 한다.
		//실질적으로는 투영변환, 그중에서도 원근투영변환의 결과값 == 카메라위치로부터의 방향이 적용된 값을 저장하기 위한 
		// 원소 w를 저장하기 위한 목적으로 사용한다.

		float arr1D[4];
		DirectX::XMFLOAT3 directXFloat3_;
		DirectX::XMFLOAT4 directXFloat4_;
		DirectX::XMVECTOR directXVector_;
	};


public:
	float4() : x(0.f), y(0.f), z(0.f), w(1.f)
	{
	}

	float4(float _value) : x(_value), y(_value), z(_value), w(1.f)
	{
	}

	float4(int _value) 
		: x(static_cast<float>(_value)),
		y(static_cast<float>(_value)),
		z(static_cast<float>(_value)),
		w(1.f)
	{
	}

	float4(const float4& _other) : x(_other.x), y(_other.y), z(_other.z), w(_other.w)
	{
	}

	float4(float4&& _other) noexcept : x(_other.x), y(_other.y), z(_other.z), w(_other.w)
	{
	}

	float4(int _x, int _y) : x(static_cast<float>(_x)), y(static_cast<float>(_y)), z(0.f), w(1.f)
	{
	}

	float4(float _x, float _y) : x(_x), y(_y), z(0.f), w(1.f)
	{
	}

	float4(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z), w(1.0f)
	{
	}

	float4(int _x, int _y, int _z)
		: x(static_cast<float>(_x)), y(static_cast<float>(_y)), z(static_cast<float>(_z)), w(1.0f)
	{
	}

	float4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w)
	{
	}

	float4(int _x, int _y, int _z, int _w) 
		: x(static_cast<float>(_x)),
		y(static_cast<float>(_y)),
		z(static_cast<float>(_z)),
		w(static_cast<float>(_w))
	{
	}

	float4(const DirectX::XMVECTOR& _vector): directXVector_(_vector)
	{
	}

	float4(const DirectX::XMFLOAT4& _float4): directXFloat4_(_float4)
	{
	}

	~float4()
	{
	}

public:
	//마이너스 연산자.
	float4 operator-() const
	{
		return DirectX::XMVectorNegate(this->directXVector_);
	}

	const float4& operator=(const float4& _other)
	{
		this->directXVector_ = _other.directXVector_;
		return *this;
	}

	float4 operator+(const float4& _other) const
	{
		return DirectX::XMVectorAdd(this->directXVector_, _other.directXVector_);
	}

	float4 operator-(const float4& _other) const
	{
		return DirectX::XMVectorSubtract(this->directXVector_, _other.directXVector_);
	}

	float4 operator*(const float4& _other) const
	{
		return DirectX::XMVectorMultiply(this->directXVector_, _other.directXVector_);
	}

	float4 operator/(const float4& _other) const
	{
		return DirectX::XMVectorDivide(this->directXVector_, _other.directXVector_);
	}

	const float4& operator+=(const float4& _other)
	{
		this->directXVector_ = DirectX::XMVectorAdd(
			this->directXVector_,
			_other.directXVector_
		);
		return *this;
	}

	const float4& operator-=(const float4& _other)
	{
		this->directXVector_ = DirectX::XMVectorSubtract(
			this->directXVector_,
			_other.directXVector_
		);
		return *this;
	}

	const float4& operator*=(const float4& _other)
	{
		this->directXVector_ = DirectX::XMVectorMultiply(
			this->directXVector_,
			_other.directXVector_
		);
		return *this;
	}

	const float4& operator/=(const float4& _other)
	{
		this->directXVector_ = DirectX::XMVectorDivide(
			this->directXVector_,
			_other.directXVector_
		);
		return *this;
	}

	float4 operator*(const float _value) const
	{
		return DirectX::XMVectorMultiply(
			this->directXVector_,
			DirectX::XMVECTOR({ _value, _value, _value, _value })
		);
	}

	float4 operator/(const float _value) const
	{
		return DirectX::XMVectorDivide(
			this->directXVector_,
			DirectX::XMVECTOR({ _value, _value, _value, _value })
		);
	}

	const float4& operator*=(const float _value)
	{
		this->directXVector_ = DirectX::XMVectorMultiply(
			this->directXVector_,
			DirectX::XMVECTOR({ _value, _value, _value, _value })
		);
		return *this;
	}

	const float4& operator/=(const float _value)
	{
		this->directXVector_ = DirectX::XMVectorDivide(
			this->directXVector_,
			DirectX::XMVECTOR({ _value, _value, _value, _value })
		);
		return *this;
	}

	bool operator==(const float4& _other) const
	{
		//return (this->x == _other.x && this->y == _other.y && this->z == _other.z);
		return fabsf(this->x - _other.x) <= FLT_EPSILON
			&& fabsf(this->y - _other.y) <= FLT_EPSILON
			&& fabsf(this->z - _other.z) <= FLT_EPSILON;
		//FLT_EPSILON: 1.192092896e-07F. float으로 표현할 수 있는 가장 작은 수 + 1.0f.
		//실수는 부동소수점 시스템 때문에 항상 약간의 오차가 발생하고, 그래서 일반적인 방식으로 대소를 비교해선 안되고,
		//두 숫자간 차이가 기준이 되는 일정 수치 이하일 때 같다고 표현하고, 그보다 크다면 다르다고 표현하는 방식을 써야 한다.
	}

	bool operator!=(const float4& _other) const
	{
		return fabsf(this->x - _other.x) > FLT_EPSILON 
			|| fabsf(this->y - _other.y) > FLT_EPSILON 
			|| fabsf(this->z - _other.z) > FLT_EPSILON;
		//FLT_EPSILON: 1.192092896e-07F. float으로 표현할 수 있는 가장 작은 수 + 1.0f.
		//실수는 부동소수점 시스템 때문에 항상 약간의 오차가 발생하고, 그래서 일반적인 방식으로 대소를 비교해선 안되고,
		//두 숫자간 차이가 기준이 되는 일정 수치 이하일 때 같다고 표현하고, 그보다 크다면 다르다고 표현하는 방식을 써야 한다.
	}

	float& operator[](int _index)
	{
		return arr1D[_index];
	}

	operator DirectX::XMFLOAT3() const
	{
		return directXFloat3_;
	}
	operator DirectX::XMFLOAT4() const
	{
		return directXFloat4_;
	}


public:

	float HX() const
	{
		return x * 0.5f;
	}
	float HY() const
	{
		return y * 0.5f;
	}
	float HZ() const
	{
		return z * 0.5f;
	}

	float4 Half() const
	{
		return { HX(), HY(), HZ() };
	}

	int IX() const
	{
		return static_cast<int>(x);
	}
	int IY() const
	{
		return static_cast<int>(y);
	}
	int IZ() const
	{
		return static_cast<int>(z);
	}
	int IW() const
	{
		return static_cast<int>(w);
	}

	unsigned int UIX() const
	{
		return static_cast<unsigned int>(x);
	}
	unsigned int UIY() const
	{
		return static_cast<unsigned int>(y);
	}
	unsigned int UIZ() const
	{
		return static_cast<unsigned int>(z);
	}

	int HIX() const
	{
		return static_cast<int>(x * 0.5f);
	}
	int HIY() const
	{
		return static_cast<int>(y * 0.5f);
	}
	int HIZ() const
	{
		return static_cast<int>(z * 0.5f);
	}

public:
	POINT ConvertToWindowsPoint()
	{
		return POINT(this->IX(), this->IY());
	}

	std::string ToString()
	{
		std::string value;
		value += "x : ";
		value += std::to_string(x);
		value += ", y : ";
		value += std::to_string(y);
		value += ", z : ";
		value += std::to_string(z);
		return value;
	}


public:
	//선형 보간(Linear Interpolation)
	static float4 Lerp(const float4& p1, const float4& p2, float _time)
	{
		return p1 * (1.0f - _time) + p2 * _time;
	}

	//구면 선형 보간(Spherical Linear Interpolation) 
	static float4 SLerpQuaternion(const float4& _left, const float4& _right, float _ratio)
	{
		if (1.0f <= _ratio)
		{
			_ratio = 1.0f;
		}

		return DirectX::XMQuaternionSlerp(_left.directXVector_, _right.directXVector_, _ratio);
	}

	static float4 DegreeToDirection2D(float _degree)
	{
		return RadianToDirection2D(_degree * GameEngineMath::DegreeToRadian);
	}
	
	static float4 RadianToDirection2D(float _radian)
	{
		return float4(
			cosf(_radian),	//빗변(거리)가 1일때의 밑변 길이 비율.
			sinf(_radian)	//빗변(거리)가 1일때의 높이 길이 비율.
		);
	}

	static float VectorXYToDegree(const float4& _thisPosition, const float4& _targetPosition)
	{
		return VectorXYToRadian(_thisPosition, _targetPosition) * GameEngineMath::RadianToDegree;
	}

	static float VectorXYToRadian(const float4& _thisPosition, const float4& _targetPosition)
	{
		return DirectX::XMVector2AngleBetweenVectors(
			_thisPosition.directXVector_,
			_targetPosition.directXVector_
		).m128_f32[0];
	}



public:

	float Length() const
	{
		return sqrtf((x * x) + (y * y) + (z * z));
	}

	//절대값 반환.
	float4 ABS3DReturn() const
	{
		return float4(fabsf(x), fabsf(y), fabsf(z));
	}

	//정규화: 벡터의 방향은 그대로 유지하면서 길이만 1로 줄이는 것.
	const float4& Normalize3D()
	{
		this->directXVector_ = DirectX::XMVector3Normalize(this->directXVector_);
		return *this;
	}

	//정규화: 벡터의 방향은 그대로 유지하면서 길이만 1로 줄이는 것.
	static float4 Normalize3DReturn(const float4& _vector)
	{
		return DirectX::XMVector3Normalize(_vector.directXVector_);
	}

	//벡터곱(Vector Product), 가위곱(Cross Product)
	static float4 CrossProduct3D(const float4& _vectorA, const float4& _vectorB)
	{
		return DirectX::XMVector3Cross(_vectorA.directXVector_, _vectorB.directXVector_);
	}

	//벡터곱(Vector Product), 가위곱(Cross Product)
	const float4& CrossProduct3D(const float4& _other)
	{
		this->directXVector_ = DirectX::XMVector3Cross(this->directXVector_, _other.directXVector_);
		return *this;
	}

	//스칼라곱(Scalar Product), 점곱(Dot Product)
	static float DotProduct3D(const float4& _vectorA, const float4& _vectorB)
	{
		return DirectX::XMVector3Dot(
			_vectorA.directXVector_,
			_vectorB.directXVector_
		).m128_f32[0];
	}

	//절대값 반환.
	static float4 ABS3DReturn(const float4& _position)
	{
		return _position.ABS3DReturn();
	}


	//Pitching: 좌우수평축 중심 회전. 여기서는 X축회전.
	//Yawing: 수직축 중심 회전. 여기서는 Y축회전. 
	//Rolling: 앞뒤수평축 중심 회전. 여기서는 Z축회전.
	//각 축이 향하는 방향은 엔진마다, 업계마다 얼마든지 달라 질 수 있으므로 각 회전이 무슨 축 중심인지 알아 둘 것.

	//라디안 3축 회전.
	const float4& RotateByRadians(float _radianX, float _radianY, float _radianZ)
	{
		this->directXVector_ = DirectX::XMVector3Rotate(
			this->directXVector_,
			DirectX::XMQuaternionRotationRollPitchYaw(
				_radianX, _radianY, _radianZ)
		);
		return *this;
	}
	//라디안 벡터 회전.
	const float4& RotateByRadians(const float4& _radianVector)
	{
		this->directXVector_ = DirectX::XMVector3Rotate(
			this->directXVector_,
			DirectX::XMQuaternionRotationRollPitchYawFromVector(
				_radianVector.directXVector_)
		);
		return *this;
	}
	//라디안 3축 회전.
	static float4 VectorRotationToRadian3Axis(const float4& _originVector, float _radianX, float _radianY, float _radianZ)
	{
		return DirectX::XMVector3Rotate(
			_originVector.directXVector_,
			DirectX::XMQuaternionRotationRollPitchYaw(
				_radianX, _radianY, _radianZ)
		);
	}
	//라디안 벡터 회전.
	static float4 VectorRotationToRadian3Axis(const float4& _originVector, const float4& _radianVector)
	{
		return DirectX::XMVector3Rotate(
			_originVector.directXVector_,
			DirectX::XMQuaternionRotationRollPitchYawFromVector(
				_radianVector.directXVector_)
		);
	}
	
	
	//60도법 3축 회전.
	const float4& RotateByDegreees(float _degreeX, float _degreeY, float _degreeZ)
	{
		this->directXVector_ = DirectX::XMVector3Rotate(
			this->directXVector_,
			DirectX::XMQuaternionRotationRollPitchYaw(
				_degreeX * GameEngineMath::DegreeToRadian,
				_degreeY * GameEngineMath::DegreeToRadian,
				_degreeZ * GameEngineMath::DegreeToRadian)
		);
		return *this;
	}
	//60도법 벡터 회전.
	const float4& RotateByDegrees(const float4& _degreeVector)
	{
		this->directXVector_ = DirectX::XMVector3Rotate(
			this->directXVector_,
			DirectX::XMQuaternionRotationRollPitchYawFromVector(
				(_degreeVector * GameEngineMath::DegreeToRadian).directXVector_)
		);
		return *this;
	}

	//60도법 3축 회전.
	static float4 VectorRotationToDegree3Axis(
		const float4& _originVector,
		float _degreeX, 
		float _degreeY,
		float _degreeZ
	)
	{
		return DirectX::XMVector3Rotate(
			_originVector.directXVector_,
			DirectX::XMQuaternionRotationRollPitchYaw(
				_degreeX * GameEngineMath::DegreeToRadian,
				_degreeY * GameEngineMath::DegreeToRadian,
				_degreeZ * GameEngineMath::DegreeToRadian)
		);
	}
	//60도법 벡터 회전.
	static float4 VectorRotationToDegree3Axis(const float4& _originVector, const float4& _degreeVector)
	{
		return DirectX::XMVector3Rotate(
			_originVector.directXVector_,
			DirectX::XMQuaternionRotationRollPitchYawFromVector(
				(_degreeVector * GameEngineMath::DegreeToRadian).directXVector_)
		);
	}

	float4 RadianVectorBetweenVectors(const float4& _targetVector)
	{
		return DirectX::XMVector3AngleBetweenVectors(
			this->directXVector_,
			_targetVector.directXVector_
		);
	}

	static float4 RadianVectorBetweenVectors(const float4& _originVector, const float4& _targetVector)
	{
		return DirectX::XMVector3AngleBetweenVectors(
			_originVector.directXVector_,
			_targetVector.directXVector_
		);
	}

	//이 벡터와 저 벡터를 잇는 벡터 생성.
	float4 DegreeVectorBetweenVectors(const float4& _targetVector)
	{
		return RadianVectorBetweenVectors(_targetVector) * GameEngineMath::RadianToDegree;
	}

	//두 벡터를 잇는 벡터 생성.
	static float4 DegreeVectorBetweenVectors(const float4& _originVector, const float4& _targetVector)
	{
		return RadianVectorBetweenVectors(_originVector, _targetVector) * GameEngineMath::RadianToDegree;
	}

	//60분법 회전 벡터를 쿼터니온으로 전환하는 함수. 
	float4 DegreeRotationToQuarternionReturn() const
	{
		return DirectX::XMQuaternionRotationRollPitchYawFromVector(
			(*this * GameEngineMath::DegreeToRadian).directXVector_
		);
	}

	//회전행렬->쿼터니온벡터.
	static float4 MatrixToQuarternion(const class float4x4& _matrix);

	//제곱근의 역수(1/_value^(1/2))
	static float InvSqrt(float _value)
	{
		const __m128 fOneHalf = _mm_set_ss(0.5f);
		__m128 Y0, X0, X1, X2, FOver2;
		float temp;

		Y0 = _mm_set_ss(_value);
		X0 = _mm_rsqrt_ss(Y0);	// 1/sqrt estimate (12 bits)
		FOver2 = _mm_mul_ss(Y0, fOneHalf);

		// 1st Newton-Raphson iteration
		X1 = _mm_mul_ss(X0, X0);
		X1 = _mm_sub_ss(fOneHalf, _mm_mul_ss(FOver2, X1));
		X1 = _mm_add_ss(X0, _mm_mul_ss(X0, X1));

		// 2nd Newton-Raphson iteration
		X2 = _mm_mul_ss(X1, X1);
		X2 = _mm_sub_ss(fOneHalf, _mm_mul_ss(FOver2, X2));
		X2 = _mm_add_ss(X1, _mm_mul_ss(X1, X2));

		_mm_store_ss(&temp, X2);
		return temp;
	}

public:
	bool CompareInt2D(const float4& _value) const
	{
		return (this->IX() == _value.IX()) && (this->IY() == _value.IY());
	}

	bool CompareInt3D(const float4& _value) const
	{
		return (this->IX() == _value.IX())
			&& (this->IY() == _value.IY())
			&& (this->IZ() == _value.IZ());
	}

	bool CompareInt4D(const float4& _value) const
	{
		return (this->IX() == _value.IX())
			&& (this->IY() == _value.IY())
			&& (this->IZ() == _value.IZ())
			&& (this->IW() == _value.IW());
	}

	bool IsZero2D() const
	{
		return x == 0.f && y == 0.f;
	}

	bool IsZero3D() const
	{
		return x == 0.f && y == 0.f && z == 0.f;
	}

	bool IsNearlyZero() const
	{
		return fabsf(x) <= 1.e-4f && fabsf(y) <= 1.e-4f && fabsf(z) <= 1.e-4f;
	}

	UINT GetUINTColor() const
	{
		UINT color = 0;
		char* colorPtr = reinterpret_cast<char*>(&color);

		colorPtr[0] = static_cast<int>(x * 255.f);
		colorPtr[1] = static_cast<int>(y * 255.f);
		colorPtr[2] = static_cast<int>(z * 255.f);
		colorPtr[3] = static_cast<int>(w * 255.f);

		return color;
	}
};

class float4x4
{
public:
	//각각의 물체가 각각의 크기와 회전값을 가진 세상: 로컬스페이스.
	//로컬스페이스에 있는 물체를 우리가 원하는 대로 변형하고 위치시키고 인식한다: 월드스페이스.
	union
	{
		struct
		{
			float4 vectorX_;
			float4 vectorY_;
			float4 vectorZ_;
			float4 vectorW_;
		};

		float arr1D[16];
		float arr2D[4][4];
		float4 arrVector[4];

		DirectX::XMMATRIX directXMatrix_;
		DirectX::XMFLOAT4X4 directXFloat4x4_;
	};

	static const float4x4 ZeroMatrix;	//영행렬.

public:
	float4x4(): directXMatrix_(DirectX::XMMatrixIdentity())
	{
	}

	float4x4(
		const float4& _vectorX,
		const float4& _vectorY,
		const float4& _vectorZ,
		const float4& _vectorW
	):	vectorX_(_vectorX),
		vectorY_(_vectorY),
		vectorZ_(_vectorZ),
		vectorW_(_vectorW)
	{
	}

	float4x4(const float4x4& _other): directXMatrix_(_other.directXMatrix_)
	{
	}

	float4x4(const DirectX::XMMATRIX& _matrix) : directXMatrix_(_matrix)
	{
	}

	~float4x4()
	{
	}


public:
	float4x4 operator*(const float4x4& _other)
	{
		return DirectX::XMMatrixMultiply(this->directXMatrix_, _other.directXMatrix_);
	}

	float4x4& operator*=(const float4x4& _other)
	{
		this->directXMatrix_ *= _other.directXMatrix_;
		return *this;
	}

	float4x4& operator=(const float4x4& _other)
	{
		this->directXMatrix_ = _other.directXMatrix_;
		return *this;
	}



public:
	void ZeroCheck()
	{
		for (size_t i = 0; i < 16; i++)
		{
			if (arr1D[i] <= FLT_EPSILON)
			{
				arr1D[i] = 0.0f;
			}
		}
	}

	//항등행렬(Identity Matrix) 만들기 == 행렬 초기화.
	void Identity()
	{
		this->directXMatrix_ = DirectX::XMMatrixIdentity();
	}

	//전치행렬 만들기: 행렬의 행과 열을 바꾸는 작업.
	static float4x4 Transpose(const float4x4& _matrix)
	{
		return DirectX::XMMatrixTranspose(_matrix.directXMatrix_);
	}

	//전치행렬 만들기: 행렬의 행과 열을 바꾸는 작업.
	const float4x4& Transpose()
	{
		this->directXMatrix_ = DirectX::XMMatrixTranspose(this->directXMatrix_);
		return *this;
	}

	//크기, 회전, 이동 한번에 변환.
	static float4x4 Transformation(
		const float4& _scale,
		const float4& _rotationQuarternion,
		const float4& _position
	)
	{
		return DirectX::XMMatrixTransformation(
			float4::Zero.directXVector_,	//크기 조정 중심.
			float4::Zero.directXVector_,	//크기 조정 방향??
			_scale.directXVector_,			//크기 변화량.
			float4::Zero.directXVector_,	//회전 조정 중심.
			_rotationQuarternion.directXVector_,	//회전량.
			_position.directXVector_		//
		);
	}

	static float4x4 Affine(const float4& _scale, const float4& _rotationQuarternion, const float4& _position)
	{
		// _Rot.DirectVector 쿼터니온 입니다.
		return DirectX::XMMatrixAffineTransformation(
			_scale.directXVector_,
			float4::Zero.directXVector_,
			_rotationQuarternion.directXVector_,
			_position.directXVector_
		);
	}

	//행렬식 구하기.
	float Determinant() const
	{
		return DirectX::XMMatrixDeterminant(this->directXMatrix_).m128_f32[0];
	}

	//행렬식 구하기.
	static float Determinant(const float4x4& _matrix)
	{
		return DirectX::XMMatrixDeterminant(_matrix.directXMatrix_).m128_f32[0];
	}

	//자기자신 역행렬 연산.
	void Inverse()
	{
		float4 determinantVector = DirectX::XMMatrixDeterminant(this->directXMatrix_);

		this->directXMatrix_ = DirectX::XMMatrixInverse(	//역행렬 구하는 함수. 
			&determinantVector.directXVector_,	//대상 행렬의 행렬식.
			this->directXMatrix_							//역행렬을 구할 대상 행렬.
		);								//행렬식이 0이라서 역행렬이 없거나 무한개라면 무한행렬을 반환한다.
	}

	//입력된 행렬의 역행렬 반환.
	static float4x4 InverseReturn(const float4x4& _matrix)
	{
		float4 determinantVector = DirectX::XMMatrixDeterminant(_matrix.directXMatrix_);

		float4x4 invertedMatrix = DirectX::XMMatrixInverse(
			&determinantVector.directXVector_,	//대상 행렬의 행렬식.
			_matrix.directXMatrix_					//역행렬을 구할 대상 행렬.
		);								//행렬식이 0이라서 역행렬이 없거나 무한개라면 무한행렬을 반환한다.
		return invertedMatrix;
	}

	//자기 자신의 역행렬 반환.
	float4x4 InverseReturn()
	{
		float4 determinantVector = DirectX::XMMatrixDeterminant(this->directXMatrix_);

		float4x4 invertedMatrix = DirectX::XMMatrixInverse(
			&determinantVector.directXVector_,	//대상 행렬의 행렬식.
			this->directXMatrix_					//역행렬을 구할 대상 행렬.
		);								//행렬식이 0이라서 역행렬이 없거나 무한개라면 무한행렬을 반환한다.
		return invertedMatrix;
	}

	//뷰스페이스 컬링 판정.
	static bool IsInViewFrustum(const float4x4& _wvpMatrix, const float4& _pivotPos)
	{
		//너비높이 1씩인 기본 Rect만 고려하였음.
		//Fullrect처럼 너비높이나 모양이 다르면 다시 만들 것. 
		float4 leftTop = float4(-0.5f + _pivotPos.x, -0.5f + _pivotPos.y);
		float4 rightTop = float4(0.5f + _pivotPos.x, -0.5f + _pivotPos.y);
		float4 leftBot = float4(-0.5f + _pivotPos.x, 0.5f + _pivotPos.y);
		float4 rightBot = float4(0.5f + _pivotPos.x, 0.5f + _pivotPos.y);

		leftTop = DirectX::XMVector4Transform(leftTop.directXVector_, _wvpMatrix.directXMatrix_);
		leftTop /= leftTop.w;
		rightTop = DirectX::XMVector4Transform(rightTop.directXVector_, _wvpMatrix.directXMatrix_);
		rightTop /= rightTop.w;
		leftBot = DirectX::XMVector4Transform(leftBot.directXVector_, _wvpMatrix.directXMatrix_);
		leftBot /= leftBot.w;
		rightBot = DirectX::XMVector4Transform(rightBot.directXVector_, _wvpMatrix.directXMatrix_);
		rightBot /= rightBot.w;

		return DirectX::XMVector2InBounds(leftTop.directXVector_, DirectX::g_XMOne3)
			|| DirectX::XMVector2InBounds(rightTop.directXVector_, DirectX::g_XMOne3)
			|| DirectX::XMVector2InBounds(leftBot.directXVector_, DirectX::g_XMOne3)
			|| DirectX::XMVector2InBounds(rightBot.directXVector_, DirectX::g_XMOne3);
	}

	//크기 변환.
	const float4x4& Scale(const float4& _scaleVector)
	{
		this->directXMatrix_ = DirectX::XMMatrixScalingFromVector(_scaleVector.directXVector_);
		return *this;
	}
	//크기 변환.
	const float4x4& Scale(float _scaleX, float _scaleY, float _scaleZ)
	{
		this->directXMatrix_ = DirectX::XMMatrixScaling(_scaleX, _scaleY, _scaleZ);
		return *this;
	}

	//라디안 벡터 회전.
	const float4x4& Rotate3AxisByRadian(const float4& _radianVector)
	{
		this->directXMatrix_ = DirectX::XMMatrixRotationRollPitchYawFromVector(
			_radianVector.directXVector_);
		return *this;
	}
	//라디안 3축 회전.
	const float4x4& Rotate3AxisByRadian(float _radianX, float _radianY, float _radianZ)
	{
		this->directXMatrix_ = DirectX::XMMatrixRotationRollPitchYaw(
			_radianX,
			_radianY,
			_radianZ
		);
		return *this;
	}

	//60도법 벡터 회전.
	const float4x4& Rotate3AxisByDegree(const float4& _degreeVector)
	{
		this->directXMatrix_ = DirectX::XMMatrixRotationRollPitchYawFromVector(
			(_degreeVector * GameEngineMath::DegreeToRadian).directXVector_
		);
		return *this;
	}
	//60도법 3축 회전.
	const float4x4& Rotate3AxisByDegree(float _degreeX, float _degreeY, float _degreeZ)
	{
		this->directXMatrix_ = DirectX::XMMatrixRotationRollPitchYaw(
			_degreeX * GameEngineMath::DegreeToRadian,
			_degreeY * GameEngineMath::DegreeToRadian,
			_degreeZ * GameEngineMath::DegreeToRadian
		);
		return *this;
	}

	//위치 이동.
	const float4x4& Position(const float4& _position)
	{
		this->directXMatrix_ = DirectX::XMMatrixTranslationFromVector(
			_position.directXVector_
		);
		return *this;
	}
	//위치 이동.
	const float4x4& Position(float _positionX, float _positionY, float _positionZ)
	{
		this->directXMatrix_ = DirectX::XMMatrixTranslation(
			_positionX,
			_positionY,
			_positionZ
		);
		return *this;
	}

	//행렬에서 크기만 벡터로 추출.
	//추출된 행렬의 크기는 1이 된다.
	float4 ExtractScaling()
	{
		float4 returnVector = float4::Zero;

		float Tolerance = 1.e-8f;	//허용 오차 범위.

		const float SquareSum0 = (arr2D[0][0] * arr2D[0][0]) + (arr2D[0][1] * arr2D[0][1]) + (arr2D[0][2] * arr2D[0][2]);
		const float SquareSum1 = (arr2D[1][0] * arr2D[1][0]) + (arr2D[1][1] * arr2D[1][1]) + (arr2D[1][2] * arr2D[1][2]);
		const float SquareSum2 = (arr2D[2][0] * arr2D[2][0]) + (arr2D[2][1] * arr2D[2][1]) + (arr2D[2][2] * arr2D[2][2]);

		if (SquareSum0 > Tolerance)
		{
			float Scale0 = sqrtf(SquareSum0);
			returnVector.x = Scale0;
			float InvScale0 = 1.f / Scale0;
			arr2D[0][0] *= InvScale0;
			arr2D[0][1] *= InvScale0;
			arr2D[0][2] *= InvScale0;
		}
		else
		{
			returnVector.x = 0;
		}

		if (SquareSum1 > Tolerance)
		{
			float Scale1 = sqrtf(SquareSum1);
			returnVector.y = Scale1;
			float InvScale1 = 1.f / Scale1;
			arr2D[1][0] *= InvScale1;
			arr2D[1][1] *= InvScale1;
			arr2D[1][2] *= InvScale1;
		}
		else
		{
			returnVector.y = 0;
		}

		if (SquareSum2 > Tolerance)
		{
			float Scale2 = sqrtf(SquareSum2);
			returnVector.z = Scale2;
			float InvScale2 = 1.f / Scale2;
			arr2D[2][0] *= InvScale2;
			arr2D[2][1] *= InvScale2;
			arr2D[2][2] *= InvScale2;
		}
		else
		{
			returnVector.z = 0;
		}

		return returnVector;
	}

	const float4x4& LookAtLH(const float4& _eyePosition, const float4& _focusPosition, const float4& _upDirection)
	{
		this->directXMatrix_ = DirectX::XMMatrixLookAtLH(	//특정 '지점'을 바라보는 뷰행렬을 계산해 반환하는 함수. 
			_eyePosition.directXVector_,
			_focusPosition.directXVector_,
			_upDirection.directXVector_
		);
		return *this;
		//왼손좌표계(Left-Handed Coordinate System): ++Z 방향이 내게서 멀어져서 화면 안으로 더 깊이 들어가는 것처럼 보이는 좌표계.
		//왼손좌표계 회전방향은 각 축 기준 시계방향이다.
		//오른손좌표계(Right-Handed Coordinate System): ++Z 방향이 내게로 더 가까워져서 화면 밖으로 나오려는 것처럼 보이는 좌표계.
		//오른손좌표계 회전방향은 각 축기준 반시계방향이다.
	}

	const float4x4& LookToLH(const float4& _eyePosition, const float4& _eyeDirection, const float4& _upDirection)
	{
		this->directXMatrix_ = DirectX::XMMatrixLookToLH(	//특정 '방향'을 바라보는 뷰행렬을 계산해 반환하는 함수. 
			_eyePosition.directXVector_,
			_eyeDirection.directXVector_,
			_upDirection.directXVector_
		);
		return *this;

		// 길이가 1인 벡터 2개를 외적하면 무조건 길이 1짜리 벡터가 나온다.
		//float4 R1 = float4::Cross(R2, R0);

		// 90 => ~90도 하려면 회전행렬을 전치하면 된다.
	}

	void ProjectOrthographicLH(
		float _width,
		float _height,
		float _nearZ,
		float _farZ
	)
	{
		this->directXMatrix_ = DirectX::XMMatrixOrthographicLH(
			_width,		//뷰스페이스의 가로길이. 직교투영이므로 원평면이든 근평면이든 똑같은 값이다.
			_height,	//뷰스페이스의 세로길이. 직교투영이므로 원평면이든 근평면이든 똑같은 값이다.
			_nearZ, 
			//카메라가 있는 지점(원근 중심)에서부터 모니터가 있는 가상의 지점(near clipping plane, 근평면)까지의 z축 길이.
			_farZ
			//카메라가 있는 지점(원근 중심)에서부터 뷰 프러스텀 밑바닥(far clipping plane, 원평면)까지의 z축 길이.
		);
	}

	void ProjectPerspectiveFovLH(
		float _fovRadianY,		
		float _aspectRatio,
		float _nearZ,
		float _farZ
	)
	{
		this->directXMatrix_ = DirectX::XMMatrixPerspectiveFovLH(
			_fovRadianY,	//FoV(Field of View): 화각, 시야 범위. Y이므로 세로길이를 형성하는 각도.
			_aspectRatio,	//AspectRatio: 뷰 프러스텀의 절단면 종횡비. 세로길이 / 가로길이. 
			_nearZ,			
			//카메라가 있는 지점(원근 중심)에서부터 모니터가 있는 가상의 지점(near clipping plane, 근평면)까지의 z축 길이.
			_farZ
			//카메라가 있는 지점(원근 중심)에서부터 뷰 프러스텀 밑바닥(far clipping plane, 원평면)까지의 z축 길이.
		);

		//float    SinFov;
		//float    CosFov;
		//DirectX::XMScalarSinCos(&SinFov, &CosFov, 0.5f * _fovRadianY);

		//float Height = CosFov / SinFov;	// == (1 / TanFov). z값이 1인 지점의 뷰 프러스텀 세로길이의 절반. 
		//float Width = Height / _aspectRatio;	//종횡비로 계산한 z값이 1인 지점의 뷰 프러스텀 가로길이의 절반. 
		//float fRange = _farZ / (_farZ - _nearZ);


		//this->arr2D[0][0] = Width;
		//this->arr2D[0][1] = 0.0f;
		//this->arr2D[0][2] = 0.0f;
		//this->arr2D[0][3] = 0.0f;
	
		//this->arr2D[1][0] = 0.0f;
		//this->arr2D[1][1] = Height;
		//this->arr2D[1][2] = 0.0f;
		//this->arr2D[1][3] = 0.0f;

		//this->arr2D[2][0] = 0.0f;
		//this->arr2D[2][1] = 0.0f;
		//this->arr2D[2][2] = fRange;
		//this->arr2D[2][3] = 1.0f;	<-투영행렬의 결과값이 벡터의 w에 저장되서 wvp행렬 계산할 때 적용되는데, 
		// 이 원소가 1이 아니면 이상한값이 저장되고, 0이라면 아예 저장되지 않은 상태로 wvp행렬을 거치게 되어
		// 적절하게 축소되지 않은 상태로 뷰포트 행렬을 거쳐 화면을 뒤덮는 크기로 거대해진다.
		//그러므로 저 값은 반드시 1이어야 한다.

		//this->arr2D[3][0] = 0.0f;
		//this->arr2D[3][1] = 0.0f;
		//this->arr2D[3][2] = -fRange * _nearZ;
		//this->arr2D[3][3] = 0.0f;	<-투영행렬은 이동행렬이 아니라 크기변환행렬의 일종이므로 여기에 0이 들어간다.


	}


	void ProjectPerspectiveLH(
		float _nearZWidth,
		float _nearZHeight,
		float _nearZ,
		float _farZ
	)
	{

		this->directXMatrix_ = DirectX::XMMatrixPerspectiveLH(
			_nearZWidth,		//근평면의 x축 길이.
			_nearZHeight,	//근평면의 y축 길이.
			_nearZ,				
			//카메라가 있는 지점(원근 중심)에서부터 모니터가 있는 가상의 지점(near clipping plane, 근평면)까지의 z축 길이.
			_farZ				
			//카메라가 있는 지점(원근 중심)에서부터 뷰 프러스텀 밑바닥(far clipping plane, 원평면)까지의 z축 길이.
		);

		//float TwoNearZ = _nearZ + _nearZ;	//ViewWidth나 ViewHeight는 절반이 필요하므로 2로 나누어야 하지만
		//// 그 대신 분자로 올라가는 _nearZ를 두배해서 계산의 효율성을 증가시킨다.
		//float fRange = _farZ / (_farZ - _nearZ);
		//
		//this->arr2D[0][0] = TwoNearZ / _nearWidth;	//z값이 1일때의 뷰 프러스텀 가로길이의 절반을 구해 넣는다.
		//this->arr2D[0][1] = 0.0f;
		//this->arr2D[0][2] = 0.0f;
		//this->arr2D[0][3] = 0.0f;
		//
		//this->arr2D[1][0] = 0.0f;
		//this->arr2D[1][1] = TwoNearZ / _nearHeight;	//z값이 1일때의 뷰 프러스텀 세로길이의 절반을 구해 넣는다.
		//this->arr2D[1][2] = 0.0f;
		//this->arr2D[1][3] = 0.0f;
		//
		//this->arr2D[2][0] = 0.0f;
		//this->arr2D[2][1] = 0.0f;
		//this->arr2D[2][2] = fRange;
		//this->arr2D[2][3] = 1.0f;	<-투영행렬의 결과값이 벡터의 w에 저장되서 wvp행렬 계산할 때 적용되는데, 
		// 이 원소가 1이 아니면 이상한값이 저장되고, 0이라면 아예 저장되지 않은 상태로 wvp행렬을 거치게 되어
		// 적절하게 축소되지 않은 상태로 뷰포트 행렬을 거쳐 화면을 뒤덮는 크기로 거대해진다.
		//그러므로 저 값은 반드시 1이어야 한다.

		//this->arr2D[3][0] = 0.0f;
		//this->arr2D[3][1] = 0.0f;
		//this->arr2D[3][2] = -fRange * _nearZ;
		//this->arr2D[3][3] = 0.0f; <-투영행렬은 이동행렬이 아니라 크기변환행렬의 일종이므로 여기에 0이 들어간다.
	}

	void Viewport(
		float _width,
		float _height,
		float _left,
		float _right,
		float _minZ,
		float _maxZ
	)
	{
		//다이렉트X에서는 따로 뷰포트를 계산해주는 함수는 없고,
		// D3D11_VIEWPORT 구조체로 ID3D11DeviceContext::RSSetViewports()함수를 통해 
		// 원하는 렌더타겟에 뷰포트값 세팅을 해주면 래스터라이저 단계에서 적용된다.

		//this->arr2D[0][0] = _width * 0.5f;
		//this->arr2D[0][1] = 0.f;
		//this->arr2D[0][2] = 0.f;
		//this->arr2D[0][3] = 0.f;

		//this->arr2D[1][0] = 0.f;
		//this->arr2D[1][1] = -_height * 0.5f;
		//this->arr2D[1][2] = 0.f;
		//this->arr2D[1][3] = 0.f;

		//this->arr2D[2][0] = 0.f;
		//this->arr2D[2][1] = 0.f;
		//this->arr2D[2][2] = 0.5f;
		//this->arr2D[2][3] = 0.f;

		//this->arr2D[3][0] = _width * 0.5f + _left;
		//this->arr2D[3][1] = _height * 0.5f + _right;
		//this->arr2D[3][2] = 0.5f;
		//this->arr2D[3][3] = 1.f;

		this->arr2D[0][0] = _width * 0.5f;
		this->arr2D[0][1] = 0.f;
		this->arr2D[0][2] = 0.f;
		this->arr2D[0][3] = 0.f;

		this->arr2D[1][0] = 0.f;
		this->arr2D[1][1] = -_height * 0.5f;
		this->arr2D[1][2] = 0.f;
		this->arr2D[1][3] = 0.f;

		this->arr2D[2][0] = 0.f;
		this->arr2D[2][1] = 0.f;
		this->arr2D[2][2] = _maxZ - _minZ;
		this->arr2D[2][3] = 0.f;

		this->arr2D[3][0] = _width * 0.5f + _left;
		this->arr2D[3][1] = _height * 0.5f + _right;
		this->arr2D[3][2] = _minZ;
		this->arr2D[3][3] = 1.f;
	}
};

float4 operator*(const float4& _vector, const float4x4& _matrix);
float4& operator*=(float4& _vector, const float4x4& _matrix);
//float4 클래스에 float4x4 클래스를 전방선언하는게 귀찮아서 전역연산자 겹지정으로 처리.


struct GameEngineRect
{
	float4 pos_;
	float4 scale_;

public:

	GameEngineRect(): pos_(float4::Zero), scale_(float4::One)
	{
	}

	GameEngineRect(const float4& _pos, const float4& _scale)
		: pos_(_pos),
		scale_(_scale)
	{
	}

public:
	const float4& CenterLeftTopPoint() const
	{
		return { static_cast<float>(CenterLeft()), static_cast<float>(CenterTop()) };
	}

	const float4& CenterLeftBotPoint() const
	{
		return { static_cast<float>(CenterLeft()), static_cast<float>(CenterBot()) };
	}

	const float4& CenterRightTopPoint() const
	{
		return { static_cast<float>(CenterRight()), static_cast<float>(CenterTop()) };
	}

	const float4& CenterRightBotPoint() const
	{
		return { static_cast<float>(CenterRight()), static_cast<float>(CenterBot()) };
	}

	int CenterLeft() const
	{
		return pos_.IX() - scale_.HIX();
	}

	int CenterRight() const
	{
		return pos_.IX() + scale_.HIX();
	}

	int CenterTop() const
	{
		return pos_.IY() - scale_.HIY();
	}

	int CenterBot() const
	{
		return pos_.IY() + scale_.HIY();
	}

	bool OverLap(const GameEngineRect& _Other)
	{
		if (CenterBot() < _Other.CenterTop())
		{
			return false;
		}

		if (CenterTop() > _Other.CenterBot())
		{
			return false;
		}

		if (CenterRight() < _Other.CenterLeft())
		{
			return false;
		}

		if (CenterLeft() > _Other.CenterRight())
		{
			return false;
		}

		return true;
	}

public:

};