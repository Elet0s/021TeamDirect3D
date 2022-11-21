#include "PreCompile.h"
#include"Mouse.h"
#include "GlobalContentsValue.h"

Mouse::Mouse()
	:mouseRenderer(0)
	, mouseLevel(0)
	, mouseCollision_(0)
	, mousePosition(0)
{

}
Mouse::~Mouse()
{

}

void Mouse::Start()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistChildDirectory("ContentsResources");
	Dir.MoveToChild("ContentsResources");
	Dir.MoveToChild("UI");
	Dir.MoveToChild("MouseUI");

	std::vector<GameEngineFile> Shaders = Dir.GetAllFiles();
	for (size_t i = 0; i < Shaders.size(); i++)
	{
		GameEngineTexture::Load(Shaders[i].GetFullPath());

	}

	{
		mouseCollision_ = CreateComponent<GameEngineCollision>();
		mouseCollision_->SetDebugSetting(CollisionType::CT_OBB2D, float4::Black);
		mouseCollision_->GetTransform().SetLocalScale({ 64.0f, 64.0f, 1.0f });
		mouseCollision_->ChangeOrder(ObjectOrder::Mouse);
	}

	mouseRenderer = CreateComponent<GameEngineTextureRenderer>();
	mouseRenderer->GetTransform().SetLocalScale(64, 64, 100);
	mouseRenderer->ChangeCamera(CameraOrder::UICamera);
	mouseRenderer->SetTexture("CursorSprite.png");
}
void Mouse::Update(float _DeltaTime)
{
	GetCurPos();
	mouseRenderer->GetTransform().SetLocalPosition(GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().x+10.0f, GetLevel()->GetUICamera()->GetMouseWorldPositionToActor().y,-100.0f);
	mouseCollision_->GetTransform().SetLocalPosition(GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor().x + 10.0f, GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor().y, -100.0f);
}
void Mouse::End()
{

}