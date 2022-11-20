#pragma once
#include "GameEngineDefaultRenderer.h"

enum class PivotMode
{
	Top,		//����߾�.
	Center,		//�߽�.
	Bot,		//�ϴ��߾�.
	Left,		//�����߾�.
	Right,		//�����߾�.
	LeftTop,	//�»��.
	RightTop,	//����.
	LeftBot,	//���ϴ�.
	RightBot,	//���ϴ�.
	Custom,		//��������.
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
};

class FrameAnimation_Desc
{
	//������ �ִϸ��̼� ������ �ʿ��� ���� ���������� ��Ƽ� ����, �����ϴ� Ŭ����.
public:
	std::string textureName_;

	bool isLoop_;		//true == �ִϸ��̼� ���ѹݺ�. false == 1ȸ�ݺ� �� �����������ӿ��� ����.
	float interval_;	//�����Ӱ� �ð�����. �⺻�� 0.1f

	UINT curFrame_;	//���� ������ �ε���.

	float frameTime_;//���������� ���� �ð�.

	std::vector<UINT> frames_;

	class GameEngineTextureRenderer* renderer_;

	FrameAnimation_Desc()
		: isLoop_(false),
		interval_(1.f),
		curFrame_(-1),
		frameTime_(0.f),
		renderer_(nullptr)
	{
	}

	FrameAnimation_Desc(const std::string& _textureName, UINT _start, UINT _end, float _interval, bool _isLoop = true)
		: textureName_(_textureName),
		isLoop_(_isLoop),
		interval_(_interval),
		curFrame_(_start),
		frameTime_(0.f),
		renderer_(nullptr)
	{
		for (UINT frameIndex = _start; frameIndex <= _end; frameIndex++)
		{
			frames_.push_back(frameIndex);
		}
	}

	FrameAnimation_Desc(const std::string& _textureName, const std::vector<UINT>& _frames, float _interval, bool _isLoop = true)
		: textureName_(_textureName),
		isLoop_(_isLoop),
		interval_(_interval),
		curFrame_(0),
		frames_(_frames),
		frameTime_(0.f),
		renderer_(nullptr)
	{
	}

	FrameAnimation_Desc(const std::string& _textureName, float _interval, bool _isLoop = true)
		: textureName_(_textureName),
		isLoop_(_isLoop),
		interval_(_interval),
		curFrame_(0),
		frameTime_(0.f),
		renderer_(nullptr)
	{
	}
};

class GameEngineFolderTexture;
class FrameAnimation
{
	//������ �ؽ��� �� �ִϸ��̼� ������ Ŭ����.

	friend class GameEngineTextureRenderer;
	//

	FrameAnimation_Desc info_;	//�ִϸ��̼� ������ �ʿ��� ������ ����.

	GameEngineTextureRenderer* parentRenderer_;	//�θ� ������.

	std::shared_ptr<GameEngineTexture> cutTexture_;			//���� �ؽ���.			
	std::shared_ptr<GameEngineFolderTexture> folderTexture_;	//�������� �ؽ��ĵ� ����.
	//�ΰ��� ���ÿ� ���Ǵ� ���� ����!

	bool bOnceStart_;
	bool bOnceEnd_;
	bool isPaused_;	//true: �Ͻ�����.

	std::function<void(const FrameAnimation_Desc&)> start_;		//�ִϸ��̼� ��� ���۽� ȣ��Ǵ� �Լ���.
	std::function<void(const FrameAnimation_Desc&)> frame_;		//�ִϸ��̼� ����� �� �����Ӹ��� ȣ��Ǵ� �Լ���.
	std::function<void(const FrameAnimation_Desc&, float)> time_;	//�ִϸ��̼� ����� ���� �ð� �Ŀ� ȣ��Ǵ� �Լ���.
	std::function<void(const FrameAnimation_Desc&)> end_;			//�ִϸ��̼� ��� ����� ȣ��Ǵ� �Լ���.

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
	//Ư�� �ؽ�ó�� �� �ؽ�ó�� ���� �ִϸ��̼��� �������ϴ� ������.

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
	void SetTexture(const std::string_view& _textureName);	//�����ؽ�ó��.
	void SetTexture(std::shared_ptr<GameEngineTexture> _texture);		//�����ؽ�ó��.
	void SetFolderTextureToIndex(const std::string_view& _textureName, UINT _index);
	void SetTexture(const std::string_view& _textureName, int _index);	//��Ʋ���ؽ�ó��.
	void SetTexture(std::shared_ptr<GameEngineTexture> _texture, int _index);		//��Ʋ���ؽ�ó��.

