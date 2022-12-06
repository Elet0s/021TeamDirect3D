#pragma once

class FieldRenderingActor: public GameEngineActor
{
	//이 클래스의 존재 이유:
public:
	FieldRenderingActor();
	~FieldRenderingActor();

protected:
	FieldRenderingActor(const FieldRenderingActor& _other) = delete;
	FieldRenderingActor(FieldRenderingActor&& _other) noexcept = delete;

private:
	FieldRenderingActor& operator=(const FieldRenderingActor& _other) = delete;
	FieldRenderingActor& operator=(const FieldRenderingActor&& _other) = delete;


public:	
	void Start() override;
	void Update(float _deltaTime) override;
	void End() override;


private:
	const float tileSize_;		//타일텍스처 가로길이. 
	//정사각형이므로 한개로 충분하다.

	const float4 tileCount_;	//사용된 타일텍스처 가로세로 개수.


	GameEngineInstancingRenderer* tileRenderer_;



};

