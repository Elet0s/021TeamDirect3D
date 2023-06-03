#include "PreCompile.h"
#include "EndActor.h"

EndActor::EndActor() 
{
}

EndActor::~EndActor() 
{
}

void EndActor::Start()
{
	if (GameEngineInput::GetInst().IsExists("SPACE") == false)
	{
		GameEngineInput::GetInst().CreateKey("SPACE", VK_SPACE);
	}

	GameEngineTextureRenderer* texture = CreateComponent<GameEngineTextureRenderer>();
	texture->SetTexture("End.png");
	texture->ScaleToTexture();
}

void EndActor::Update(float _deltaTime)
{
	if (GameEngineInput::GetInst().IsDown("SPACE") == true)
	{
		GameEngineWindow::GetInst().Off();
	}
}

void EndActor::End()
{
}

