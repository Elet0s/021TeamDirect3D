#include "PreCompile.h"
#include "ShaderTestLevel.h"
#include "Mouse.h"
#include "Player.h"
#include "Texture2DShadowRenderer.h"
#include "FieldRenderingActor.h"
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
	this->GetMainCamera()->SetProjectionMode(ProjectionMode::Perspective);
	this->GetMainCamera()->SetFarZ(500.f);
	//this->GetCamera(static_cast<UINT>(CameraOrder::MousePointerCamera))->SetProjectionMode(CameraProjectionMode::Perspective);


	shaderTestActor_ = CreateActor<Mouse>(0, "ShaderTestActor");


	
	//DirectX::XMPlaneIntersectLine();
	//DirectX::TriangleTests::Intersects();
}

void ShaderTestLevel::Update(float _deltaTime)
{
	
}

void ShaderTestLevel::End()
{
}

void ShaderTestLevel::LevelStartEvent()
{
	//shaderTestActor_->SetProjectionMode(ProjectionMode::Perspective);
}