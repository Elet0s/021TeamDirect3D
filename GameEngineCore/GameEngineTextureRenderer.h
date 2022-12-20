#pragma once
#include "GameEngineDefaultRenderer.h"

enum class PivotMode
{
	Top,		//상단중앙.
	Center,		//중심.
	Bot,		//하단중앙.
	Left,		//좌측중앙.
	Right,		//우측중앙.
	LeftTop,	//좌상단.
	RightTop,	//우상단.
	LeftBot,	//좌하단.
	RightBot,	//우하단.
	Custom,		//임의지점.
	None
};

enum class ScaleMode
{
	Image,
	Custom,
};

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

class FrameAnimation_Desc
{
	//프레임 애니메이션 생성에 필요한 각종 상세정보들을 모아서 저장, 관리하는 클래스.
public:
	class GameEngineTextureRenderer* parentRenderer_;

	std::string textureName_;

	std::vector<UINT> frames_;	//재생할 프레임 번호 순서.

	UINT curFrame_;	//현재 프레임 인덱스.

	float curframeTime_;//현재프레임 지난 시간.

	float interval_;	//프레임간 시간간격.

	bool isLoop_;		//true == 애니메이션 무한반복. false == 1회반복 후 마지막프레임에서 정지.

	float playTime_;	//여태까지 애니메이션이 재생된 시간.

	FrameAnimation_Desc()
		: parentRenderer_(nullptr),
		curFrame_(0),
		curframeTime_(0.f),
		interval_(1.f),
		isLoop_(false),
		playTime_(0.f)
	{
	}

	FrameAnimation_Desc(const std::string_view& _textureName, UINT _start, UINT _end, float _interval, bool _isLoop = true)
		: parentRenderer_(nullptr),
		textureName_(_textureName),
		curFrame_(_start),
		curframeTime_(0.f),
		interval_(_interval),
		isLoop_(_isLoop),
		playTime_(0.f)
	{
		frames_.reserve(static_cast<size_t>(_end) - static_cast<size_t>(_start) + 1);
		for (UINT frameIndex = _start; frameIndex <= _end; ++frameIndex)
		{
			frames_.push_back(frameIndex);
		}
	}

	FrameAnimation_Desc(const std::string_view& _textureName, const std::vector<UINT>& _frames, float _interval, bool _isLoop = true)
		: parentRenderer_(nullptr),
		textureName_(_textureName),
		frames_(_frames),
		curFrame_(0),
		curframeTime_(0.f),
		interval_(_interval),
		isLoop_(_isLoop),
		playTime_(0.f)
	{
	}

	FrameAnimation_Desc(const std::string& _textureName, float _interval, bool _isLoop = true)
		: parentRenderer_(nullptr),
		textureName_(_textureName),
		curFrame_(0),
		curframeTime_(0.f),
		interval_(_interval),
		isLoop_(_isLoop),
		playTime_(0.f)
	{
	}
};

class GameEngineFolderTexture;
class FrameAnimation
{
	//프레임 텍스쳐 및 애니메이션 렌더링 클래스.

	friend class GameEngineTextureRenderer;
	//

	FrameAnimation_Desc info_;	//애니메이션 생성시 필요한 상세정보 모음.

	GameEngineTextureRenderer* parentRenderer_;	//부모 렌더러.

	std::shared_ptr<GameEngineTexture> cutTexture_;			//단일 텍스쳐.			
	std::shared_ptr<GameEngineFolderTexture> folderTexture_;	//폴더단위 텍스쳐들 모음.
	//두개가 동시에 사용되는 경우는 없음!

	bool bOnceStart_;
	bool bOnceEnd_;
	bool isPaused_;	//true: 일시정지.

	std::function<void(const FrameAnimation_Desc&)> start_;		//애니메이션 재생 시작시 호출되는 함수들.
	std::function<void(const FrameAnimation_Desc&)> frame_;		//애니메이션 재생중 매 프레임마다 호출되는 함수들.
	std::function<void(const FrameAnimation_Desc&, float)> time_;	//애니메이션 재생중 일정 시간 후에 호출되는 함수들.
	std::function<void(const FrameAnimation_Desc&)> end_;			//애니메이션 재생 종료시 호출되는 함수들.

	void Reset();
	void Update(float _deltaTime);
	void PauseSwitch();

public:
	FrameAnimation()
		: parentRenderer_(nullptr),
		cutTexture_(nullptr),
		folderTexture_(nullptr),
		bOnceStart_(false),
		bOnceEnd_(false),
		isPaused_(false)
	{
	}

};

class GameEngineTexture;
class GameEngineTextureRenderer : public GameEngineDefaultRenderer
{
	//특정 텍스처나 그 텍스처로 만든 애니메이션을 렌더링하는 렌더러.

	friend FrameAnimation;
	//


public:
	GameEngineTextureRenderer();
	~GameEngineTextureRenderer();

protected:
	GameEngineTextureRenderer(const GameEngineTextureRenderer& _other) = delete;
	GameEngineTextureRenderer(GameEngineTextureRenderer&& _other) noexcept = delete;

private:
	GameEngineTextureRenderer& operator=(const GameEngineTextureRenderer& _other) = delete;
	GameEngineTextureRenderer& operator=(const GameEngineTextureRenderer&& _other) = delete;


public:
	void SetTexture(const std::string_view& _textureName);	//폴더텍스처용.
	void SetTexture(std::shared_ptr<GameEngineTexture> _texture);		//폴더텍스처용.
	void SetFolderTextureToIndex(const std::string_view& _textureName, UINT _index);
	void SetTexture(const std::string_view& _textureName, int _index);	//아틀라스텍스처용.
	void SetTexture(std::shared_ptr<GameEngineTexture> _texture, int _index);		//아틀라스텍스처용.

