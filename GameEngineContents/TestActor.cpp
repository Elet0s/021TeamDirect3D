#include"PreCompile.h"
#include"TestActor.h"

TestActor::TestActor()
	:mouseCollision01_(),
	mouseCollision02_(),
	mouseCollision03_(),
	A(false)
{

}
TestActor::~TestActor()
{

}
void TestActor::Start()
{
	mouseCollision01_ = CreateComponent<GameEngineCollision>();
	mouseCollision01_->SetDebugSetting(CollisionType::CT_OBB2D, float4::Black);
	mouseCollision01_->GetTransform().SetWorldScale(10, 10, 10);

	mouseCollision02_ = CreateComponent<GameEngineCollision>();
	mouseCollision02_->SetDebugSetting(CollisionType::CT_OBB2D, float4::Black);
	mouseCollision02_->GetTransform().SetWorldScale(10, 10, 10);

	mouseCollision03_ = CreateComponent<GameEngineCollision>();
	mouseCollision03_->SetDebugSetting(CollisionType::CT_OBB2D, float4::Black);
	mouseCollision03_->GetTransform().SetWorldScale(10, 10, 10);



}
void TestActor::Update(float _deltaTime)
{

		mouseCollision01_->GetTransform().SetWorldPosition(
			GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().x
			, GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().y
			, GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().z + 240.f);

		mouseCollision02_->GetTransform().SetWorldPosition(
			GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().x - 250.f
			, GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().y
			, GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().z + 240.f);

		mouseCollision03_->GetTransform().SetWorldPosition(
			GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().x + 250.f
			, GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().y
			, GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().z + 240.f);



}
void TestActor::End()
{

}