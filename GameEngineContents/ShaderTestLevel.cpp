#include "PreCompile.h"
#include "ShaderTestLevel.h"
#include "Player.h"
#include "Texture2DShadowRenderer.h"
#include "FieldRenderingActor.h"
#include "TestFieldRenderingActor.h"
#include "Monster.h"
#include "BlackEyes.h"
#include "Brown.h"
#include "Green.h"
#include "NormalGoblin.h"
#include "RedFlyingEyes.h"
#include "FlyingEyes.h"

ShaderTestLevel::ShaderTestLevel(): shaderTestActor_(nullptr), shaderTestRenderer_(nullptr)
{
}

ShaderTestLevel::~ShaderTestLevel()
{
}

void ShaderTestLevel::Start()
{
	//GameEngineDirectory testDir;
	//testDir.MoveParentToExistChildDirectory("ContentsResources");
	//testDir.MoveToChild("ContentsResources");
	//testDir.MoveToChild("InstancingTest");
	//testDir.MoveToChild("Field");

	//GameEngineTexture2DArray::Load(testDir.GetFullPath());

	//testDir.MoveToParent("InstancingTest");
	//testDir.MoveToChild("Monster");

	//GameEngineTexture2DArray::Load(testDir.GetFullPath());


	shaderTestActor_ = CreateActor<TestFieldRenderingActor>(0, "ShaderTestActor");
	shaderTestActor_->Initialize(
		550,
		50,
		float4(100, 100),
		60.f
	);
	shaderTestActor_->GetTransform().SetLocalScale(float4::White);
	shaderTestActor_->GetTransform().SetWorldScale(float4::White);
	shaderTestActor_->GetTransform().SetWorldPosition(float4::Zero);


	//Monster::ReserveMonsters(this, 50);


	//Monster::CreateMonster<Brown>(this, 10);
	//Monster::CreateMonster<Green>(this, 10);
	//Monster::CreateMonster<NormalGoblin>(this, 10);
	//Monster::CreateMonster<RedFlyingEyes>(this, 10);
	//Monster::CreateMonster<FlyingEyes>(this, 10);

	//Monster::SummonMonster<Brown>(this, 10);
	//Monster::SummonMonster<Green>(this, 10);
	//Monster::SummonMonster<NormalGoblin>(this, 10);
	//Monster::SummonMonster<RedFlyingEyes>(this, 10);
	//Monster::SummonMonster<FlyingEyes>(this, 10);
	

}

void ShaderTestLevel::Update(float _deltaTime)
{
	shaderTestActor_->GetTransform().SetWorldPosition(GetMainCameraActor()->GetTransform().GetWorldPosition());
}

void ShaderTestLevel::End()
{
}
