#pragma once

class GameEngineCamera;
class GameEngineTexture;
namespace GameEngineDebug
{
	//디버그 렌더용 렌더유닛 생성, 초기화.
	void Debug3DInitialize();

	//디버그 렌더링 관련 정보를 실제로 렌더링하는 함수.
	void Debug3DRender();

	//디버그 렌더용 렌더유닛 파괴.
	void Debug3DDestroy();


	//아래는 디버그 렌더링에 필요한 정보를 저장하는 함수들.

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
