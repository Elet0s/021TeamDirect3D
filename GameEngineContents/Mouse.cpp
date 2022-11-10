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
	Dir.MoveToChild("Actor");
	Dir.MoveToChild("Mouse");

	std::vector<GameEngineFile> Shaders = Dir.GetAllFiles();
	for (size_t i = 0; i < Shaders.size(); i++)
	{
		GameEngineTexture::Load(Shaders[i].GetFullPath());

	}

	{
		mouseCollision_ = CreateComponent<GameEngineCollision>();
		mouseCollision_->GetTransform().SetLocalScale({ 64.0f, 64.0f, 64.0f });
		mouseCollision_->ChangeOrder(ObjectOrder::Mouse);
	}

	mouseRenderer = CreateComponent<GameEngineTextureRenderer>();
	mouseRenderer->GetTransform().SetLocalScale(64, 64, -100);
	//mouseRenderer->ChangeCamera(CameraOrder::UICamera);
	mouseRenderer->SetTexture("Cursor.png");
}
void Mouse::Update(float _DeltaTime)
{
	GetCurPos();
	mouseRenderer->GetTransform().SetLocalPosition(GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor().x+10.0f, GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor().y,0.0f);

}
void Mouse::End()
{

}