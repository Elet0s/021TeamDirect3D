#include "PreCompile.h"
#include "TileMapActor.h"
#include "TileMapRenderer.h"

TileMapActor::TileMapActor(): tileRenderer_(nullptr)
{
}

TileMapActor::~TileMapActor()
{
}

void TileMapActor::Start()
{
	tileRenderer_ = CreateComponent<TileMapRenderer>();
}

void TileMapActor::Update(float _deltaTime)
{
}

void TileMapActor::End()
{
}
