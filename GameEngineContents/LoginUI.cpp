#include "PreCompile.h"
#include "LoginUI.h"
#include "Enums.h"


LoginUI::LoginUI(): uiRenderer_(nullptr)
{
}

LoginUI::~LoginUI()
{
}

void LoginUI::Start()
{
	uiRenderer_ = CreateComponent<GameEngineTextureRenderer>("UIRenderer");
	uiRenderer_->SetMesh("Rect");
	uiRenderer_->GetTransform().SetLocalScale(1280, 720, 100);
	uiRenderer_->GetTransform().SetLocalPosition(0, 0, 800);
	uiRenderer_->SetTexture("LoginBackground.png");
}

void LoginUI::Update(float _deltaTime)
{
}

void LoginUI::End()
{
} 

void LoginUI::OnEvent()
{
	int i = 0;
}
