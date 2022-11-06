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
	//���� ������ ���� ������ �����ϱ� ���ؼ� �����Ҵ����� ����.

	GameEngineRenderUnit* debugTextureRenderUnit_;
	//���� ������ ���� ������ �����ϱ� ���ؼ� �����Ҵ����� ����.

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
		//debugRenderUnit_�� ���� ������ "Box" �޽��� "3DDebug" ���׸��� ���� ���ķ� ������Ų��.

		debugTextureRenderUnit_ = new GameEngineRenderUnit();
		debugTextureRenderUnit_->SetMesh("Rect");
		debugTextureRenderUnit_->SetMaterial("3DDebug");
		//debugTextureRenderUnit_�� ���� ������ "Rect" �޽��� "3DDebug" ���׸��� ���� ���ķ� ������Ų��.


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
			MsgBoxAssertString(_textureName + ": �׷� �̸��� �ؽ�ó�� �������� �ʽ��ϴ�.");
			return;
		}

		debugTransform.SetLocalScale(_scale);
		debugTransform.SetLocalRotation(_rotation);
		debugTransform.SetLocalPosition(_position);

		if (_scale.CompareInt2D(float4::Zero))	
			//ũ�� ������ �⺻���� float4::Zero���, ũ�⼳���� �� ������ ���� ������ �����ϰ� �ؽ�ó ��ü ũ��� �����Ѵ�. 
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
			MsgBoxAssert("�������� �ʴ� �ؽ�ó�Դϴ�.");
			return;
		}

		debugTransform.SetLocalScale(_scale);
		debugTransform.SetLocalRotation(_rotation);
		debugTransform.SetLocalPosition(_position);

		if (true ==_scale.CompareInt2D(float4::Zero))
			//ũ�� ������ �⺻���� float4::Zero���, ũ�⼳���� �� ������ ���� ������ �����ϰ� �ؽ�ó ��ü ũ��� �����Ѵ�. 
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