	void SetFrame(int _index);	//�ִϸ��̼��� Ư�� ������ ����.

	void SetPivot();
	void SetPivot(PivotMode _pivot);
	void SetPivotToVector(const float4& _localPos);

	//void SetSamplingMode_Point();
	////���Ͱ� D3D11_FILTER_MIN_MAG_MIP_POINT�� ���õ� ���÷� ���.

	//void SetSamplingMode_Linear();
	////���Ͱ� D3D11_FILTER_MIN_MAG_MIP_LINEAR�� ���õ� ���÷� ���.


	void CreateFrameAnimation_CutTexture(const std::string_view& _animationName, const FrameAnimation_Desc& _desc);
	void CreateFrameAnimation_FolderTexture(const std::string_view& _animationName, const FrameAnimation_Desc& _desc);

	void ChangeFrameAnimation(const std::string_view& _animationName, bool _isForcedChange = false);

	void ScaleToTexture();	//�ؽ�ó ũ�⿡ �޽� �������� �ڵ����� �����ִ� �Լ�.

	void ScaleToCutTexture(int _index);		//�߸� �ؽ�ó ũ�⿡ �޽� �������� �ڵ����� �����ִ� �Լ�.

	void CurAnimationReset();
	void CurAnimationSetStartPivotFrame(int _setFrame);	//�ִϸ��̼� �� ���� ���ϴ� ���������� �ű�� �Լ�.

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
			MsgBoxAssertString(std::string(_animationName) + ": �׷� �̸��� �ִϸ��̼��� �����ϴ�.");
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
			MsgBoxAssertString(std::string(_animationName) + ": �׷� �̸��� �ִϸ��̼��� �����ϴ�.");
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
			MsgBoxAssertString(std::string(_animationName) + ": �׷� �̸��� �ִϸ��̼��� �����ϴ�.");
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
			MsgBoxAssertString(std::string(_animationName) + ": �׷� �̸��� �ִϸ��̼��� �����ϴ�.");
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

	//�ؽ�ó�������� �ؽ�ó�� �׸��µ� �ʿ��� "TextureAtlas"������ ���������ΰ� 
	// PixelData, AtlasData �� ������۸� ����ϰ� AtlasData�� �ʱ�ȭ�ϴ� �Լ�.
	void SetTextureRendererSetting();
	//�ؽ�ó�������� �����Ҷ�, �ؽ�ó�������� Start()�Լ����� �� �Լ��� ȣ��Ǳ� ������ 
	// �ؽ�ó�������� �����Ҷ� Ʈ�������� �ؽ�ó ���� ���� �ٸ� ������ �ʿ����� �ʴ�.					 

private:
	void FrameDataReset();	//CurAnimationReset()�Լ��� ���� ������??

private:
	PivotMode pivotMode_;				//���� ������� �ؽ�ó�� ������ ������.
	std::shared_ptr<GameEngineTexture> currentTexture_;	//���� ������� �ؽ�ó.					

	std::map<std::string, FrameAnimation> allAnimations_;	//<-�� �ִϸ��̼��� �������� ����??
	FrameAnimation* currentAnimation_;

	ScaleMode scaleMode_;
	float scaleRatio_;

	PixelData pixelDataInst_;
	AtlasData atlasDataInst_;		//���� ������� �ؽ�ó���� �������Ǵ� ���� ������ �ؽ�ó�� �׸� �Ǻ� ������ ���� ����. 

};

