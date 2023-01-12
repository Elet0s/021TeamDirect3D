#include "PreCompile.h"
#include "GameEngineTextureRenderer.h"
#include "GameEngineFolderTexture.h"

void FrameAnimation::Reset()
{
	info_.curframeTime_ = 0.f;
	info_.curFrame_ = 0;
	info_.playTime_ = 0.f;
}

void FrameAnimation::Update(float _deltaTime)
{
	if (false == isPaused_)
	{
		info_.curframeTime_ += _deltaTime;
		info_.playTime_ += _deltaTime;

		if (nullptr != time_)
		{
			this->time_(info_, _deltaTime);
		}

		if (false == bOnceStart_
			&& info_.curFrame_ == 0)
		{
			if (nullptr != start_)
			{
				this->start_(info_);
			}

			bOnceStart_ = true;
			bOnceEnd_ = false;
		}

		if (info_.interval_ <= info_.curframeTime_)
		{
			if (info_.curFrame_ == info_.frames_.size() - 1
				&& false == bOnceEnd_)
			{
				if (nullptr != end_)
				{
					end_(info_);
				}
				bOnceStart_ = false;
				bOnceEnd_ = true;
				return;
			}

			++info_.curFrame_;
			if (nullptr != frame_)
			{
				frame_(info_);
			}

			if (info_.curFrame_ >= info_.frames_.size())
			{
				if (true == info_.isLoop_)
				{
					info_.curFrame_ = 0;
				}
				else
				{
					info_.curFrame_ = static_cast<UINT>(info_.frames_.size() - 1);
				}
			}
			info_.curframeTime_ -= info_.interval_;
		}
	}

	if (nullptr != cutTexture_)
	{
		parentRenderer_->currentTexture_ = cutTexture_;
		parentRenderer_->SetTexture(cutTexture_, info_.frames_[info_.curFrame_]);
		parentRenderer_->SetPivot();

		if (0 != cutTexture_->GetCutCount())
		{
			if (ScaleMode::Image == parentRenderer_->scaleMode_)
			{
				parentRenderer_->ScaleToCutTexture(info_.frames_[info_.curFrame_]);
			}
		}
		else
		{
			if (ScaleMode::Image == parentRenderer_->scaleMode_)
			{
				parentRenderer_->ScaleToTexture();
			}
		}
	}
	else if (nullptr != folderTexture_)
	{
		parentRenderer_->ResetFrameData();
		parentRenderer_->currentTexture_ = folderTexture_->GetTexture(info_.frames_[info_.curFrame_]);
		parentRenderer_->SetTexture(folderTexture_->GetTexture(info_.frames_[info_.curFrame_]));
		parentRenderer_->SetPivot();

		if (ScaleMode::Image == parentRenderer_->scaleMode_)
		{
			parentRenderer_->ScaleToTexture();
		}
	}
	else
	{
		MsgBoxAssert("텍스쳐가 준비되지 않았습니다.");
		return;
	}
}

void FrameAnimation::PauseSwitch()
{
	isPaused_ = !isPaused_;
}

GameEngineTextureRenderer::GameEngineTextureRenderer()
	: currentTexture_(nullptr),
	currentAnimation_(nullptr),
	pivotMode_(PivotMode::Custom),
	scaleMode_(ScaleMode::Custom),
	scaleRatio_(1.f)
{
}

GameEngineTextureRenderer::~GameEngineTextureRenderer()
{
}

void GameEngineTextureRenderer::SetTexture(const std::string_view& _textureName)
{
	if (nullptr == GameEngineTexture::Find(_textureName))
	{
		MsgBoxAssertString(std::string(_textureName) + ": 그런 이름의 텍스처가 없습니다.");
		return;
	}

	this->currentTexture_ = this->GetShaderResourceHelper().SetTexture("Tex", _textureName);
}

void GameEngineTextureRenderer::SetTexture(std::shared_ptr<GameEngineTexture> _texture)
{
	if (nullptr == _texture)
	{
		MsgBoxAssert("텍스처가 없습니다.");
		return;
	}

	currentTexture_ = _texture;
	this->GetShaderResourceHelper().SetTexture("Tex", _texture);
}

void GameEngineTextureRenderer::SetFolderTextureToIndex(const std::string_view& _textureName, UINT _index)
{
	std::shared_ptr<GameEngineFolderTexture> folderTexture = GameEngineFolderTexture::Find(_textureName);
	if (nullptr == folderTexture)
	{
		MsgBoxAssertString(std::string(_textureName) + ": 그런 이름의 폴더 텍스처가 없습니다.");
		return;
	}

	SetTexture(folderTexture->GetTexture(_index));

	atlasDataInst_.frameData_.posX = 0.f;
	atlasDataInst_.frameData_.posY = 0.f;
	atlasDataInst_.frameData_.sizeX = 1.f;
	atlasDataInst_.frameData_.sizeY = 1.f;
}