	void SetFrame(int _index);	//애니메이션의 특정 프레임 지정.

	void SetPivot();
	void SetPivot(PivotMode _pivot);
	void SetPivotToVector(const float4& _localPos);


	void CreateFrameAnimation_CutTexture(const std::string_view& _animationName, const FrameAnimation_Desc& _desc);
	void CreateFrameAnimation_FolderTexture(const std::string_view& _animationName, const FrameAnimation_Desc& _desc);

	void ChangeFrameAnimation(const std::string_view& _animationName, bool _isForcedChange = false);

	void ScaleToTexture();	//텍스처 크기에 메쉬 스케일을 자동으로 맞춰주는 함수.

	void ScaleToCutTexture(int _index);		//잘린 텍스처 크기에 메쉬 스케일을 자동으로 맞춰주는 함수.

	void CurAnimationReset();
	void CurAnimationSetStartPivotFrame(int _setFrame);	//애니메이션 중 내가 원하는 프레임으로 옮기는 함수.

	void CurAnimationPauseSwitch();
	void CurAnimationPauseOn();
	void CurAnimationPauseOff();
	bool IsCurAnimationPaused();

	std::shared_ptr<GameEngineTexture> GetCurrentTexture() const;

public:

	void AnimationBindStart(
		const std::string_view& _animationName,
		std::function<void(const FrameAnimation_Desc&)> _function)
	{
		std::string uppercaseAnimationName = GameEngineString::ToUpperReturn(_animationName);

		if (allAnimations_.end() == allAnimations_.find(uppercaseAnimationName))
		{
			MsgBoxAssertString(std::string(_animationName) + ": 그런 이름의 애니메이션이 없습니다.");
			return;
		}

		allAnimations_[uppercaseAnimationName].start_ = _function;
	}

	void AnimationBindFrame(
		const std::string_view& _animationName,
		std::function<void(const FrameAnimation_Desc&)> _function)
	{
		std::string uppercaseAnimationName = GameEngineString::ToUpperReturn(_animationName);

		if (allAnimations_.end() == allAnimations_.find(uppercaseAnimationName))
		{
			MsgBoxAssertString(std::string(_animationName) + ": 그런 이름의 애니메이션이 없습니다.");
			return;
		}

		allAnimations_[uppercaseAnimationName].frame_ = _function;
	}

	void AnimationBindTime(
		const std::string_view& _animationName,
		std::function<void(const FrameAnimation_Desc&, float)> _function)
	{
		std::string uppercaseAnimationName = GameEngineString::ToUpperReturn(_animationName);

		if (allAnimations_.end() == allAnimations_.find(uppercaseAnimationName))
		{
			MsgBoxAssertString(std::string(_animationName) + ": 그런 이름의 애니메이션이 없습니다.");
			return;
		}

		allAnimations_[uppercaseAnimationName].time_ = _function;
	}

	void AnimationBindEnd(
		const std::string_view& _animationName,
		std::function<void(const FrameAnimation_Desc&)> _function)
	{
		std::string uppercaseAnimationName = GameEngineString::ToUpperReturn(_animationName);

		if (allAnimations_.end() == allAnimations_.find(uppercaseAnimationName))
		{
			MsgBoxAssertString(std::string(_animationName) + ": 그런 이름의 애니메이션이 없습니다.");
			return;
		}

		allAnimations_[uppercaseAnimationName].end_ = _function;
	}

	void SetScaleMode_Image()
	{
		scaleMode_ = ScaleMode::Image;
	}

	void SetScaleRatio(float _scale)
	{
		scaleRatio_ = _scale;
	}

	float GetScaleRatio()
	{
		return scaleRatio_;
	}

	PixelData& GetPixelData()
	{
		return pixelDataInst_;
	}
	
	AtlasData& GetAtlasData()
	{
		return atlasDataInst_;
	}

	bool IsCurAnimation()
	{
		return nullptr != currentAnimation_;
	}

protected:
	void Start() override;
	void Update(float _deltaTime) override;

	//텍스처렌더러가 텍스처를 그리는데 필요한 "TextureAtlas"렌더링 파이프라인과 
	// PixelData, AtlasData 두 상수버퍼를 등록하고 AtlasData를 초기화하는 함수.
	void SetTextureRendererSetting();
	//텍스처렌더러를 생성할때, 텍스처렌더러의 Start()함수에서 이 함수가 호출되기 때문에 
	// 텍스처렌더러를 생성할때 트랜스폼과 텍스처 지정 외의 다른 절차가 필요하지 않다.					 

private:
	void FrameDataReset();	//CurAnimationReset()함수와 무슨 차이지??

private:
	PivotMode pivotMode_;				//현재 사용중인 텍스처의 렌더링 기준점.
	std::shared_ptr<GameEngineTexture> currentTexture_;	//현재 사용중인 텍스처.					

	std::map<std::string, FrameAnimation> allAnimations_;	//<-왜 애니메이션을 값형으로 저장??
	FrameAnimation* currentAnimation_;

	ScaleMode scaleMode_;
	float scaleRatio_;

	PixelData pixelDataInst_;
	AtlasData atlasDataInst_;		//현재 사용중인 텍스처에서 렌더링되는 범위 정보와 텍스처를 그릴 피봇 정보를 가진 변수. 

};

