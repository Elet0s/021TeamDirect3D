#include "PreCompile.h"
#include "GameEngineCoreDebug.h"
#include "GameEngineCore.h"
#include "GameEngineCamera.h"
#include "GameEngineMaterial.h"
#include "GameEngineShaderResourceHelper.h"
#include "GameEngineTexture.h"
#include "GameEngineRenderer.h"


namespace GameEngineDebug
{
	enum class DebugRenderType
	{
		Sphere,
		Box,
	};

	struct DebugInfo
	{
		int type_[4];
		float4 color_;

	public:
		DebugInfo(DebugRenderType _type, const float4& _color)
			: type_{ static_cast<int>(_type) },
			color_(_color)
		{
		}
	};

	struct DebugRenderData
	{
		DebugInfo info_;
		TransformData data_;
		GameEngineTexture* texture_;

		DebugRenderData(const DebugInfo& _info, const TransformData& _data, GameEngineTexture* _texture = nullptr)
			: info_(_info),
			data_(_data),
			texture_(_texture)
		{
		}
	};

	std::vector<DebugRenderData> debugData_ = std::vector<DebugRenderData>();
	GameEngineRenderUnit* debugRenderUnit_;
	//전역 변수의 생성 시점을 조절하기 위해서 동적할당으로 생성.

	GameEngineRenderUnit* debugTextureRenderUnit_;
	//전역 변수의 생성 시점을 조절하기 위해서 동적할당으로 생성.

	void GameEngineDebug::Debug3DInitialize()
	{
		static bool isOnce = false;

		if (true == isOnce)
		{
			return;
		}

		debugRenderUnit_ = new GameEngineRenderUnit();
		debugRenderUnit_->SetMesh("Box");
		debugRenderUnit_->SetMaterial("3DDebug");
		//debugRenderUnit_의 생성 시점을 "Box" 메쉬와 "3DDebug" 마테리얼 생성 이후로 지연시킨다.

		debugTextureRenderUnit_ = new GameEngineRenderUnit();
		debugTextureRenderUnit_->SetMesh("Rect");
		debugTextureRenderUnit_->SetMaterial("3DDebug");
		//debugTextureRenderUnit_의 생성 시점을 "Rect" 메쉬와 "3DDebug" 마테리얼 생성 이후로 지연시킨다.


		isOnce = true;
	}

	void GameEngineDebug::Debug3DRender()
	{
		for (size_t i = 0; i < debugData_.size(); i++)
		{
			if (nullptr == debugData_[i].texture_)
			{
				debugRenderUnit_->GetShaderResourceHelper().SetConstantBuffer_Link("TransformData", debugData_[i].data_);
				debugRenderUnit_->GetShaderResourceHelper().SetConstantBuffer_Link("DebugInfo", debugData_[i].info_);

				debugRenderUnit_->Render(GameEngineTime::GetDeltaTime());
			}
			else
			{
				debugTextureRenderUnit_->GetShaderResourceHelper().SetConstantBuffer_Link("TransformData", debugData_[i].data_);
				debugTextureRenderUnit_->GetShaderResourceHelper().SetConstantBuffer_Link("DebugInfo", debugData_[i].info_);
				debugTextureRenderUnit_->GetShaderResourceHelper().SetTexture("Tex", debugData_[i].texture_);

				debugTextureRenderUnit_->Render(GameEngineTime::GetDeltaTime());
			}
		}
		debugData_.clear();
	}

	void Debug3DDestroy()
	{
		if (nullptr != debugRenderUnit_)
		{
			delete debugRenderUnit_;
			debugRenderUnit_ = nullptr;
		}

		if (nullptr != debugTextureRenderUnit_)
		{
			delete debugTextureRenderUnit_;
			debugTextureRenderUnit_ = nullptr;
		}
	}

	void GameEngineDebug::DrawBox(const GameEngineTransform& _transform, const float4& _color)
	{
		DrawBox(_transform, GameEngineCore::GetCurrentLevel()->GetMainCamera(), _color);
	}

	void GameEngineDebug::DrawBox(const GameEngineTransform& _transform, GameEngineCamera* _camera, const float4& _color)
	{
		static GameEngineTransform debugTransform;

		debugTransform.Copy(_transform);
		debugTransform.SetViewMatrix(_camera->GetViewMatrix());
		debugTransform.SetProjectionMatrix(_camera->GetProjectionMatrix());
		debugTransform.CalculateWorldViewProjection();

		debugData_.push_back(
			DebugRenderData(
				DebugInfo(DebugRenderType::Box, _color),
				debugTransform.GetTransformData(),
				nullptr
			)
		);
	}