void GameEngineTextureRenderer::SetTexture(const std::string_view& _textureName, int _index)
{
	this->SetTexture(_textureName);
	this->SetFrame(_index);
}

void GameEngineTextureRenderer::SetTexture(std::shared_ptr<GameEngineTexture> _texture, int _index)
{
	if (nullptr == _texture)
	{
		MsgBoxAssert("존재하지 않는 텍스쳐입니다.");
		return;
	}

	SetTexture(_texture);
	SetFrame(_index);
}

void GameEngineTextureRenderer::SetFrame(int _index)
{
	this->atlasDataInst_.frameData_ = currentTexture_->GetFrameData(_index);
}

void GameEngineTextureRenderer::SetPivot()
{
	SetPivot(pivotMode_);
}

void GameEngineTextureRenderer::SetPivot(PivotMode _pivot)
{
	switch (_pivot)
	{
	case PivotMode::Top:
		atlasDataInst_.pivotPos_ = float4(0.f, -0.5f, 0.f, 0.f);
		break;
	case PivotMode::Center:
		atlasDataInst_.pivotPos_ = float4::Zero;
		break;
	case PivotMode::Bot:
		atlasDataInst_.pivotPos_ = float4(0.f, 0.5f, 0.f, 0.f);
		break;
	case PivotMode::Left:
		atlasDataInst_.pivotPos_ = float4(0.5f, 0.f, 0.f, 0.f);
		break;
	case PivotMode::Right:
		atlasDataInst_.pivotPos_ = float4(-0.5f, 0.f, 0.f, 0.f);
		break;
	case PivotMode::LeftTop:
		atlasDataInst_.pivotPos_ = float4(0.5f, -0.5f, 0.f, 0.f);
		break;
	case PivotMode::RightTop:
		atlasDataInst_.pivotPos_ = float4(-0.5f, -0.5f, 0.f, 0.f);
		break;
	case PivotMode::LeftBot:
		atlasDataInst_.pivotPos_ = float4(0.5f, 0.5f, 0.f, 0.f);
		break;
	case PivotMode::RightBot:
		atlasDataInst_.pivotPos_ = float4(-0.5f, 0.5f, 0.f, 0.f);
		break;
	case PivotMode::Custom:
		//_pivot == Custom일때는 아무것도 하지 않는다.
		break;

	default:
		MsgBoxAssert("존재할 수 없는 피봇모드입니다.");
		return;
	}

	pivotMode_ = _pivot;
}

void GameEngineTextureRenderer::SetPivotToVector(const float4& _localPos)
{
	this->GetTransform().SetLocalPosition(_localPos);
}

void GameEngineTextureRenderer::CreateFrameAnimation_CutTexture(const std::string_view& _animationName, const FrameAnimation_Desc& _desc)
{
	std::string uppercaseAnimationName = GameEngineString::ToUpperReturn(_animationName);

	if (allAnimations_.end() != allAnimations_.find(uppercaseAnimationName))
	{
		MsgBoxAssertString(std::string(_animationName) + ": 같은 이름의 애니메이션이 이미 존재합니다.");
		return;
	}

	FrameAnimation& newAnimation = allAnimations_[uppercaseAnimationName];	//생성과 동시에 삽입.
	newAnimation.info_ = _desc;
	newAnimation.info_.parentRenderer_ = this;
	newAnimation.parentRenderer_ = this;
	newAnimation.cutTexture_ = GameEngineTexture::Find(newAnimation.info_.textureName_);
	newAnimation.folderTexture_ = nullptr;
}

void GameEngineTextureRenderer::CreateFrameAnimation_FolderTexture(const std::string_view& _animationName, const FrameAnimation_Desc& _desc)
{
	std::string uppercaseAnimationName = GameEngineString::ToUpperReturn(_animationName);

	if (allAnimations_.end() != allAnimations_.find(uppercaseAnimationName))
	{
		MsgBoxAssertString(std::string(_animationName) + ": 같은 이름의 애니메이션이 이미 존재합니다.");
		return;
	}

	FrameAnimation& newAnimation = allAnimations_[uppercaseAnimationName];	//생성과 동시에 삽입.
	newAnimation.info_ = _desc;
	newAnimation.info_.parentRenderer_ = this;
	newAnimation.parentRenderer_ = this;
	newAnimation.cutTexture_ = nullptr;
	newAnimation.folderTexture_ = GameEngineFolderTexture::Find(newAnimation.info_.textureName_);


	if (0 == newAnimation.info_.frames_.size())
	{
		for (UINT textureIndex = 0; textureIndex < newAnimation.folderTexture_->GetTextureCount();
			textureIndex++)
		{
			newAnimation.info_.frames_.push_back(textureIndex);
		}
	}
}

