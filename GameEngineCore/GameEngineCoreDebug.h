#pragma once

class GameEngineCamera;
class GameEngineTexture;
namespace GameEngineDebug
{
	//����� ������ �������� ����, �ʱ�ȭ.
	void Debug3DInitialize();

	//����� ������ ���� ������ ������ �������ϴ� �Լ�.
	void Debug3DRender();

	//����� ������ �������� �ı�.
	void Debug3DDestroy();


	//�Ʒ��� ����� �������� �ʿ��� ������ �����ϴ� �Լ���.

	void DrawBox(const GameEngineTransform& _transform, const float4& _color);
	void DrawBox(const GameEngineTransform& _transform, std::shared_ptr<GameEngineCamera> _camera, const float4& _color);
	void DrawBox(const float4& _position, const float4& _scale, const float4& _rotation, const float4& _color);

	void DrawSphere(const GameEngineTransform& _transform, const float4& _color);
	void DrawSphere(const GameEngineTransform& _transform, std::shared_ptr<GameEngineCamera> _camera, const float4& _color);

	void DrawTexture(
		const std::string& _textureName,
		const float4& _position,
		const float4& _rotation = float4::Zero,
		const float4& _scale = float4::Zero);
	void DrawTexture(
		const std::string& _textureName,
		class std::shared_ptr<GameEngineCamera> _camera,
		const float4& _position,
		const float4& _rotation = float4::Zero,
		const float4& _scale = float4::Zero);

	void DrawTexture(
		std::shared_ptr<GameEngineTexture> _texture,
		const float4& _position,
		const float4& _rotation = float4::Zero,
		const float4& _scale = float4::Zero);
	void DrawTexture(
		std::shared_ptr<GameEngineTexture> _texture,
		std::shared_ptr<GameEngineCamera> _camera,
		const float4& _position,
		const float4& _rotation = float4::Zero,
		const float4& _scale = float4::Zero);



}