	void DrawBox(const float4& _position, const float4& _scale, const float4& _rotation, const float4& _color)
	{
		static GameEngineTransform debugTransform;
		debugTransform.SetLocalScale(_scale);
		debugTransform.SetLocalRotation(_rotation);
		debugTransform.SetLocalPosition(_position);
		debugData_.push_back(
			DebugRenderData(
				DebugInfo(DebugRenderType::Box, _color),
				debugTransform.GetTransformData(),
				nullptr
			)
		);
	}

	void GameEngineDebug::DrawSphere(const GameEngineTransform& _transform, const float4& _color)
	{
		DrawSphere(_transform, GameEngineCore::GetCurrentLevel()->GetMainCamera(), _color);
	}

	void GameEngineDebug::DrawSphere(const GameEngineTransform& _transform, GameEngineCamera* _camera, const float4& _color)
	{
		static GameEngineTransform debugTransform;

		debugTransform.Copy(_transform);
		debugTransform.SetViewMatrix(_camera->GetViewMatrix());
		debugTransform.SetProjectionMatrix(_camera->GetProjectionMatrix());
		debugTransform.CalculateWorldViewProjection();

		debugData_.push_back(
			DebugRenderData( 
				DebugInfo(DebugRenderType::Sphere, _color), 
				debugTransform.GetTransformData() 
			)
		);
	}

	void GameEngineDebug::DrawTexture(
		const std::string& _textureName,
		const float4& _position,
		const float4& _rotation /*= float4::Zero*/,
		const float4& _scale /*= float4::Zero*/
	)
	{
		DrawTexture(
			_textureName,
			GameEngineCore::GetCurrentLevel()->GetMainCamera(),
			_position,
			_rotation,
			_scale
		);
	}

	void GameEngineDebug::DrawTexture(
		const std::string& _textureName,
		GameEngineCamera* _camera, 
		const float4& _position,
		const float4& _rotation /*= float4::Zero*/,
		const float4& _scale /*= float4::Zero*/
	)
	{
		static GameEngineTransform debugTransform;

		GameEngineTexture* findTexture = GameEngineTexture::Find(_textureName);
		if (nullptr == findTexture)
		{
			MsgBoxAssertString(_textureName + ": 그런 이름의 텍스처가 존재하지 않습니다.");
			return;
		}

		debugTransform.SetLocalScale(_scale);
		debugTransform.SetLocalRotation(_rotation);
		debugTransform.SetLocalPosition(_position);

		if (_scale.CompareInt2D(float4::Zero))	
			//크기 설정이 기본값인 float4::Zero라면, 크기설정을 할 생각이 없는 것으로 생각하고 텍스처 자체 크기로 세팅한다. 
		{
			debugTransform.SetLocalScale(findTexture->GetScale());
		}

		debugTransform.SetViewMatrix(_camera->GetViewMatrix());
		debugTransform.SetProjectionMatrix(_camera->GetProjectionMatrix());
		debugTransform.CalculateWorldViewProjection();

		debugData_.push_back(
			DebugRenderData(
				DebugInfo(DebugRenderType::Box, float4::White),
				debugTransform.GetTransformData(),
				findTexture 
			)
		);
	}

	void GameEngineDebug::DrawTexture(
		GameEngineTexture* _texture,
		const float4& _position, 
		const float4& _rotation /*= float4::Zero*/,
		const float4& _scale /*= float4::Zero*/
	)
	{
		DrawTexture(
			_texture,
			GameEngineCore::GetCurrentLevel()->GetMainCamera(),
			_position,
			_rotation,
			_scale
		);
	}

	void GameEngineDebug::DrawTexture(
		GameEngineTexture* _texture,
		GameEngineCamera* _camera,
		const float4& _position,
		const float4& _rotation /*= float4::Zero*/,
		const float4& _scale /*= float4::Zero*/
	)
	{
		static GameEngineTransform debugTransform;

		if (nullptr == _texture)
		{
			MsgBoxAssert("존재하지 않는 텍스처입니다.");
			return;
		}

		debugTransform.SetLocalScale(_scale);
		debugTransform.SetLocalRotation(_rotation);
		debugTransform.SetLocalPosition(_position);

		if (true ==_scale.CompareInt2D(float4::Zero))
			//크기 설정이 기본값인 float4::Zero라면, 크기설정을 할 생각이 없는 것으로 생각하고 텍스처 자체 크기로 세팅한다. 
		{
			debugTransform.SetLocalScale(_texture->GetScale());
		}

		debugTransform.SetViewMatrix(_camera->GetViewMatrix());
		debugTransform.SetProjectionMatrix(_camera->GetProjectionMatrix());
		debugTransform.CalculateWorldViewProjection();

		debugData_.push_back(
			DebugRenderData(
				DebugInfo(DebugRenderType::Box, float4::White),
				debugTransform.GetTransformData(),
				_texture
			)
		);
	}
}