void GameEngineTextureRenderer::ChangeFrameAnimation(
	const std::string_view& _animationName, bool _isForcedChange /*= false*/)
{
	std::string uppercaseAnimationName = GameEngineString::ToUpperReturn(_animationName);

	if (allAnimations_.end() == allAnimations_.find(uppercaseAnimationName))
	{
		MsgBoxAssertString(std::string(_animationName) + ": 그런 이름의 애니메이션이 존재하지 않습니다.");
		return;
	}

	if (this->currentAnimation_ != &allAnimations_[uppercaseAnimationName] || true == _isForcedChange)
	{
		this->currentAnimation_ = &allAnimations_[uppercaseAnimationName];
		this->currentAnimation_->Reset();
		if (nullptr != currentAnimation_->cutTexture_)
		{
			SetTexture(
				currentAnimation_->cutTexture_,
				currentAnimation_->info_.frames_[currentAnimation_->info_.curFrame_]);
			if (ScaleMode::Image == this->scaleMode_)
			{
				ScaleToCutTexture(currentAnimation_->info_.curFrame_);
			}
		}
		else if (nullptr != currentAnimation_->folderTexture_)
		{
			SetTexture(
				currentAnimation_->folderTexture_->GetTexture(
					currentAnimation_->info_.frames_[currentAnimation_->info_.curFrame_]));
			if (ScaleMode::Image == this->scaleMode_)
			{
				ScaleToTexture();
			}
		}
		else
		{
			MsgBoxAssertString(std::string(_animationName) + ": 텍스처가 준비되지 않은 애니메이션입니다.");
			return;
		}
	}

}

void GameEngineTextureRenderer::ScaleToTexture()
{
	float4 scale = currentTexture_->GetScale();

	if (0 > this->GetTransform().GetLocalScale().x)
	{
		scale.x = -scale.x;
	}

	if (0 > this->GetTransform().GetLocalScale().y)
	{
		scale.y = -scale.y;
	}

	this->GetTransform().SetLocalScale(scale * scaleRatio_);
}

void GameEngineTextureRenderer::ScaleToCutTexture(int _index)
{
	float4 scale = currentTexture_->GetCutScale(_index);

	if (0 > this->GetTransform().GetLocalScale().x)
	{
		scale.x = -scale.x;
	}

	if (0 > this->GetTransform().GetLocalScale().y)
	{
		scale.y = -scale.y;
	}

	this->GetTransform().SetLocalScale(scale * scaleRatio_);
}

void GameEngineTextureRenderer::CurAnimationReset()
{
	currentAnimation_->Reset();
}

void GameEngineTextureRenderer::CurAnimationSetStartPivotFrame(int _setFrame)
{
	currentAnimation_->info_.curFrame_ = _setFrame;
}

void GameEngineTextureRenderer::CurAnimationPauseSwitch()
{
	currentAnimation_->PauseSwitch();
}

void GameEngineTextureRenderer::CurAnimationPauseOn()
{
	currentAnimation_->isPaused_ = true;
}

void GameEngineTextureRenderer::CurAnimationPauseOff()
{
	currentAnimation_->isPaused_ = false;
}

bool GameEngineTextureRenderer::IsCurAnimationPaused()
{
	return currentAnimation_->isPaused_;
}

std::shared_ptr<GameEngineTexture> GameEngineTextureRenderer::GetCurrentTexture() const
{
	return currentTexture_;
}

void GameEngineTextureRenderer::Initialize(const std::string_view& _materialName)
{
	this->SetMaterial(_materialName);

	atlasDataInst_.frameData_.posX = 0.f;
	atlasDataInst_.frameData_.posY = 0.f;
	atlasDataInst_.frameData_.sizeX = 1.f;
	atlasDataInst_.frameData_.sizeY = 1.f;
	atlasDataInst_.pivotPos_ = float4::Zero;

	this->GetShaderResourceHelper().SetConstantBuffer_Link("AtlasData", atlasDataInst_);
	this->GetShaderResourceHelper().SetConstantBuffer_Link("PixelData", pixelDataInst_);
}

void GameEngineTextureRenderer::Start()
{
	GameEngineDefaultRenderer::Start();

	GameEngineRenderer::PushRendererToMainCamera();

	this->Initialize("TextureAtlas");
}

void GameEngineTextureRenderer::Update(float _deltaTime)
{
	if (nullptr != this->currentAnimation_)
	{
		currentAnimation_->Update(_deltaTime);
	}
}

void GameEngineTextureRenderer::ResetFrameData()
{
	this->atlasDataInst_.frameData_.posX = 0.f;
	this->atlasDataInst_.frameData_.posY = 0.f;
	this->atlasDataInst_.frameData_.sizeX = 1.f;
	this->atlasDataInst_.frameData_.sizeY = 1.f;
}
