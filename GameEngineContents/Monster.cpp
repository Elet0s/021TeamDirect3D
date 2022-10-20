#include "PreCompile.h"
#include "Monster.h"
#include "GlobalContentsValue.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
	GameEngineDefaultRenderer* monsterRenderer = CreateComponent<GameEngineDefaultRenderer>();
	monsterRenderer->GetTransform().SetLocalScale(100, 100, 1);
	monsterRenderer->SetPipeLine("Color");
	monsterRenderer->SetMesh("Rect");


	monsterRenderer->GetShaderResourceHelper().SetConstantBuffer_Link("ResultColor", float4::Red);



}

void Monster::Update(float _deltaTime)
{
}

void Monster::End()
{
}
