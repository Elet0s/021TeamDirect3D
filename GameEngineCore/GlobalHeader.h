#pragma once

struct PixelData
{
	float4 mulColor_;
	float4 plusColor_;
	float4 slice_;

	PixelData() : mulColor_(float4::White), plusColor_(float4::Zero), slice_(float4::Zero)
	{
	}
};

struct AtlasData
{
	float4 frameData_;
	float4 pivotPos_;

	AtlasData()
		: frameData_(float4::Zero),
		pivotPos_(float4::Zero)
	{
	}

	AtlasData(const AtlasData& _other)
		: frameData_(_other.frameData_),
		pivotPos_(_other.pivotPos_)
	{
	}

	AtlasData(const float4& _frameData, const float4& _pivotPos)
		: frameData_(_frameData),
		pivotPos_(_pivotPos)
	{
	}

	AtlasData(float _posX, float _posY, float _sizeX, float _sizeY, float _pivotPosX, float _pivotPosY)
		: frameData_(_posX, _posY, _sizeX, _sizeY),
		pivotPos_(_pivotPosX, _pivotPosY, 0.f, 0.f)
	{
	}

	void SetData(const AtlasData& _data)
	{
		this->frameData_ = _data.frameData_;
		this->pivotPos_ = _data.pivotPos_;
	}

	void SetData(const float4& _frameData, const float4& _pivotPos)
	{
		this->frameData_ = _frameData;
		this->pivotPos_ = _pivotPos;
	}

	void SetData(float _posX, float _posY, float _sizeX, float _sizeY, float _pivotPosX, float _pivotPosY)
	{
		this->frameData_.posX = _posX;
		this->frameData_.posY = _posY;
		this->frameData_.sizeX = _sizeX;
		this->frameData_.sizeY = _sizeY;
		this->pivotPos_ = float4(_pivotPosX, _pivotPosY, 0.f, 0.f);
	}

	const AtlasData& GetData() const
	{
		return *this;
	}
};

struct RenderOption
{
	float deltaTime_ = 0.f;
	float sumDeltaTime_ = 0.f;
	int isAnimation_ = 0;
	int vertexInversion_ = 1;   //그림자용 정점 좌우 뒤집힘 표시 변수. 좌우 뒤집어야 하면 -1 대입.
	float pivotPosX_ = 0.f;     //피봇포스 X
	float pivotPosY_ = 0.f;     //피봇포스 Y
	float lightingRotationX_ = 0.f;  //조명 X축 각도. 
	float lightingRotationY_ = 0.f;  //조명 Y축 각도. 
};
