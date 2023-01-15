#include "PreCompile.h"
#include "TitleActor.h"


TitleActor::TitleActor() 
{
}

TitleActor::~TitleActor() 
{
}

void TitleActor::Start()
{
	if (GameEngineInput::GetInst().IsExists("SPACE") == false)
	{
		GameEngineInput::GetInst().CreateKey("SPACE", VK_SPACE);
	}

	std::shared_ptr<GameEngineTextureRenderer> texture = CreateComponent<GameEngineTextureRenderer>();
	texture->SetTexture("Title.png");
	texture->ScaleToTexture();
}

void TitleActor::Update(float _deltaTime)
{
	if (GameEngineInput::GetInst().IsDown("SPACE") == true)
	{
		GEngine::ChangeLevel("worldMap");
	}
}

void TitleActor::End()
{

}

