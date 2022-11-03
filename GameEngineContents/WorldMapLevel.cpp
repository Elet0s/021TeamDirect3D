#include"PreCompile.h"
#include"WorldMapLevel.h"
#include"WorldMapActor.h"
#include "MyWorldMapRenderer.h"

WorldMapLevel::WorldMapLevel()
{

}
WorldMapLevel::~WorldMapLevel()
{

}
void WorldMapLevel::Start()
{

	WorldMapActor* WorldMap = CreateActor<WorldMapActor>();

	WorldMap->worldmaprenderer_->CreateTileMap(50, 20, {128,128}, "grassTexture.png");
}
void WorldMapLevel::Update(float _deltaTime)
{

}
void WorldMapLevel::End()
{

}
void WorldMapLevel::LevelStartEvent()
{

}