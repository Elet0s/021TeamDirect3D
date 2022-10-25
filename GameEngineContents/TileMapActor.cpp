#include "PreCompile.h"
#include "TileMapActor.h"
#include "MyTileMapRenderer.h"

TileMapActor::TileMapActor(): tileRenderer_(nullptr)
{
}

TileMapActor::~TileMapActor()
{
}

void TileMapActor::Start()
{
	tileRenderer_ = CreateComponent<MyTileMapRenderer>();
}

void TileMapActor::Update(float _deltaTime)
{
}

void TileMapActor::End()
{
}
