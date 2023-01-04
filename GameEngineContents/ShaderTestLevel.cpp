#include "PreCompile.h"
#include "ShaderTestLevel.h"
#include "Mouse.h"
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
	: shaderTestActor_(nullptr)
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

	this->GetMainCamera()->SetProjectionMode(CameraProjectionMode::Orthographic);
	this->GetMainCamera()->SetFarZ(100.f);


	shaderTestActor_ = CreateActor<Mouse>(0, "ShaderTestActor");


	
	//DirectX::XMPlaneIntersectLine();
	//DirectX::TriangleTests::Intersects();
}

void ShaderTestLevel::Update(float _deltaTime)
{
	//shaderTestActor_->GetTransform().SetWorldPosition(GetMainCameraActor()->GetTransform().GetWorldPosition());
	float4 temp = shaderTestActor_->GetTransform().GetWorldPosition();


}

void ShaderTestLevel::End()
{
}
