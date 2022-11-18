#pragma once
#include "Player.h"
#include "Monster.h"
#include "BlackEyes.h"
#include "Brown.h"
#include "Green.h"
#include "NormalGoblin.h"
#include "RedFlyingEyes.h"
#include "FlyingEyes.h"

enum class ObjectOrder
{
	TileMap,
	Player,
	Monster,
	Mouse,
	Camera,
	Sector,
	UI = 1000
};


class GlobalContentsValue
{

public:
	class Actors
	{
	public:
		static Monster* testMonster_;

	private:
		Actors() {}
		~Actors() {}
	};

private:
	GlobalContentsValue() {}
	~GlobalContentsValue() {}
};

