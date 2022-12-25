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
#include "GameEngineStatusWindow.h"

ShaderTestLevel::ShaderTestLevel()
	: shaderTestActor_(nullptr),
	shaderTestRenderer_(nullptr),
	testLighting_(nullptr)
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
		10,
		1,
		float4(10, 10),
		1.f
	);
	shaderTestActor_->GetTransform().SetLocalScale(float4::White);
	shaderTestActor_->GetTransform().SetWorldScale(float4::White);
	shaderTestActor_->GetTransform().SetWorldPosition(float4::Zero);


	testLighting_ = CreateActor<GameEngineLighting>(0, "TestLighting");
	testLighting_->GetTransform().SetWorldRotation(-45.f, 45.f, 0.f);
	testLighting_->GetLightingData().mainLightColor_ = float4(0.55f, 0.55f, 0.55f);
	testLighting_->GetLightingData().ambientLightColor_ = float4(0.1f, 0.1f, 0.1f);
	testLighting_->GetLightingData().specularLightRatio_ = 0.f;
	testLighting_->GetLightingData().diffuseLightRatio_ = 2.f;

	this->GetMainCamera()->PushLighting(testLighting_);


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

	testLighting_->GetTransform().SetWorldPosition(GetMainCameraActor()->GetTransform().GetWorldPosition());
}

void ShaderTestLevel::End()
{
}
