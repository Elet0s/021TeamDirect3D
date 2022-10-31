#pragma once

class GameEngineMath
{
public:
	static const float PI;
	static const float PI2;
	static const float HalfPI;
	static const float DegreeToRadian;	//60�й�->ȣ����(0.017453...)
	static const float RadianToDegree;	//ȣ����->60�й�(57.29577...)


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

	//���� ����ϴ� ���� ������ �̸� ���������� ������ ȣ���ϴ� �������� �Ƴ� �� �ִ�.

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

	//�������Ͽ��� ����??
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

		//������ǥ��(Homogeneous Coordinates): n������ ������ n+1���� ��ǥ�� ��Ÿ���� ��ǥ���� �Ѵ�.
		//���������δ� ������ȯ, ���߿����� ����������ȯ�� ����� == ī�޶���ġ�κ����� ������ ����� ���� �����ϱ� ���� 
		// ���� w�� �����ϱ� ���� �������� ����Ѵ�.

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
	//���̳ʽ� ������.
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
		//FLT_EPSILON: 1.192092896e-07F. float���� ǥ���� �� �ִ� ���� ���� �� + 1.0f.
		//�Ǽ��� �ε��Ҽ��� �ý��� ������ �׻� �ణ�� ������ �߻��ϰ�, �׷��� �Ϲ����� ������� ��Ҹ� ���ؼ� �ȵǰ�,
		//�� ���ڰ� ���̰� ������ �Ǵ� ���� ��ġ ������ �� ���ٰ� ǥ���ϰ�, �׺��� ũ�ٸ� �ٸ��ٰ� ǥ���ϴ� ����� ��� �Ѵ�.
	}

	bool operator!=(const float4& _other) const
	{
		return fabsf(this->x - _other.x) > FLT_EPSILON 
			|| fabsf(this->y - _other.y) > FLT_EPSILON 
			|| fabsf(this->z - _other.z) > FLT_EPSILON;
		//FLT_EPSILON: 1.192092896e-07F. float���� ǥ���� �� �ִ� ���� ���� �� + 1.0f.
		//�Ǽ��� �ε��Ҽ��� �ý��� ������ �׻� �ణ�� ������ �߻��ϰ�, �׷��� �Ϲ����� ������� ��Ҹ� ���ؼ� �ȵǰ�,
		//�� ���ڰ� ���̰� ������ �Ǵ� ���� ��ġ ������ �� ���ٰ� ǥ���ϰ�, �׺��� ũ�ٸ� �ٸ��ٰ� ǥ���ϴ� ����� ��� �Ѵ�.
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
	static float4 Lerp(const float4& p1, const float4& p2, float _time)
	{
		return p1 * (1.0f - _time) + p2 * _time;
	}

	static float4 DegreeToDirection2D(float _degree)
	{
		return RadianToDirection2D(_degree * GameEngineMath::DegreeToRadian);
	}
	
	static float4 RadianToDirection2D(float _radian)
	{
		return float4(
			cosf(_radian),	//����(�Ÿ�)�� 1�϶��� �غ� ���� ����.
			sinf(_radian)	//����(�Ÿ�)�� 1�϶��� ���� ���� ����.
		);
	}

	static float VectorXYToDegree(const float4& _thisPosition, const float4& _targetPosition)
	{
		return VectorXYToRadian(_thisPosition, _targetPosition) * GameEngineMath::RadianToDegree;
	}

	static float VectorXYToRadian(const float4& _thisPosition, const float4& _targetPosition)
	{
		//float4 direction = _targetPosition - _thisPosition;
		//direction.Normalize();
	
		//float angle = acosf(direction.x);
		//if (_thisPosition.y > _targetPosition.y)
		//{
		//	angle = GameEngineMath::PI2 - angle;
		//}
	
		//return angle;
	
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

	float4 ABS3DReturn() const
	{
		return float4(fabsf(x), fabsf(y), fabsf(z));
	}

	//����ȭ: ������ ������ �״�� �����ϸ鼭 ���̸� 1�� ���̴� ��.
	const float4& Normalize3D()
	{
		this->directXVector_ = DirectX::XMVector3Normalize(this->directXVector_);
		return *this;
	}

	//����ȭ: ������ ������ �״�� �����ϸ鼭 ���̸� 1�� ���̴� ��.
	static float4 Normalize3DReturn(const float4& _vector)
	{
		return DirectX::XMVector3Normalize(_vector.directXVector_);
	}

	// ������ ���� �ִ°�
	// ���콺 Ŭ���� ȸ������ �˾Ƴ���.
	
	//���Ͱ�(Vector Product), ������(Cross Product)
	static float4 Cross(const float4& _vectorA, const float4& _vectorB)
	{
		return DirectX::XMVector3Cross(_vectorA.directXVector_, _vectorB.directXVector_);
	}

	//���Ͱ�(Vector Product), ������(Cross Product)
	const float4& Cross(const float4& _other)
	{
		this->directXVector_ = DirectX::XMVector3Cross(this->directXVector_, _other.directXVector_);
		return *this;
	}

	//��Į���(Scalar Product), ����(Dot Product)
	static float Dot(const float4& _vectorA, const float4& _vectorB)
	{
		return DirectX::XMVector3Dot(
			_vectorA.directXVector_,
			_vectorB.directXVector_
		).m128_f32[0];
	}

	static float4 ABS3DReturn(const float4& _position)
	{
		return _position.ABS3DReturn();
	}


	//Pitching: �¿������ �߽� ȸ��. ���⼭�� X��ȸ��.
	//Yawing: ������ �߽� ȸ��. ���⼭�� Y��ȸ��. 
	//Rolling: �յڼ����� �߽� ȸ��. ���⼭�� Z��ȸ��.
	//�� ���� ���ϴ� ������ ��������, ���踶�� �󸶵��� �޶� �� �� �����Ƿ� �� ȸ���� ���� �� �߽����� �˾� �� ��.

	//���� 3�� ȸ��.
	const float4& RotateByRadians(float _radianX, float _radianY, float _radianZ)
	{
		this->directXVector_ = DirectX::XMVector3Rotate(
			this->directXVector_,
			DirectX::XMQuaternionRotationRollPitchYaw(
				_radianX, _radianY, _radianZ)
		);
		return *this;
	}
	//���� ���� ȸ��.
	const float4& RotateByRadians(const float4& _radianVector)
	{
		this->directXVector_ = DirectX::XMVector3Rotate(
			this->directXVector_,
			DirectX::XMQuaternionRotationRollPitchYawFromVector(
				_radianVector.directXVector_)
		);
		return *this;
	}
	//���� 3�� ȸ��.
	static float4 VectorRotationToRadian3Axis(const float4& _originVector, float _radianX, float _radianY, float _radianZ)
	{
		return DirectX::XMVector3Rotate(
			_originVector.directXVector_,
			DirectX::XMQuaternionRotationRollPitchYaw(
				_radianX, _radianY, _radianZ)
		);
	}
	//���� ���� ȸ��.
	static float4 VectorRotationToRadian3Axis(const float4& _originVector, const float4& _radianVector)
	{
		return DirectX::XMVector3Rotate(
			_originVector.directXVector_,
			DirectX::XMQuaternionRotationRollPitchYawFromVector(
				_radianVector.directXVector_)
		);
	}
	
	
	//60���� 3�� ȸ��.
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
	//60���� ���� ȸ��.
	const float4& RotateByDegrees(const float4& _degreeVector)
	{
		this->directXVector_ = DirectX::XMVector3Rotate(
			this->directXVector_,
			DirectX::XMQuaternionRotationRollPitchYawFromVector(
				(_degreeVector * GameEngineMath::DegreeToRadian).directXVector_)
		);
		return *this;
	}

	//60���� 3�� ȸ��.
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
	//60���� ���� ȸ��.
	static float4 VectorRotationToDegree3Axis(const float4& _originVector, const float4& _degreeVector)
	{
		return DirectX::XMVector3Rotate(
			_originVector.directXVector_,
			DirectX::XMQuaternionRotationRollPitchYawFromVector(
				(_degreeVector * GameEngineMath::DegreeToRadian).directXVector_)
		);
	}

	//60�й� ���͸� ���ʹϿ����� ��ȯ�ϴ� �Լ�. 
	float4 DegreeRotationToQuarternionReturn() const
	{
		return DirectX::XMQuaternionRotationRollPitchYawFromVector(
			(*this * GameEngineMath::DegreeToRadian).directXVector_
		);
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
	//������ ��ü�� ������ ũ��� ȸ������ ���� ����: ���ý����̽�.
	//���ý����̽��� �ִ� ��ü�� �츮�� ���ϴ� ��� �����ϰ� ��ġ��Ű�� �ν��Ѵ�: ���彺���̽�.
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

	static const float4x4 ZeroMatrix;	//�����.

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

	//�׵����(Identity Matrix) ����� == ��� �ʱ�ȭ.
	void Identity()
	{
		this->directXMatrix_ = DirectX::XMMatrixIdentity();
	}

	//��ġ��� �����: ����� ��� ���� �ٲٴ� �۾�.
	static float4x4 Transpose(const float4x4& _matrix)
	{
		return DirectX::XMMatrixTranspose(_matrix.directXMatrix_);
	}

	//��ġ��� �����: ����� ��� ���� �ٲٴ� �۾�.
	const float4x4& Transpose()
	{
		this->directXMatrix_ = DirectX::XMMatrixTranspose(this->directXMatrix_);
		return *this;
	}

	//��Ľ� ���ϱ�.
	float Determinant()
	{
		return DirectX::XMMatrixDeterminant(this->directXMatrix_).m128_f32[0];
	}

	//��Ľ� ���ϱ�.
	static float Determinant(const float4x4 _matrix)
	{
		return DirectX::XMMatrixDeterminant(_matrix.directXMatrix_).m128_f32[0];
	}

	//�ڱ��ڽ� ����� ����.
	void Inverse()
	{
		float4 determinantVector = DirectX::XMMatrixDeterminant(this->directXMatrix_);

		this->directXMatrix_ = DirectX::XMMatrixInverse(	//����� ���ϴ� �Լ�. 
			&determinantVector.directXVector_,	//��� ����� ��Ľ�.
			this->directXMatrix_							//������� ���� ��� ���.
		);								//��Ľ��� 0�̶� ������� ���ų� ���Ѱ���� ��������� ��ȯ�Ѵ�.
	}

	//�Էµ� ����� ����� ��ȯ.
	static float4x4 InverseReturn(const float4x4& _matrix)
	{
		float4 determinantVector = DirectX::XMMatrixDeterminant(_matrix.directXMatrix_);


		float4x4 invertedMatrix = DirectX::XMMatrixInverse(
			&determinantVector.directXVector_,	//��� ����� ��Ľ�.
			_matrix.directXMatrix_					//������� ���� ��� ���.
		);								//��Ľ��� 0�̶� ������� ���ų� ���Ѱ���� ��������� ��ȯ�Ѵ�.
		return invertedMatrix;
	}

	//�ڱ� �ڽ��� ����� ��ȯ.
	float4x4 InverseReturn()
	{
		float4 determinantVector = DirectX::XMMatrixDeterminant(this->directXMatrix_);

		float4x4 invertedMatrix = DirectX::XMMatrixInverse(
			&determinantVector.directXVector_,	//��� ����� ��Ľ�.
			this->directXMatrix_					//������� ���� ��� ���.
		);								//��Ľ��� 0�̶� ������� ���ų� ���Ѱ���� ��������� ��ȯ�Ѵ�.
		return invertedMatrix;
	}

	//ũ�� ��ȯ.
	const float4x4& Scale(const float4& _scaleVector)
	{
		this->directXMatrix_ = DirectX::XMMatrixScalingFromVector(_scaleVector.directXVector_);
		return *this;
	}
	//ũ�� ��ȯ.
	const float4x4& Scale(float _scaleX, float _scaleY, float _scaleZ)
	{
		this->directXMatrix_ = DirectX::XMMatrixScaling(_scaleX, _scaleY, _scaleZ);
		return *this;
	}

	//���� ���� ȸ��.
	const float4x4& Rotate3AxisByRadian(const float4& _radianVector)
	{
		this->directXMatrix_ = DirectX::XMMatrixRotationRollPitchYawFromVector(
			_radianVector.directXVector_);
		return *this;
	}
	//���� 3�� ȸ��.
	const float4x4& Rotate3AxisByRadian(float _radianX, float _radianY, float _radianZ)
	{
		this->directXMatrix_ = DirectX::XMMatrixRotationRollPitchYaw(
			_radianX,
			_radianY,
			_radianZ
		);
		return *this;
	}

	//60���� ���� ȸ��.
	const float4x4& Rotate3AxisByDegree(const float4& _degreeVector)
	{
		this->directXMatrix_ = DirectX::XMMatrixRotationRollPitchYawFromVector(
			(_degreeVector * GameEngineMath::DegreeToRadian).directXVector_
		);
		return *this;
	}
	//60���� 3�� ȸ��.
	const float4x4& Rotate3AxisByDegree(float _degreeX, float _degreeY, float _degreeZ)
	{
		this->directXMatrix_ = DirectX::XMMatrixRotationRollPitchYaw(
			_degreeX * GameEngineMath::DegreeToRadian,
			_degreeY * GameEngineMath::DegreeToRadian,
			_degreeZ * GameEngineMath::DegreeToRadian
		);
		return *this;
	}

	//��ġ �̵�.
	const float4x4& Position(const float4& _position)
	{
		this->directXMatrix_ = DirectX::XMMatrixTranslationFromVector(
			_position.directXVector_
		);
		return *this;
	}
	//��ġ �̵�.
	const float4x4& Position(float _positionX, float _positionY, float _positionZ)
	{
		this->directXMatrix_ = DirectX::XMMatrixTranslation(
			_positionX,
			_positionY,
			_positionZ
		);
		return *this;
	}

	const float4x4& LookAtLH(const float4& _eyePosition, const float4& _focusPosition, const float4& _upDirection)
	{
		this->directXMatrix_ = DirectX::XMMatrixLookAtLH(	//Ư�� '����'�� �ٶ󺸴� ������� ����� ��ȯ�ϴ� �Լ�. 
			_eyePosition.directXVector_,
			_focusPosition.directXVector_,
			_upDirection.directXVector_
		);
		return *this;
		//�޼���ǥ��(Left-Handed Coordinate System): ++Z ������ ���Լ� �־����� ȭ�� ������ �� ���� ���� ��ó�� ���̴� ��ǥ��.
		//�޼���ǥ�� ȸ�������� �� �� ���� �ð�����̴�.
		//��������ǥ��(Right-Handed Coordinate System): ++Z ������ ���Է� �� ��������� ȭ�� ������ �������� ��ó�� ���̴� ��ǥ��.
		//��������ǥ�� ȸ�������� �� ����� �ݽð�����̴�.
	}

	const float4x4& LookToLH(const float4& _eyePosition, const float4& _eyeDirection, const float4& _upDirection)
	{
		this->directXMatrix_ = DirectX::XMMatrixLookToLH(	//Ư�� '����'�� �ٶ󺸴� ������� ����� ��ȯ�ϴ� �Լ�. 
			_eyePosition.directXVector_,
			_eyeDirection.directXVector_,
			_upDirection.directXVector_
		);
		return *this;

		// ���̰� 1�� ���� 2���� �����ϸ� ������ ���� 1¥�� ���Ͱ� ���´�.
		//float4 R1 = float4::Cross(R2, R0);

		// 90 => ~90�� �Ϸ��� ȸ������� ��ġ�ϸ� �ȴ�.
	}

	void ProjectOrthographicLH(
		float _width,
		float _height,
		float _nearZ,
		float _farZ
	)
	{
		this->directXMatrix_ = DirectX::XMMatrixOrthographicLH(
			_width,		//�佺���̽��� ���α���. ���������̹Ƿ� ������̵� ������̵� �Ȱ��� ���̴�.
			_height,	//�佺���̽��� ���α���. ���������̹Ƿ� ������̵� ������̵� �Ȱ��� ���̴�.
			_nearZ, 
			//ī�޶� �ִ� ����(���� �߽�)�������� ����Ͱ� �ִ� ������ ����(near clipping plane, �����)������ z�� ����.
			_farZ
			//ī�޶� �ִ� ����(���� �߽�)�������� �� �������� �عٴ�(far clipping plane, �����)������ z�� ����.
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
			_fovRadianY,	//FoV(Field of View): ȭ��, �þ� ����. Y�̹Ƿ� ���α��̸� �����ϴ� ����.
			_aspectRatio,	//AspectRatio: �� ���������� ���ܸ� ��Ⱦ��. ���α��� / ���α���. 
			_nearZ,			
			//ī�޶� �ִ� ����(���� �߽�)�������� ����Ͱ� �ִ� ������ ����(near clipping plane, �����)������ z�� ����.
			_farZ
			//ī�޶� �ִ� ����(���� �߽�)�������� �� �������� �عٴ�(far clipping plane, �����)������ z�� ����.
		);

		//float    SinFov;
		//float    CosFov;
		//DirectX::XMScalarSinCos(&SinFov, &CosFov, 0.5f * _fovRadianY);

		//float Height = CosFov / SinFov;	// == (1 / TanFov). z���� 1�� ������ �� �������� ���α����� ����. 
		//float Width = Height / _aspectRatio;	//��Ⱦ��� ����� z���� 1�� ������ �� �������� ���α����� ����. 
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
		//this->arr2D[2][3] = 1.0f;	<-��������� ������� ������ w�� ����Ǽ� wvp��� ����� �� ����Ǵµ�, 
		// �� ���Ұ� 1�� �ƴϸ� �̻��Ѱ��� ����ǰ�, 0�̶�� �ƿ� ������� ���� ���·� wvp����� ��ġ�� �Ǿ�
		// �����ϰ� ��ҵ��� ���� ���·� ����Ʈ ����� ���� ȭ���� �ڵ��� ũ��� �Ŵ�������.
		//�׷��Ƿ� �� ���� �ݵ�� 1�̾�� �Ѵ�.

		//this->arr2D[3][0] = 0.0f;
		//this->arr2D[3][1] = 0.0f;
		//this->arr2D[3][2] = -fRange * _nearZ;
		//this->arr2D[3][3] = 0.0f;	<-��������� �̵������ �ƴ϶� ũ�⺯ȯ����� �����̹Ƿ� ���⿡ 0�� ����.


	}


	void ProjectPerspectiveLH(
		float _nearZWidth,
		float _nearZHeight,
		float _nearZ,
		float _farZ
	)
	{

		this->directXMatrix_ = DirectX::XMMatrixPerspectiveLH(
			_nearZWidth,		//������� x�� ����.
			_nearZHeight,	//������� y�� ����.
			_nearZ,				
			//ī�޶� �ִ� ����(���� �߽�)�������� ����Ͱ� �ִ� ������ ����(near clipping plane, �����)������ z�� ����.
			_farZ				
			//ī�޶� �ִ� ����(���� �߽�)�������� �� �������� �عٴ�(far clipping plane, �����)������ z�� ����.
		);

		//float TwoNearZ = _nearZ + _nearZ;	//ViewWidth�� ViewHeight�� ������ �ʿ��ϹǷ� 2�� ������� ������
		//// �� ��� ���ڷ� �ö󰡴� _nearZ�� �ι��ؼ� ����� ȿ������ ������Ų��.
		//float fRange = _farZ / (_farZ - _nearZ);
		//
		//this->arr2D[0][0] = TwoNearZ / _nearWidth;	//z���� 1�϶��� �� �������� ���α����� ������ ���� �ִ´�.
		//this->arr2D[0][1] = 0.0f;
		//this->arr2D[0][2] = 0.0f;
		//this->arr2D[0][3] = 0.0f;
		//
		//this->arr2D[1][0] = 0.0f;
		//this->arr2D[1][1] = TwoNearZ / _nearHeight;	//z���� 1�϶��� �� �������� ���α����� ������ ���� �ִ´�.
		//this->arr2D[1][2] = 0.0f;
		//this->arr2D[1][3] = 0.0f;
		//
		//this->arr2D[2][0] = 0.0f;
		//this->arr2D[2][1] = 0.0f;
		//this->arr2D[2][2] = fRange;
		//this->arr2D[2][3] = 1.0f;	<-��������� ������� ������ w�� ����Ǽ� wvp��� ����� �� ����Ǵµ�, 
		// �� ���Ұ� 1�� �ƴϸ� �̻��Ѱ��� ����ǰ�, 0�̶�� �ƿ� ������� ���� ���·� wvp����� ��ġ�� �Ǿ�
		// �����ϰ� ��ҵ��� ���� ���·� ����Ʈ ����� ���� ȭ���� �ڵ��� ũ��� �Ŵ�������.
		//�׷��Ƿ� �� ���� �ݵ�� 1�̾�� �Ѵ�.

		//this->arr2D[3][0] = 0.0f;
		//this->arr2D[3][1] = 0.0f;
		//this->arr2D[3][2] = -fRange * _nearZ;
		//this->arr2D[3][3] = 0.0f; <-��������� �̵������ �ƴ϶� ũ�⺯ȯ����� �����̹Ƿ� ���⿡ 0�� ����.


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
		//���̷�ƮX������ ���� ����Ʈ�� ������ִ� �Լ��� ����,
		// D3D11_VIEWPORT ����ü�� ID3D11DeviceContext::RSSetViewports()�Լ��� ���� 
		// ���ϴ� ����Ÿ�ٿ� ����Ʈ�� ������ ���ָ� �����Ͷ����� �ܰ迡�� ����ȴ�.

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
		this->arr2D[2][2] = 0.5f;
		this->arr2D[2][3] = 0.f;

		this->arr2D[3][0] = _width * 0.5f + _left;
		this->arr2D[3][1] = _height * 0.5f + _right;
		this->arr2D[3][2] = 0.5f;
		this->arr2D[3][3] = 1.f;
			
	}

};

float4 operator*(const float4& _vector, const float4x4& _matrix);
float4& operator*=(float4& _vector, const float4x4& _matrix);
//float4 Ŭ������ float4x4 Ŭ������ ���漱���ϴ°� �����Ƽ� ���������� ���������� ó��.


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